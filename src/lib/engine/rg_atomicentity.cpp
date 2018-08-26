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

#include "rg_atomicentity.h"

RG_AtomicEntity::RG_AtomicEntity(RG_EntityContainer *parent)
    : RG_Entity(parent)
{

}

RG_AtomicEntity::~RG_AtomicEntity()
{

}

void RG_AtomicEntity::calculateBorders()
{
    RG_VectorSolutions vs = getRefPoints();
    vMin = vs[0];
    vMax = vs[0];
    for (int i=1; i<vs.count(); i++) {
        RG_Vector v = vs[i];
        if (vMin.x > v.x) vMin.x = v.x;
        if (vMax.x < v.x) vMax.x = v.x;
        if (vMin.y > v.y) vMin.y = v.y;
        if (vMax.y < v.y) vMax.y = v.y;
    }
}
