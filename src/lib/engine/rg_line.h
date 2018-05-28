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

#ifndef RG_LINE_H
#define RG_LINE_H

#include "rg_atomicentity.h"


#include "rg_vector.h"

class RG_Painter;
class RG_GraphicView;

struct RG_LineData {
    RG_Vector startPoint;
    RG_Vector endPoint;
};

class RG_Line : public RG_AtomicEntity
{
public:
    RG_Line(RG_EntityContainer* parent);
    RG_Line(RG_EntityContainer *parent,
            const RG_LineData& d);

    virtual RG::EntityType rtti() const override {
        return RG::EntityLine;
    }

    virtual RG_Vector getNearestPointOnEntity(const RG_Vector &coord,
                                              double *dist) const override;

    virtual RG_Vector getStartPoint() const override;
    virtual RG_Vector getEndPoint() const override;

    virtual void draw(RG_Painter* painter, RG_GraphicView* view) override;
private:
    RG_LineData data;
};

#endif // RG_LINE_H
