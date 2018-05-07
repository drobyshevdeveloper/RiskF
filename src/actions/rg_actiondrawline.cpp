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

#include "rg_actiondrawline.h"

#include <QMouseEvent>

RG_ActionDrawLine::RG_ActionDrawLine(RG_EntityContainer &container, RG_GraphicView &graphicView)
    : RG_PreviewActionInterface("Draw line", container, graphicView)
{
    actionType = RG::ActionDrawLine;
}

RG_ActionDrawLine::~RG_ActionDrawLine()
{

}

void RG_ActionDrawLine::mousePressEvent(QMouseEvent *e)
{

}

void RG_ActionDrawLine::mouseMoveEvent(QMouseEvent *e)
{

}

void RG_ActionDrawLine::mouseReleaseEvent(QMouseEvent *e)
{

}
