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

#include "rg_snapper.h"

#include <QMouseEvent>

#include "rl_debug.h"
#include "rg.h"
#include "rg_vector.h"
#include "rg_entity.h"
#include "rg_entitycontainer.h"
#include "rg_line.h"
#include "rg_graphicview.h"

struct RG_Snapper::Indicator {
    RG::SnapperType type;

};

RG_Snapper::RG_Snapper(RG_EntityContainer &container, RG_GraphicView &graphicView)
    : container(&container)
    , graphicView(&graphicView)
    , snapIndicator(new Indicator)
{
    setSnapperType(RG::SnapperDefault);
}

void RG_Snapper::init(int status)
{
    snapCoord = RG_Vector{false};
    snapSpot  = RG_Vector{false};
}

RG_Snapper::~RG_Snapper()
{
    if (snapIndicator) {
        delete snapIndicator;
        snapIndicator = nullptr;
    }
}

void RG_Snapper::finish()
{
    finished = true;
}

bool RG_Snapper::isFinished()
{
    return finished;
}

// Установить новые координаты курсора
RG_Vector RG_Snapper::setSnapPoint(const RG_Vector &coord)
{
    if (coord.valid) {
        snapCoord = coord;
        drawSnapper();
    }
    return coord;
}

// Переместить курсор с учетом режимов привязки
RG_Vector RG_Snapper::snapPoint(QMouseEvent *e)
{
    // Реализуем режим привязки позже,
    // сейчас просто изменим кооринаты
    RG_Vector mouseCoord = graphicView->toGraph(double(e->pos().x()), double(e->pos().y()));
    return setSnapPoint(mouseCoord);
}

void RG_Snapper::deleteSnapper()
{
    graphicView->getOverlayContainer(RG::Snapper)->clear();
    graphicView->redraw(RG::RedrawOverlay);
}

// Нарисовать на накладываемом слое Snapper курсор
void RG_Snapper::drawSnapper()
{
    graphicView->getOverlayContainer(RG::Snapper)->clear();

    if (snapCoord) {
        RG_Line* line;
        RG_EntityContainer* overlayContainer = graphicView->getOverlayContainer(RG::Snapper);

        switch (getSnapperType()) {
        case RG::SnapperDefault:
            line = new RG_Line(nullptr, {{snapCoord.x-40, snapCoord.y},
                                         {snapCoord.x+40, snapCoord.y}});
            overlayContainer->addEntity(line);
            line = new RG_Line(nullptr,{{snapCoord.x, snapCoord.y-40},
                                        {snapCoord.x, snapCoord.y+40}});
            overlayContainer->addEntity(line);
            line = new RG_Line(nullptr,{{snapCoord.x-4, snapCoord.y-4},
                                        {snapCoord.x+4, snapCoord.y-4}});
            overlayContainer->addEntity(line);
            line = new RG_Line(nullptr,{{snapCoord.x-4, snapCoord.y+4},
                                        {snapCoord.x+4, snapCoord.y+4}});
            overlayContainer->addEntity(line);
            line = new RG_Line(nullptr,{{snapCoord.x-4, snapCoord.y-4},
                                        {snapCoord.x-4, snapCoord.y+4}});
            overlayContainer->addEntity(line);
            line = new RG_Line(nullptr,{{snapCoord.x+4, snapCoord.y-4},
                                        {snapCoord.x+4, snapCoord.y+4}});
            overlayContainer->addEntity(line);
            break;
        case RG::SnapperMiddleCross:
            line = new RG_Line(nullptr, {{snapCoord.x-40, snapCoord.y},
                                         {snapCoord.x+40, snapCoord.y}});
            overlayContainer->addEntity(line);
            line = new RG_Line(nullptr,{{snapCoord.x, snapCoord.y-40},
                                        {snapCoord.x, snapCoord.y+40}});
            overlayContainer->addEntity(line);
            break;
        case RG::SnapperLongCross:
            line = new RG_Line(nullptr, {{0, snapCoord.y},
                                         {double(graphicView->getWidth()), snapCoord.y}});
            overlayContainer->addEntity(line);

            line = new RG_Line(nullptr, {{snapCoord.x, 0},
                                         {snapCoord.x, double(graphicView->getHeight())}});
            overlayContainer->addEntity(line);

            break;
        }
    }

    graphicView->redraw(RG::RedrawOverlay);

}

void RG_Snapper::setSnapperType(RG::SnapperType type)
{
    RG::SnapperType oldType = getSnapperType();
    snapIndicator->type = type;
    if (oldType != type) {
        drawSnapper();
    }
}

RG::SnapperType RG_Snapper::getSnapperType()
{
    return snapIndicator->type;
}

RG_Entity* RG_Snapper::catchEntity(const RG_Vector &pos)
{
    double dist = 0.0;
    RG_Entity* en = container->getNearestEntity(pos, &dist);

    // Проверим, если объект слишком далеко, то его мы не нашли
    if (dist>5.0) {
        return nullptr;
    }

    RL_DEBUG << "RG_Snapper::catchEntity en=" << en << "; dist=" << dist;
    return en;
}
