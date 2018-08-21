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

#include "rg_rectangle.h"

#include "rg_painter.h"
#include "rg_graphicview.h"

RG_Rectangle::RG_Rectangle(RG_EntityContainer *parent)
    : RG_AtomicEntity(parent)
{
    data.corner1 = RG_Vector(false);
    data.corner2 = RG_Vector(false);
}

RG_Rectangle::RG_Rectangle(RG_EntityContainer *parent, const RG_RectangleData& d)
    : RG_AtomicEntity(parent)
    , data(d)
{

}

RG_Entity* RG_Rectangle::clone()
{
    RG_Rectangle* rect = new RG_Rectangle(*this);
    rect->initID();
    return rect;
}

RG_Vector RG_Rectangle::getNearestPointOnEntity(const RG_Vector &coord, double *dist) const
{
    double distRes = RG_MAXDOUBLE;
    double d;
    RG_Vector ptRes;
    RG_Vector pt;

    RG_VectorSolutions vs = getRefPoints();

    pt = getNearestPointOnLine(coord, vs[0], vs[1], &d);
    if (d<distRes) {
        distRes = d;
        ptRes = pt;
    }

    pt = getNearestPointOnLine(coord, vs[1], vs[2], &d);
    if (d<distRes) {
        distRes = d;
        ptRes = pt;
    }

    pt = getNearestPointOnLine(coord, vs[2], vs[3], &d);
    if (d<distRes) {
        distRes = d;
        ptRes = pt;
    }

    pt = getNearestPointOnLine(coord, vs[3], vs[0], &d);
    if (d<distRes) {
        distRes = d;
        ptRes = pt;
    }

    if (dist) {
        *dist =distRes;
    }
    return ptRes;
}

RG_Vector RG_Rectangle::getStartPoint() const
{
    return data.corner1;
}

RG_Vector RG_Rectangle::getEndPoint() const
{
    return data.corner2;
}

void RG_Rectangle::calculateBorders()
{
    vMin.x = data.corner1.x;
    vMax.x = data.corner2.x;
    if (vMin.x > vMax.x) {
        std::swap(vMin.x, vMax.x);
    }
    vMin.y = data.corner1.y;
    vMax.y = data.corner2.y;
    if (vMin.y > vMax.y) {
        std::swap(vMin.y, vMax.y);
    }
}

void RG_Rectangle::draw(RG_Painter *painter, RG_GraphicView *view)
{
    RG_VectorSolutions vs = getRefPoints();
    painter->drawLine(vs[0], vs[1]);
    painter->drawLine(vs[1], vs[2]);
    painter->drawLine(vs[2], vs[3]);
    painter->drawLine(vs[3], vs[0]);
}

void RG_Rectangle::moveRef(RG_Marker &marker, const RG_Vector &offset)
{
    // Пока не уверен что данны вариант метода необходим
}

void RG_Rectangle::moveRef(const RG_Vector &ref, const RG_Vector &offset)
{
    RG_VectorSolutions vs = getRefPoints();
    if (vs[0].isEqu(ref)) {
        moveVertex1(offset);
        return;
    }
    if (vs[1].isEqu(ref)) {
        moveVertex2(offset);
        return;
    }
    if (vs[2].isEqu(ref)) {
        moveVertex3(offset);
        return;
    }
    if (vs[3].isEqu(ref))
        moveVertex4(offset);
}

void RG_Rectangle::moveVertex1(const RG_Vector &offset)
{
    data.corner1 = data.corner1 + offset;
    calculateBorders();
}

void RG_Rectangle::moveVertex2(const RG_Vector &offset)
{
    data.corner2.x = data.corner2.x + offset.x;
    data.corner1.y = data.corner1.y + offset.y;
    calculateBorders();
}

void RG_Rectangle::moveVertex3(const RG_Vector &offset)
{
    data.corner2 = data.corner2 + offset;
    calculateBorders();
}

void RG_Rectangle::moveVertex4(const RG_Vector &offset)
{
    data.corner1.x = data.corner1.x + offset.x;
    data.corner2.y = data.corner2.y + offset.y;
    calculateBorders();
}

RG_VectorSolutions RG_Rectangle::getRefPoints() const
{
    RG_VectorSolutions vs;

    vs.push_Back(data.corner1);
    vs.push_Back({data.corner2.x, data.corner1.y});
    vs.push_Back(data.corner2);
    vs.push_Back({data.corner1.x, data.corner2.y});

    return vs;
}
