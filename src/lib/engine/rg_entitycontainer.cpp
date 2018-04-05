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

RG_EntityContainer::RG_EntityContainer(RG_EntityContainer *parent)
    : RG_Entity(parent)
{

}

RG_EntityContainer::~RG_EntityContainer()
{

}

void RG_EntityContainer::addEntity(RG_Entity *entity)
{
    if (!entity) {
        return;
    }
    entities.append(entity);
}
