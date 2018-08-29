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
#include "rg_line.h"
#include "rg_information.h"

RG_EntityContainer::RG_EntityContainer(RG_EntityContainer *parent, bool owner)
    : RG_Entity(parent)
{
    this->owner = owner;
    resetBorders();
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

RG_Entity* RG_EntityContainer::clone()
{
    // Надо реализовать
    RG_EntityContainer* ec = new RG_EntityContainer(*this);
    ec->initID();
    return ec;
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
    adjustBorders(entity);
}

void RG_EntityContainer::removeEntity(RG_Entity *entity)
{
    if (!entity) {
        return;
    }
    entities.removeOne(entity);
    if (owner) {
        delete entity;
    }
    calculateBorders();
}

const QList<RG_Entity *> RG_EntityContainer::getEntityList()
{
    return entities;
}

void RG_EntityContainer::setSelected(bool select)
{
    foreach (RG_Entity* e, getEntityList()) {
        e->setSelected(select);
    }
}

int RG_EntityContainer::countSelection() const
{
    int result = 0;
    for (RG_Entity* e: entities) {
        if (e->isContainer()) result += static_cast<RG_EntityContainer*>(e)->countSelection();
        else if (e->isSelected()) result++;
    }

    return result;
}

/**
 * @brief RG_EntityContainer::selectWindow - выбирает или отменяет выбор сущности,
 * попавших в прямоугольную область выделения
 * @param v1 - первая точка прямоугольной области выделения
 * @param v2 - вторая точка прямоугольной точки выделения
 * @param select - true если необходимо выделить сущности, false если необходимо снять выделение
 * @param cross  - true выделить сущности полностью и частично попавшие в прямоугольную область выделения
 *                 false выделить сущности полностью поппавшие в прямоугольную область выделения
 */
void RG_EntityContainer::selectWindow(RG_Vector v1, RG_Vector v2, bool select, bool cross)
{
    if (!isVisible()) {
        return;
    }

    // Создадим 4 линии из прямоугольной области выделения
    RG_Line l1 = RG_Line(nullptr, {v1, {v2.x, v1.y}});
    RG_Line l2 = RG_Line(nullptr, {v1, {v1.x, v2.y}});
    RG_Line l3 = RG_Line(nullptr, {{v1.x, v2.y}, v2});
    RG_Line l4 = RG_Line(nullptr, {{v2.x, v1.y}, v2});

    foreach (RG_Entity* e, entities) {
        bool included = false;

        // Проверим видимость сущности
        if (!e->isVisible()) {
            continue;
        }

        if (e->isInWindow(v1, v2)){
            included = true;
        } else if (cross) {
            if (e->isContainer()) {
                RG_EntityContainer* ec = (RG_EntityContainer*)e;
                ec->selectWindow(v1, v2, select, cross);
            } else {
                if (!RG_Information::getIntersection(e, &l1).empty())
                    included = true;
                else if (!RG_Information::getIntersection(e, &l2).empty())
                    included = true;
                else if (!RG_Information::getIntersection(e, &l3).empty())
                    included = true;
                else if (!RG_Information::getIntersection(e, &l4).empty())
                    included = true;
            }
        }

        if (included) {
            e->setSelected(select);
        }
    }
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

RG_Marker RG_EntityContainer::getNearestSelectedRef(const RG_Vector& coord) const
{
    RG_Marker marker;
    marker.dist = RG_MAXDOUBLE;

    foreach (auto e, entities) {
        RG_Marker m = e->getNearestSelectedRef(coord);
        if (m.valid && (marker.dist > m.dist)) {
            marker = m;
        }
    }

    return marker;
}

double RG_EntityContainer::getDistanceToPoint(const RG_Vector &coord,
                                              RG_Entity** entity) const
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
        resetBorders();
    }
}

void RG_EntityContainer::draw(RG_Painter *painter, RG_GraphicView *view)
{
    if ( !(painter && view)) {
        return;
    }

    foreach (RG_Entity* e, entities) {
        view->drawEntity(painter, e);
    }
}

void RG_EntityContainer::moveRef(const RG_Vector& ref, const RG_Vector& offset)
{
    foreach (RG_Entity* e, entities) {
        e->moveRef(ref, offset);
    }
    calculateBorders();
}

/*
void RG_EntityContainer::moveFace(const RG_Marker &marker, const RG_Vector &offset)
{
    marker.entity->moveFace(marker, offset);
    calculateBorders();
}
*/

void RG_EntityContainer::moveFace(const RG_Vector &ref, const RG_Vector &offset)
{
    foreach (RG_Entity* e, entities) {
        e->moveFace(ref, offset);
    }
    calculateBorders();
}

void RG_EntityContainer::move(const RG_Vector &offset)
{
    foreach (auto e, entities) {
        e->move(offset);
    }
    calculateBorders();
}

void RG_EntityContainer::rotate(const RG_Vector &ptBase, const RG_Vector &ptAngle)
{
    foreach (auto e, entities) {
        e->rotate(ptBase, ptAngle);
    }
    calculateBorders();
}

void RG_EntityContainer::calculateBorders()
{
    resetBorders();

    foreach (RG_Entity* e, entities) {
        if (e->isVisible()) {
            e->calculateBorders();
            adjustBorders(e);
        }
    }
}

void RG_EntityContainer::adjustBorders(const RG_Entity *e)
{
    vMin.x = std::min(e->getMin().x, vMin.x);
    vMax.x = std::max(e->getMax().x, vMax.x);
    vMin.y = std::min(e->getMin().y, vMin.y);
    vMax.y = std::max(e->getMax().y, vMax.y);
}
