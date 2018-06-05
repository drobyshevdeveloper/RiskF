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
#include "rg_painter.h"
#include "rg_eventhandler.h"
#include "rg_entitycontainer.h"

RG_GraphicView::RG_GraphicView(QWidget *parent)
    : QWidget(parent)
    , eventHandler(new RG_EventHandler(this))
{
    setScale(RG_Vector{1.0, 1.0});
    setOffset(0 ,0);
}

RG_GraphicView::~RG_GraphicView()
{
    if (!overlayEntities.empty()) {
        for (auto a : overlayEntities) {
            delete a;
        }
        overlayEntities.clear();
    }
    if (eventHandler) {
        delete eventHandler;
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
// Смещение начала координат документа относительно левого нижнего угла представления
void RG_GraphicView::setOffset(int ox, int oy)
{
    setOffsetX(ox);
    setOffsetY(oy);
}

void RG_GraphicView::setOffsetX(int ox)
{
    offsetX = ox;
}

void RG_GraphicView::setOffsetY(int oy)
{
    offsetY = oy;
}

int RG_GraphicView::getOffsetX() const
{
    return offsetX;
}

int RG_GraphicView::getOffsetY() const
{
    return offsetY;
}

void RG_GraphicView::setScale(const RG_Vector &sv)
{
    scale = sv;
}

RG_Vector RG_GraphicView::getScale() const
{
    return scale;
}

// Преобразование координат документа в координаты окна
RG_Vector RG_GraphicView::toGui(const RG_Vector& v) const
{
    return {toGuiX(v.x), toGuiY(v.y)};
}
double RG_GraphicView::toGuiX(const double x) const
{
    return x * scale.x + offsetX;
}
double RG_GraphicView::toGuiY(const double y) const
{
    return - y * scale.y + getHeight() - offsetY;
}
double RG_GraphicView::toGuiDX(const double dx) const
{
    return dx * scale.x;
}
double RG_GraphicView::toGuiDY(const double dy) const
{
    return dy * scale.x;
}
// Преобразование координат окна в координаты документа
RG_Vector RG_GraphicView::toGraph(const RG_Vector& v) const
{
    return {toGraphX(std::round(v.x)),
            toGraphY(std::round(v.y))};
}
double RG_GraphicView::toGraphX(const int x) const
{
    return ( x - offsetX ) / scale.x;
}
double RG_GraphicView::toGraphY(const int y) const
{
    return - ( y - getHeight() + offsetY ) / scale.y;
}
double RG_GraphicView::toGraphDX(const int dx) const
{
    return dx / scale.x;
}
double RG_GraphicView::toGraphDY(const int dy) const
{
    return dy / scale.y;
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

void RG_GraphicView::drawLayer2(RG_Painter *painter)
{
    RL_DEBUG << "RG_GraphicView::drawLayer2 Begin";

    foreach (RG_Entity* e, container->getEntityList()) {
        if (!e->isContainer() && (e->isSelected()!=painter->getDrawSelectOnlyMode()))  {
            continue;
        }
        e->draw(painter, this);
    }

    RL_DEBUG << "RG_GraphicView::drawLayer2 Ok";
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
