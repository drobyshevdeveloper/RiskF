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

#include "rl_debug.h"
#include "rg_document.h"
#include "rg_eventhandler.h"
#include "rg_painterqt.h"

RS_GraphicView::RS_GraphicView(QWidget *parent, Qt::WindowFlags f, RG_Document *doc)
    : RG_GraphicView(parent)
{
    setContainer(doc);
    layerPixmap1 = nullptr;
    layerPixmap3 = nullptr;

    // Настроить представление на прием событий перемещения мыши
    // даже при не нажатых кнопках
    setMouseTracking(true);
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

int RS_GraphicView::getWidth()
{
    return width();
}

int RS_GraphicView::getHeight()
{
    return height();
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

void RS_GraphicView::paintEvent(QPaintEvent *event)
{
    RL_DEBUG << "RS_GraphicView::paintEvent (Begin)";
    getPixmapForView(&layerPixmap1);
    getPixmapForView(&layerPixmap3);
//    RL_DEBUG << "layerPixmap3 = " << *layerPixmap3;

    if (redrawMethod & RG::RedrawDrawing) {
        RG_PainterQt painter1(layerPixmap1);
        layerPixmap1->fill(Qt::white);
        drawLayer1(&painter1);
        painter1.end();
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
