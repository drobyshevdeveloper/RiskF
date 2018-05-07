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

#include "rg_graphic.h"

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

/**
 * @brief RG_Entity::getGraphic - поиск объекта графического документа, которому принадлежить сущьность
 * @return ссылку на объект документа, или nullptr
 */
RG_Graphic* RG_Entity::getGraphic() const
{
    if (rtti()==RG::EntityGraphic) {
        RG_Graphic const* ret=static_cast<RG_Graphic const*>(this);
        return const_cast<RG_Graphic*>(ret);
    } else if (!parent) {
        return nullptr;
    }
    return parent->getGraphic();
}

RG_Vector RG_Entity::getStartPoint() const
{
    return {};
}

RG_Vector RG_Entity::getEndPoint() const
{
    return {};
}
