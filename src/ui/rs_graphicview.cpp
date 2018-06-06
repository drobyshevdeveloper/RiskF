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
#include "rg_painterqt.h"
#include "rs_scrollbar.h"

RS_GraphicView::RS_GraphicView(QWidget *parent, Qt::WindowFlags f, RG_Document *doc)
    : RG_GraphicView(parent)
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

        // Определим размеры представления с учетом полей, на которые можно переместиться
        // полосами прокрутки. Размер представления с полями равен
        // мах(width,boundrect.width)*2,5 x max(height,boundrect.height)*2,5
        RG_Vector min = toGui(container->getMin());
        RG_Vector max = toGui(container->getMax());
/*      if (min.x > max.x) {
            // Документ пустой, расширим его габариты до видимой области представления
            boundWidth  = getWidth();
            boundHeight = getHeight();
        }
*/
        // Учесть текущее смещение для корректировки габаритов (вдруг мы смотрим далеко за
        // габаритами документа, соответственно видимую часть представления
        // тоже необходимо включить в расчет габаритов
        min.x = std::min(min.x, 0.0);
        min.y = std::min(min.y, 0.0);
        max.x = std::max(max.x, (double)getWidth());
        max.y = std::max(max.y, (double)getHeight());
        // рассчитаем габариты документа
        int boundWidth  = max.x - min.x;
        int boundHeight = max.y - min.y;

        //  Расширим габариты на 75% от ширины и высоты представления в каждую сторону (150% по каждой оси)
        // для возможности прокрутки немного за габарит документа
        boundWidth  += 1.5 * getWidth();
        boundHeight += 1.5 * getHeight();

        hScrollbar->setRange(min.x - getWidth(), max.x);
        hScrollbar->setPageStep(getWidth());

        vScrollbar->setRange(min.y - getHeight(), max.y);
        vScrollbar->setPageStep(getHeight());

        hScrollbar->setValue(getOffsetX());
        vScrollbar->setValue(getOffsetY());

        running = false;
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

    layout->addWidget(hScrollbar, 1, 0);
    layout->addWidget(vScrollbar, 0, 1);

    bScrollbars = true;
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
    eventHandler->mousePressEvent(e);
}

void RS_GraphicView::mouseReleaseEvent(QMouseEvent *e)
{
    eventHandler->mouseReleaseEvent(e);
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
