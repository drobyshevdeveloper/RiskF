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

#ifndef RG_MARKER_H
#define RG_MARKER_H

#include "rg_vector.h"

class RG_Entity;

class RG_Marker
{
public:
    enum Typ {
        Move,           // Маркер перемещения сущности целиком
        Vertex,         // Маркер изменения вершины сущности
        Face,           // Маркер изменения грани сущности
        Rotate          // Маркер изменения угла наклона сущности
    };

    RG_Marker();

    bool       valid;  // флаг валидности описания маркера
    RG_Entity* entity; // ссылка на сущность, которой принадлежит маркер
    RG_Vector  coord;  // координаты маркера
    RG_Vector offset;  // смещение до маркера (от заданной точки)
    double     dist;   // расстояние до маркера (от искомой точки)
    int        index;  // порядковый номер маркера в списке маркера сущности
    Typ        type;   // Тип маркера
};

#endif // RG_MARKER_H
