/****************************************************************************
**
** Copyright (C) 2018 AWSoft.
** Contact: https://www.
**
** Это файл является частью программы RiskF - Программы по проведению
** расчетов величины индивидуального пожарного риска.
**
** Программа использует кроссплатформенный фреймворк для разработки ПО Qt
** под лицензией GNU LGPL v3.0 динамически подключая ее
** https://www.qt.io
**
** Лицензия на использовние исходных текстов и программы RiskF
** находится в файле licenses.txt
**
****************************************************************************/

#include "rs_graphicview.h"

#include <QScrollBar>
#include <QGridLayout>

#include "rl_debug.h"
#include "rg_document.h"
#include "rg_eventhandler.h"
#include "rg_actiondefault.h"
#include "rg_actionzoom.h"
#include "rg_actionzoompan.h"
#include "rg_painterqt.h"
#include "rs_scrollbar.h"

#define CURSOR_SIZE 16

RS_GraphicView::RS_GraphicView(QWidget *parent, Qt::WindowFlags f, RG_Document *doc)
    : RG_GraphicView(parent)
    , curCad(new QCursor(Qt::CrossCursor))
    , curArrow(new QCursor(Qt::ArrowCursor))
    , curOpenHand(new QCursor(Qt::OpenHandCursor))
    , curClosedHand(new QCursor(Qt::ClosedHandCursor))
{
    if (doc) {
        setContainer(doc);
        eventHandler->setDefaultAction(new RG_ActionDefault(*doc, *this));
    }

    layerPixmap1 = nullptr;
    layerPixmap3 = nullptr;

    // Настроить представление на прием событий перемещения мыши
    // даже при не нажатых кнопках
    setMouseTracking(true);
    setFocusPolicy(Qt::ClickFocus);

    setScale({2.0, 2.0});

    bScrollbars = false;
}

RS_GraphicView::~RS_GraphicView()
{
    // Удалим буферы графики
    if (layerPixmap1) delete layerPixmap1;
    if (layerPixmap3) delete layerPixmap3;
}

void RS_GraphicView::redraw(RG::RedrawMethod method)
{
    redrawMethod = (RG::RedrawMethod) (redrawMethod | method);
    update();
}

int RS_GraphicView::getWidth() const
{
    return width();
}

int RS_GraphicView::getHeight() const
{
    return height();
}

void RS_GraphicView::adjustOffsetControl()
{
    if (bScrollbars) {
        static bool running = false; // Флаг выполнения функции
        if (running) {
            return;
        }

        running = true;

        RG_Vector min = container->getMin();
        RG_Vector max = container->getMax();

        double ox = getOffsetX();
        double oy = getOffsetY();
        double graphW = toGraphDX(getWidth());
        double graphH = toGraphDY(getHeight());

        if (container->getEntityList().empty()) {
            // Если документ пустой, то расширим его до размеров видимого представления
            min = {.0, .0};
            max.x = min.x + graphW;
            max.y = min.y + graphH;
        }

        //  Расширим габариты на 90% от ширины и высоты представления в каждую сторону (150% по каждой оси)
        // для возможности прокрутки немного за габарит документа
        min.x -= graphW * .9;
        min.y -= graphH * .9;
        max.x += graphW * .9;
        max.y += graphH * .9;

        // Изменим при необходимости размеры видимой области с учетом видимой части представления
        // т.е. с учетом области документа которая сейчас на экране, даже если в данной части документа
        // отсутствуют сущности
        min.x = std::min(ox, min.x);
        min.y = std::min(oy, min.y);
        max.x = std::max(ox+graphW, max.x);
        max.y = std::max(oy+graphH, max.y);

        hScrollbar->setRange(min.x * getScale().x, (max.x - graphW)*getScale().x);
        hScrollbar->setPageStep(getWidth());
        hScrollbar->setSingleStep(getWidth()/10);

        vScrollbar->setRange((-max.y + graphH) * getScale().y, -min.y * getScale().y);
        vScrollbar->setPageStep(getHeight());
        vScrollbar->setSingleStep(getHeight()/10);

        hScrollbar->setValue(ox);//+0.5);
        vScrollbar->setValue(oy);//+0.5);

        running = false;
    }
}

void RS_GraphicView::setMouseCursor(RG::MouseCursor c)
{
    switch (c) {
    case RG::ArrowCursor:
        setCursor(*curArrow);
        break;
    case RG::OpenHandCursor:
        setCursor(*curOpenHand);
        break;
    case RG::ClosedHandCursor:
        setCursor(*curClosedHand);
        break;
    }
}
void RS_GraphicView::addScrollbars()
{
    hScrollbar = new RS_ScrollBar(Qt::Horizontal, this);
    vScrollbar = new RS_ScrollBar(Qt::Vertical, this);
    layout = new QGridLayout(this);

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 0);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 0);

    connect(hScrollbar, SIGNAL(valueChanged(int)),
            this, SLOT(slotHScrolled(int)));
    connect(vScrollbar, SIGNAL(valueChanged(int)),
            this, SLOT(slotVScrolled(int)));
    connect(hScrollbar, SIGNAL(sliderReleased()),
            this, SLOT(slotSliderReleased()));
    connect(vScrollbar, SIGNAL(sliderReleased()),
            this, SLOT(slotSliderReleased()));

    layout->addWidget(hScrollbar, 1, 0);
    layout->addWidget(vScrollbar, 0, 1);

    bScrollbars = true;

    adjustOffsetControl();
}

