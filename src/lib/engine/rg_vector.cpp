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

#include "rg_vector.h"

RG_Vector::RG_Vector(double vx, double vy, double vz)
{
    x = vx;
    y = vy;
    z = vz;
    valid = true;
}

RG_Vector::RG_Vector(bool valid)
    :valid(valid)
{
}

RG_Vector::operator bool() const
{
    return valid;
}

bool RG_Vector::operator == (bool valid) const
{
    return this->valid == valid;
}

bool RG_Vector::operator != (bool valid) const
{
    return this->valid != valid;
}
