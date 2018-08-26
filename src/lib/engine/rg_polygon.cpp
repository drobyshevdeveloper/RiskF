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

#include "rg_polygon.h"

#include "rl_debug.h"
#include "rg_marker.h"
#include "rg_painter.h"
#include "rg_information.h"
#include "rg_pen.h"
#include "rg_painter.h"
#include "rg_graphicview.h"

RG_Polygon::RG_Polygon(RG_EntityContainer *parent)
    : RG_AtomicEntity(parent)
{
}

RG_Polygon::RG_Polygon(RG_EntityContainer *parent, const RG_PolygonData& d, bool isRect)
    : RG_AtomicEntity(parent)
    , data(d)
{
    fRect = isRect;
    calculateBorders();
}

RG_Entity* RG_Polygon::clone()
{
    RG_Polygon* poly = new RG_Polygon(*this);
    poly->initID();
    return poly;
}

double RG_Polygon::getWidth()
{
    if (!isRect()) return 0;

    // Вычислить ширину прямоугольника
    return 0;
}

double RG_Polygon::getHeight()
{
    if (!isRect()) return 0;

    // Вычислить высоту прямоугольника
    return 0;
}

RG_Vector RG_Polygon::getNearestPointOnEntity(const RG_Vector &coord, double *dist) const
{
    double distRes = RG_MAXDOUBLE;
    double d;
    RG_Vector ptRes;
    RG_Vector pt;

    RG_VectorSolutions vs = getRefPoints();

    for (int i=0; i<vs.count(); i++) {
        pt = RG_Information::getNearestPointOnLineSegment(coord, vs[i], vs[(i+1)%vs.count()], &d);
        if (d<distRes) {
            distRes = d;
            ptRes = pt;
        }
    }

    if (RG_Information::isPointInPolygon(coord, vs)) {
        distRes = 0.0;
        ptRes = coord;
    }

    if (dist) {
        *dist =distRes;
    }
    return ptRes;
}

/*
void RG_Polygon::calculateBorders()
{
    vMin = data.vertexes[0];
    vMax = data.vertexes[0];
    for (int i=1; i<data.vertexes.count(); i++) {
        RG_Vector v = data.vertexes[i];
        if (vMin.x > v.x) vMin.x = v.x;
        if (vMax.x < v.x) vMax.x = v.x;
        if (vMin.y > v.y) vMin.y = v.y;
        if (vMax.y < v.y) vMax.y = v.y;
    }
}
*/
void RG_Polygon::draw(RG_Painter *painter, RG_GraphicView *view)
{
    if ( !(painter && view) ) {
        return;
    }

    RG_Pen pen;
    pen.setColor(QColor(Qt::black));

    if (isSelected()) {
        pen.setColor(QColor(Qt::red));
    }
    painter->setPen(pen);

    RG_VectorSolutions vs = getRefPoints();
    for (int i=0; i<vs.count(); i++) {
        painter->drawLine(view->toGraph(vs[i]), view->toGraph(vs[(i+1)%vs.count()]));
    }
}

void RG_Polygon::moveRef(const RG_Vector &ref, const RG_Vector &offset)
{
    RG_VectorSolutions vs = getRefPoints();
    for (int i=0; i<vs.count(); i++) {
        if (vs[i].isEqu(ref)) {
            moveVertex(i, offset);
        }
    }
}

void RG_Polygon::moveFace(const RG_Vector &ref, const RG_Vector &offset)
{
/*    RG_Marker marker = getNearestMarkerFace(ref);
    if (marker.valid && marker.type == RG_Marker::Face && marker.dist<3.0) {
        RG_VectorSolutions vs = getRefPoints();
        const RG_Vector offsetX = {offset.x, 0.0};
        const RG_Vector offsetY = {0.0, offset.y};
        switch (marker.index) {
        case 0:
            moveVertex1(offsetY);
            break;
        case 1:
            moveVertex2(offsetX);
            break;
        case 2:
            moveVertex3(offsetY);
            break;
        case 3:
            moveVertex4(offsetX);
            break;
        }
    }*/
}

void RG_Polygon::move(const RG_Vector &offset)
{
    for (int i=0; i<data.vertexes.count(); i++) {
        data.vertexes[i] = data.vertexes[i] + offset;
    }
    calculateBorders();
}

void RG_Polygon::moveVertex(int index, const RG_Vector &offset)
{
    RL_DEBUG << "RG_Polygon::moveVertex index = " << index << ", offset(" << offset.x << "," << offset.y << ")";
    if (isRect()) {
        switch(index) {
        case 0:
            data.vertexes[0] = data.vertexes[0] + offset;
            break;
        case 1:
            data.vertexes[1].x = data.vertexes[1].x + offset.x;
            data.vertexes[0].y = data.vertexes[0].y + offset.y;
            break;
        case 2:
            data.vertexes[1] = data.vertexes[1] + offset;
            break;
        case 3:
            data.vertexes[0].x = data.vertexes[0].x + offset.x;
            data.vertexes[1].y = data.vertexes[1].y + offset.y;
            break;
        }
    } else {
        data.vertexes[index] = data.vertexes[index] + offset;
    }
    calculateBorders();
}

RG_VectorSolutions RG_Polygon::getRefPoints() const
{
    if (!isRect()) return data.vertexes;

    // Примитив является прямоугольником, вычислим вершины по двум диаганальным точкам и углу поворота
    RG_VectorSolutions vs;

    vs.push_Back(data.vertexes.getVector().at(0));
    vs.push_Back({data.vertexes[1].x, data.vertexes[0].y});
    vs.push_Back(data.vertexes[1]);
    vs.push_Back({data.vertexes[0].x, data.vertexes[1].y});

    return vs;

}