void RS_GraphicView::mouseMoveEvent(QMouseEvent *e)
{
    RL_DEBUG << "RS_GraphicView::mouseMoveEvent Begin";

    e->accept();
    eventHandler->mouseMoveEvent(e);

    RL_DEBUG << "RS_GraphicView::mouseMoveEvent Ok";
}

void RS_GraphicView::mousePressEvent(QMouseEvent *e)
{
    if (e->button()==Qt::MiddleButton) {
        setCurrentAction(new RG_ActionZoomPan(*container, *this));
    }
    eventHandler->mousePressEvent(e);
}

void RS_GraphicView::mouseReleaseEvent(QMouseEvent *e)
{
    eventHandler->mouseReleaseEvent(e);
}

void RS_GraphicView::wheelEvent(QWheelEvent *e)
{
    double zoom;
    if (e->delta() > 0) {
        // Колесико мыши повернулось вперед, от пользователя
        // Уменьшим масштаб
        setCurrentAction(new RG_ActionZoom(*container, *this, RG::Out, RG_Vector(e->x(), e->y())));
        zoom = 1 / 1.37;
    } else {
        // Колесико мыши повернулось назад, к пользователю
        // Увеличим масштаб
        zoom = 1.37;
        setCurrentAction(new RG_ActionZoom(*container, *this, RG::In, RG_Vector(e->x(), e->y())));
    }

    // Из-за погрешности вычислений позиция нарисованного курсора может меняться,
    // поэтому сместим его на текущую позицию системного курсора
    QMouseEvent* event = new QMouseEvent(QEvent::MouseMove,
                                         QPoint(e->x(), e->y()),
                                         Qt::NoButton, Qt::NoButton,
                                         Qt::NoModifier);
    eventHandler->mouseMoveEvent(event);
    delete event;

    e->accept();
}

void RS_GraphicView::keyPressEvent(QKeyEvent *e)
{
    eventHandler->keyPressEvent(e);
}

void RS_GraphicView::keyReleaseEvent(QKeyEvent *e)
{
    eventHandler->keyReleaseEvent(e);
}

void RS_GraphicView::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
}

void RS_GraphicView::leaveEvent(QEvent *event)
{
    // Указатель мыши покинул область окна, удалим курсор
    eventHandler->leaveEvent(event);
    QWidget::leaveEvent(event);
}

void RS_GraphicView::paintEvent(QPaintEvent *event)
{
    RL_DEBUG << "RS_GraphicView::paintEvent (Begin)";
    getPixmapForView(&layerPixmap1);
    getPixmapForView(&layerPixmap3);
//    RL_DEBUG << "layerPixmap3 = " << *layerPixmap3;

    if (redrawMethod & RG::RedrawDrawing) {
        layerPixmap1->fill(Qt::white);
        RG_PainterQt painter2(layerPixmap1);
        painter2.setDrawSelectOnlyMode(false);
        drawLayer2(&painter2);
        painter2.setDrawSelectOnlyMode(true);
        drawLayer2(&painter2);
        painter2.end();
    }

//    layerPixmap3->fill();
    layerPixmap3->fill(Qt::transparent);//QColor(255,255,255, Qt::transparent));
    RG_PainterQt painter3(layerPixmap3);
    drawLayer3(&painter3);
    painter3.end();

    RG_PainterQt painterQt(this);
    painterQt.drawPixmap(0,0,layerPixmap1);
    painterQt.drawPixmap(0,0,layerPixmap3);
    painterQt.end();

    redrawMethod = RG::RedrawNone;

    RL_DEBUG << "RS_GraphicView::paintEvent (Ok)";
}

void RS_GraphicView::resizeEvent(QResizeEvent *event)
{
    redraw(RG::RedrawAll);
}
/**
 * @brief RS_GraphicView::getPixmapForView - создает буфер размером с представление
 *                Если буфер уже существует и его размер совпадает с размером представления
 *                то буфер остается прежним
 * @param pm - указатель на буфер
 */
void RS_GraphicView::getPixmapForView(QPixmap **pm)
{
    const QSize s(getWidth(),getHeight());
    if ((*pm)) {
        if ((*pm)->size()==s) {
            return; // размер представления не изменился
        }
    }

    // Если буфер был создан, то необходимо удалить его
    if ((*pm)) {
        delete (*pm);
    }
    // Создаем новый буфер с новыми размерами
    (*pm) = new QPixmap(getWidth(), getHeight());
}
/*
void RS_GraphicView::slotHScrolled(int value)
{
    setOffsetX(value);
    adjustOffsetControl();
    redraw();

}

void RS_GraphicView::slotVScrolled(int value)
{
    setOffsetY(value);
    adjustOffsetControl();
    redraw();
}
*/
