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

#ifndef RG_ENTITYCONTAINER_H
#define RG_ENTITYCONTAINER_H

#include "rg_entity.h"

class RG_EntityContainer;

class RG_EntityContainer : public RG_Entity
{
public:
    RG_EntityContainer(RG_EntityContainer* parent);
    virtual ~RG_EntityContainer();

    virtual RG::EntityType rtti() const {return RG::EntityContainer;}
};

#endif // RG_ENTITYCONTAINER_H
