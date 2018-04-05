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

#ifndef RG_ENTITY_H
#define RG_ENTITY_H

#include "rg.h"
#include "rg_undoable.h"


class RG_EntityContainer;
class RG_Graphic;

class RG_Entity : public RG_Undoable
{
public:
    RG_Entity(RG_EntityContainer* parent);
    virtual ~RG_Entity();

    virtual RG::EntityType rtti() const {return RG::EntityUnknow;}
    virtual bool isContainer() const = 0;


    RG_Graphic* getGraphic() const;

protected: void initID();

protected:
    RG_EntityContainer* parent = nullptr;
    unsigned long int id;

};

#endif // RG_ENTITY_H
