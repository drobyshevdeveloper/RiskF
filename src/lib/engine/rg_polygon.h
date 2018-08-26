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

#ifndef RG_POLYGON_H
#define RG_POLYGON_H

#include "rg_atomicentity.h"
#include "rg_vector.h"

class RG_PolygonData {
    RG_VectorSolutions vertexes;
}

class RG_Polygon : public RG_AtomicEntity
{
public:
    RG_Polygon(RG_EntityContainer* parent);
    RG_Polygon(RG_EntityContainer *parent,
                 const RG_PolygonData &d);

    virtual RG_Entity* clone() override;

    virtual RG::EntityType rtti() const override {
        return RG::EntityPolygon;
    }

    virtual RG_Vector getNearestPointOnEntity(const RG_Vector &coord,
                                              double *dist) const override;

    virtual void calculateBorders() override;

    virtual void draw(RG_Painter* painter, RG_GraphicView* view) override;
    virtual void moveRef(const RG_Vector& ref, const RG_Vector& offset) override;
    virtual void moveFace(const RG_Vector& ref, const RG_Vector& offset) override;
    virtual void move(const RG_Vector &offset) override;
/*    void moveVertex1(const RG_Vector& offset);
    void moveVertex2(const RG_Vector& offset);
    void moveVertex3(const RG_Vector& offset);
    void moveVertex4(const RG_Vector& offset);
*/

    virtual RG_VectorSolutions getRefPoints() const override;

protected:
    RG_PolygonData data;
};

#endif // RG_POLYGON_H
