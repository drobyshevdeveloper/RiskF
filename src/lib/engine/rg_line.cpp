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

#include "rg_line.h"

#include <cmath>

#include "rg_pen.h"
#include "rg_painter.h"
#include "rg_graphicview.h"

RG_Line::RG_Line(RG_EntityContainer *parent)
    : RG_AtomicEntity(parent)
{

}

RG_Line::RG_Line(RG_EntityContainer *parent, const RG_LineData &d)
    : RG_AtomicEntity(parent), data(d)
{
    calculateBorders();
}

RG_Entity* RG_Line::clone()
{
    RG_Line* l = new RG_Line(*this);
    l->initID();
    return l;
}

RG_Vector RG_Line::getNearestPointOnEntity(const RG_Vector &coord, double *dist) const
{
    return getNearestPointOnLine(coord, data.startPoint, data.endPoint, dist);
    /*
    // Используем формулу: proj_b_to_a = a * dot(a, b)/dot(a,a) (dot - скалярное произведение векторов)
    // Преобразуем линию в вектор (a)
    RG_Vector direction = data.endPoint - data.startPoint;
    // Квадрат длины вектора (dot(a,a))
    double len2 = direction.squared();
    // Преобразуем указанную точку в вектор (b)
    RG_Vector vct = coord - data.startPoint;
    // Найдем dot(a,b)/dot(a,a)
    double t = vct.dot(direction) / len2;
    // Умножим вектор линии на полученный t и перенесем на линию получив точку
    RG_Vector result = data.startPoint + direction * t;
    if (dist) {
        *dist = coord.distanceTo(result);
    }
    return result;
    */
}

RG_Vector RG_Line::getStartPoint() const
{
    return data.startPoint;
}

RG_Vector RG_Line::getEndPoint() const
{
    return data.endPoint;
}

void RG_Line::calculateBorders()
{
    vMin.x = data.startPoint.x;
    vMax.x = data.endPoint.x;
    if (vMin.x > vMax.x) {
        std::swap(vMin.x, vMax.x);
    }
    vMin.y = data.startPoint.y;
    vMax.y = data.endPoint.y;
    if (vMin.y > vMax.y) {
        std::swap(vMin.y, vMax.y);
    }
}

void RG_Line::draw(RG_Painter *painter, RG_GraphicView *view)
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

    painter->drawLine(view->toGui(getStartPoint()),
                      view->toGui(getEndPoint()));

}

void RG_Line::moveRef(RG_Marker &marker, const RG_Vector &offset)
{
    if (marker.index==0) {
        data.startPoint = marker.coord + offset;
    } else {
        data.endPoint = marker.coord + offset;
    }
}

void RG_Line::moveRef(const RG_Vector &ref, const RG_Vector &offset)
{
    if ((std::abs(getStartPoint().x-ref.x)<RG_TOLERANCE) &&
        (std::abs(getStartPoint().y-ref.y)<RG_TOLERANCE)) {
        moveStartPoint(offset);
        return;
    }
    if ((std::abs(getEndPoint().x-ref.x)<RG_TOLERANCE) &&
        (std::abs(getEndPoint().y-ref.y)<RG_TOLERANCE)) {
        moveEndPoint(offset);
    }
}

void RG_Line::moveFace(const RG_Marker &marker, const RG_Vector &offset)
{
    move(offset);
}

void RG_Line::moveFace(const RG_Vector &ref, const RG_Vector &offset)
{
    RG_Marker m = getNearestMarkerFace(ref);
    if (m.valid && m.type == RG_Marker::Face) {
        move(offset);
    }
}

void RG_Line::move(const RG_Vector &offset)
{
    moveStartPoint(offset);
    moveEndPoint(offset);
}

void RG_Line::moveStartPoint(const RG_Vector &offset)
{
    data.startPoint = data.startPoint + offset;
    calculateBorders();
}

void RG_Line::moveEndPoint(const RG_Vector &offset)
{
    data.endPoint = data.endPoint + offset;
    calculateBorders();
}

RG_VectorSolutions RG_Line::getRefPoints() const
{
    RG_VectorSolutions vs;

    vs.push_Back(getStartPoint());
    vs.push_Back(getEndPoint());

    return vs;
}
