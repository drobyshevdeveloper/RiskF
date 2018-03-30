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

#include "rg_entity.h"

RG_Entity::RG_Entity(RG_EntityContainer *parent)
    : RG_Undoable()
{
    this->parent = parent;
    initID();
}

RG_Entity::~RG_Entity()
{

}

void RG_Entity::initID()
{
    static unsigned long int idCounter = 0;
    id = ++idCounter;
}
