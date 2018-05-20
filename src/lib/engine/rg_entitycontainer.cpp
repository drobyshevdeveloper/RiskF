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

#include "rg_entitycontainer.h"
#include "rg_painter.h"
#include "rg_graphicview.h"

RG_EntityContainer::RG_EntityContainer(RG_EntityContainer *parent, bool owner)
    : RG_Entity(parent)
{
    this->owner = owner;
}

RG_EntityContainer::~RG_EntityContainer()
{
    if (owner) {
        // Если контейнер владеет своими элементами, то перед
        // удалением необходимо удалить и элементы
        while (!entities.isEmpty()) {
            delete entities.takeFirst();
        }
    } else {
        entities.clear();
    }
}

void RG_EntityContainer::setOwner(bool owner)
{
    this->owner = owner;
}

void RG_EntityContainer::addEntity(RG_Entity *entity)
{
    if (!entity) {
        return;
    }
    entities.append(entity);
}

const QList<RG_Entity *> RG_EntityContainer::getEntityList()
{
    return entities;
}

RG_Vector RG_EntityContainer::getNearestPointOnEntity(const RG_Vector &coord, double *dist) const
{
    return RG_Vector();
}

RG_Entity* RG_EntityContainer::getNearestEntity(const RG_Vector &coord, double *dist) const
{
    double distResult = RG_MAXDOUBLE;
    RG_Entity* en = nullptr;

    distResult = getDistanceToPoint(coord, &en);
    if (dist) {
        *dist = distResult;
    }
    return en;
}

double RG_EntityContainer::getDistanceToPoint(const RG_Vector &coord, RG_Entity** entity) const
{
    RG_Entity* en = nullptr;
    double distResult = RG_MAXDOUBLE;
    double distEntity = RG_MAXDOUBLE;
    RG_Vector v;

    foreach (auto e, entities) {
        distEntity = e->getDistanceToPoint(coord);
        if (distEntity <= distResult) {
            distResult = distEntity;
            en = e;
        }
    }

    if (entity) {
        (*entity) = en;
    }

    return distResult;
}

void RG_EntityContainer::clear()
{
    if (owner) {
        // Если контейнер владеет своими элементами, то перед
        // удалением необходимо удалить и элементы
        while (!entities.isEmpty()) {
            delete entities.takeFirst();
        }
    } else {
        entities.clear();
    }
}

void RG_EntityContainer::draw(RG_Painter *painter, RG_GraphicView *view)
{
    if ( !(painter && view)) {
        return;
    }

    foreach (auto a, entities) {
        a->draw(painter,view);
    }
}
