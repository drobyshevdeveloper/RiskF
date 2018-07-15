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

#include "rg_preview.h"

#include "rg_entity.h"

RG_Preview::RG_Preview(RG_EntityContainer *parent)
    : RG_EntityContainer(parent)
{

}

RG_Preview::~RG_Preview()
{

}

void RG_Preview::addEntity(RG_Entity *entity)
{
    RG_EntityContainer::addEntity(entity);
}

void RG_Preview::addSelectionFrom(RG_EntityContainer *container)
{
    foreach (RG_Entity* e, container->getEntityList()) {
        if (e->isSelected()) {
            RG_Entity* ec = e->clone();
            ec->setSelected(false);
            ec->reparent(nullptr);
            addEntity(ec);
        }
    }
}
