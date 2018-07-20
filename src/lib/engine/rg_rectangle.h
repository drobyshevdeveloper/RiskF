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

protected:
    RG_RectangleData data;
};

#endif // RG_RECTANGLE_H
