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

#ifndef RG_OVERLAYRECT_H
#define RG_OVERLAYRECT_H

#include "rg_atomicentity.h"

class RG_OverlayRectData {
    RG_OverlayRectData()
        :corner1 (false)
        ,corner2 (false)
    {}
    RG_OverlayRectData(const RG_Vector& c1,
                       const RG_Vector& c2)
        :corner1 (c1)
        ,corner2 (c2)
    {}


    RG_Vector corner1;
    RG_Vector corner2;
}

class RG_OverlayRect : public RG_AtomicEntity
{
public:
    RG_OverlayRect(RG_EntityContainer* parent);

    virtual ~RG_OverlayRect();

    virtual RG::EntityType rtti() const override {return RG::EntityOverlayRect;}

private:
    RG_OverlayRectData data;
};

#endif // RG_OVERLAYRECT_H
