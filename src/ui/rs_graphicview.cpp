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


#include "rg_document.h"
#include "rg_eventhandler.h"

RS_GraphicView::RS_GraphicView(QWidget *parent, Qt::WindowFlags f, RG_Document *doc)
    : RG_GraphicView(parent)
{
    setContainer(doc);
}

RS_GraphicView::~RS_GraphicView()
{

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
    e->accept();
    eventHandler->mouseMoveEvent(e);
}

void RS_GraphicView::mousePressEvent(QMouseEvent *e)
{

}

void RS_GraphicView::mouseReleaseEvent(QMouseEvent *e)
{

}

void RS_GraphicView::paintEvent(QPaintEvent *event)
{
}
