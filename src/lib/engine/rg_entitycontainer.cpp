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
