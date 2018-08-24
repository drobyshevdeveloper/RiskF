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

#ifndef RG_RECTANGLE_H
#define RG_RECTANGLE_H

#include "rg_atomicentity.h"

#include "rg_vector.h"

class RG_EntityContainer;

struct RG_RectangleData {
    RG_Vector corner1;
    RG_Vector corner2;
};

class RG_Rectangle : public RG_AtomicEntity
{
public:
    RG_Rectangle(RG_EntityContainer* parent);
    RG_Rectangle(RG_EntityContainer *parent,
                 const RG_RectangleData &d);

    virtual RG_Entity* clone() override;

    virtual RG::EntityType rtti() const override {
        return RG::EntityRectangle;
    }

    virtual RG_Vector getNearestPointOnEntity(const RG_Vector &coord,
                                              double *dist) const override;

    virtual RG_Vector getStartPoint() const override;
    virtual RG_Vector getEndPoint() const override;
    virtual void calculateBorders() override;

    virtual void draw(RG_Painter* painter, RG_GraphicView* view) override;
    virtual void moveRef(RG_Marker& marker, const RG_Vector& offset) override;
    virtual void moveRef(const RG_Vector& ref, const RG_Vector& offset) override;
    virtual void moveFace(const RG_Marker &marker, const RG_Vector &offset) override;
    virtual void moveFace(const RG_Vector& ref, const RG_Vector& offset) override;
    virtual void move(const RG_Vector &offset) override;
//    void moveStartPoint(const RG_Vector& offset);
//    void moveEndPoint(const RG_Vector& offset);
    void moveVertex1(const RG_Vector& offset);
    void moveVertex2(const RG_Vector& offset);
    void moveVertex3(const RG_Vector& offset);
    void moveVertex4(const RG_Vector& offset);


    RG_VectorSolutions getRefPoints() const override;


protected:
    RG_RectangleData data;
};

#endif // RG_RECTANGLE_H
