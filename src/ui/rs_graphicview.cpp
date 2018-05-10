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
    layerPixmap3 = nullptr;

    // Настроить представление на прием событий перемещения мыши
    // даже при не нажатых кнопках
    setMouseTracking(true);
}

RS_GraphicView::~RS_GraphicView()
{
    // Удалим буферы графики
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

}

void RS_GraphicView::mouseReleaseEvent(QMouseEvent *e)
{

}

void RS_GraphicView::paintEvent(QPaintEvent *event)
{
    RL_DEBUG << "RS_GraphicView::paintEvent (Begin)";
    getPixmapForView(&layerPixmap3);
//    RL_DEBUG << "layerPixmap3 = " << *layerPixmap3;

    RG_PainterQt painterQt(layerPixmap3);
    layerPixmap3->fill();
    drawLayer3(&painterQt);


    painterQt.end();
    painterQt.begin(this);
    painterQt.drawPixmap(0,0,layerPixmap3);
    painterQt.end();

    RL_DEBUG << "RS_GraphicView::paintEvent (Ok)";
}

/**
 * @brief RS_GraphicView::getPixmapForView - создает буфер размером с представление
 *                Если буфер уже существует и его размер совпадает с размером представления
 *                то буфер остается прежним
 * @param pm - указатель на буфер
 */
void RS_GraphicView::getPixmapForView(QPixmap **pm)
{
//    RL_DEBUG << "RS_GraphicView::getPixmapForView Begin";
//    RL_DEBUG << (*pm);

    const QSize s(getWidth(),getHeight());
//    RL_DEBUG << s;
    if ((*pm)) {
//        RL_DEBUG << "Pixmap not NULL";
        if ((*pm)->size()==s) {
//            RL_DEBUG << "No resize";
//            RL_DEBUG << "RS_GraphicView::getPixmapForView Ok";
            return; // размер представления не изменился
        }
    }

    // Если буфер был создан, то необходимо удалить его
    if ((*pm)) {
//        RL_DEBUG << "deleting old Pixmap";
        delete (*pm);
    }
    // Создаем новый буфер с новыми размерами
//    RL_DEBUG << "create new Pixmap";
    (*pm) = new QPixmap(getWidth(), getHeight());

//    RL_DEBUG << "RS_GraphicView::getPixmapForView Ok";
}
