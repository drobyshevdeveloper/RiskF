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

#include "rg_actioninterface.h"

#include "rg_entitycontainer.h"
#include "rg_graphic.h"

RG_ActionInterface::RG_ActionInterface(const char* name,
                                       RG_EntityContainer &container,
                                       RG_GraphicView &graphicView)
    : RG_Snapper(container, graphicView)
{
    this->name = name;
    graphic = container.getGraphic();

    actionType = RG::ActionNone;
}

RG_ActionInterface::~RG_ActionInterface()
{

}

void RG_ActionInterface::init()
{

}

void RG_ActionInterface::mouseMoveEvent(QMouseEvent *e) {}

void RG_ActionInterface::mousePressEvent(QMouseEvent *e) {}

void RG_ActionInterface::mouseReleaseEvent(QMouseEvent *e) {}
