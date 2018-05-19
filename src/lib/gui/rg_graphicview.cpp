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

#include "rg_graphicview.h"

#include "rl_debug.h"
#include "rg_eventhandler.h"
#include "rg_entitycontainer.h"

RG_GraphicView::RG_GraphicView(QWidget *parent)
    : QWidget(parent)
    , eventHandler(new RG_EventHandler(this))
{

}

RG_GraphicView::~RG_GraphicView()
{
    if (!overlayEntities.empty()) {
        for (auto a : overlayEntities) {
            delete a;
        }
        overlayEntities.clear();
    }
}

void RG_GraphicView::setContainer(RG_EntityContainer *c)
{
    container = c;
}

void RG_GraphicView::killAllActions()
{
    if (eventHandler) {
        eventHandler->killAllActions();
    }
}



void RG_GraphicView::setCurrentAction(RG_ActionInterface *action)
{
    if (eventHandler) {
        eventHandler->setCurrentAction(action);
    }
}

RG_EntityContainer* RG_GraphicView::getOverlayContainer(RG::OverlayGraphics position)
{
    if (overlayEntities[position]) {
        return overlayEntities[position];
    }

    overlayEntities[position] = new RG_EntityContainer(nullptr);
    return overlayEntities[position];
}

void RG_GraphicView::drawLayer1(RG_Painter *painter)
{
    RL_DEBUG << "RG_GraphicView::drawLayer1 Begin";

    foreach (RG_Entity* e, container->getEntityList()) {
        e->draw(painter, this);
    }

    RL_DEBUG << "RG_GraphicView::drawLayer1 Ok";
}

void RG_GraphicView::drawLayer3(RG_Painter *painter)
{
    RL_DEBUG << "RG_GraphicView::drawLayer3 Begin";
    if (overlayEntities.empty()) {
        RL_DEBUG << "Empty";
        return;
    }

    foreach (RG_EntityContainer* oe, overlayEntities) {
        foreach (RG_Entity* e, oe->getEntityList()) {
            RL_DEBUG << e;
            e->draw(painter, this);
        }
    }

    RL_DEBUG << "RG_GraphicView::drawLayer3 Ok";
}
