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

#include "rl_debug.h"
#include "rg_entitycontainer.h"
#include "rg_graphic.h"

RG_ActionInterface::RG_ActionInterface(const char* name,
                                       RG_EntityContainer &container,
                                       RG_GraphicView &graphicView)
    : RG_Snapper(container, graphicView)
{
    this->name = name;
    graphic = container.getGraphic();
    if (!graphic) {
        RL_DEBUG << "RG_ActionInterface::RG_ActionInterface() ERROR: RG_Graphic is not find";
        qFatal("RG_ActionInterface::RG_ActionInterface() ERROR: RG_Graphic is not find");
    }
    document = container.getDocument();
    if (!document) {
        RL_DEBUG << "RG_ActionInterface::RG_ActionInterface() ERROR: RG_Document is not find";
        qFatal("RG_ActionInterface::RG_ActionInterface() ERROR: RG_Document is not find");
    }

    actionType = RG::ActionNone;
}

RG_ActionInterface::~RG_ActionInterface()
{

}

void RG_ActionInterface::init(int status)
{
    setStatus(status);
    RG_Snapper::init(status);

}

void RG_ActionInterface::resume()
{
    updateMouseCursor();
}

void RG_ActionInterface::setStatus(int status)
{
    this->status = status;
    updateMouseCursor();
}

int RG_ActionInterface::getStatus()
{
    return status;
}

void RG_ActionInterface::coordinateEvent(RG_CoordinateEvent *ce) {}

void RG_ActionInterface::mouseMoveEvent(QMouseEvent *e) {}

void RG_ActionInterface::mousePressEvent(QMouseEvent *e) {}

void RG_ActionInterface::mouseReleaseEvent(QMouseEvent *e) {}

void RG_ActionInterface::keyPressEvent(QKeyEvent *e) {}

void RG_ActionInterface::keyReleaseEvent(QKeyEvent *e) {}
void RG_ActionInterface::updateMouseCursor() {}
