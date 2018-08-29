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
#include "geom.h"
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
    RL_DEBUG << "RG_Polygon::draw :";
    for (int i=0; i<vs.count(); i++) {
        painter->drawLine(view->toGui(vs[i]), view->toGui(vs[(i+1)%vs.count()]));
        RL_DEBUG << "line (" << view->toGui(vs[i]).x << "," << view->toGui(vs[i]).y << ")-("
                             << view->toGui(vs[(i+1)%vs.count()]).x << ","
                             << view->toGui(vs[(i+1)%vs.count()]).y << ")";
    }
}

void RG_Polygon::moveRef(const RG_Vector &ref, const RG_Vector &offset)
{
    RG_VectorSolutions vs = getRefPoints();
    for (int i=0; i<vs.count(); i++) {
        if (vs[i].isEqu(ref)) {
            moveVertex(i, offset, vs);
        }
    }
}

void RG_Polygon::moveFace(const RG_Vector &ref, const RG_Vector &offset)
{
    RG_VectorSolutions vs = getRefPoints();
    for (int i=0; i<vs.count(); i=++) {
        double dist;
        RG_Vector pt = RG_Information::getNearestPointOnLineSegment(ref, vs[i], vs[(i+1)%vs.count()], &dist);
        if (d<3.0) {
            // Найдена грань, которую необходимо переместить

        }

    }
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

void RG_Polygon::rotate(const RG_Vector &ptBase, const RG_Vector &ptAngle)
{
    for (int i=0; i<data.vertexes.count(); i++) {
        data.vertexes[i].rotate(ptBase, ptAngle - ptBase);
    }
    if (!isRect()) return;
    // Если сущность является прямоугольником, скорректируем угол наклона
    data.angle += (ptAngle - ptBase).angle();
}

void RG_Polygon::moveVertex(int index, const RG_Vector &offset, RG_VectorSolutions &vs)
{
    RL_DEBUG << "RG_Polygon::moveVertex index = " << index << ", offset(" << offset.x << "," << offset.y << ")";
    if (isRect()) {
        switch(index) {
        case 0:
            data.vertexes[0] = data.vertexes[0] + offset;
            break;
        case 1:
            RG_Information::calculateRectVertex(vs[1] + offset, vs[3], data.angle, &vs[0], &vs[2]);
            data.vertexes[0] = vs[0];
            data.vertexes[1] = vs[2];
            break;
        case 2:
            data.vertexes[1] = data.vertexes[1] + offset;
            break;
        case 3:
            RG_Information::calculateRectVertex(vs[1], vs[3] + offset, data.angle, &vs[0], &vs[2]);
            data.vertexes[0] = vs[0];
            data.vertexes[1] = vs[2];
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

    RG_Vector v3, v4;
    RG_Information::calculateRectVertex(data.vertexes[0], data.vertexes[1],
                                        data.angle, &v3, &v4);

    vs.push_Back(data.vertexes[0]);
    vs.push_Back(v3);
    vs.push_Back(data.vertexes[1]);
    vs.push_Back(v4);
/*
    Geom2D::Coord v1, v2, v3, v4;
    v1 = {data.vertexes[0].x, data.vertexes[0].y};
    v2 = {data.vertexes[1].x, data.vertexes[1].y};
    Geom2D::getRectVertex(v1, v2, data.angle, &v3, &v4);

    vs.push_Back(data.vertexes[0]);
    vs.push_Back({v3.x, v3.y});
    vs.push_Back(data.vertexes[1]);
    vs.push_Back({v4.x, v4.y});

    RL_DEBUG << "RG_Polygon::getRefPoints(rect)  v1 = ("
             << v1.x << "," << v1.y << ") v4 = ("
             << v4.x << "," << v4.y << ")";
    RL_DEBUG << "RG_Polygon::getRefPoints(rect)  vs[0] = ("
             << vs[0].x << "," << vs[0].y << ") vs[3] = ("
             << vs[3].x << "," << vs[3].y << ")";
*/
    return vs;

}
