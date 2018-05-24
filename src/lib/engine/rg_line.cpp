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

}

RG_Vector RG_Line::getNearestPointOnEntity(const RG_Vector &coord, double *dist) const
{
    // Используем формулу: proj_b_to_a = a * dot(a, b)/dot(a,a)
    // Преобразуе линию в вектор (a)
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
}

RG_Vector RG_Line::getStartPoint() const
{
    return data.startPoint;
}

RG_Vector RG_Line::getEndPoint() const
{
    return data.endPoint;
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

    painter->drawLine(getStartPoint(), getEndPoint());

}
