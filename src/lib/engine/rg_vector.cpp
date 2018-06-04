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

#include <math.h>

#include "rg.h"

RG_Vector::RG_Vector(double vx, double vy, double vz)
{
    x = vx;
    y = vy;
    z = vz;
    valid = true;
}

/*RG_Vector::RG_Vector(int vx, int vy, int vz)
{
    x = double(vx);
    y = double(vy);
    z = double(vz);
    valid = true;
}*/

RG_Vector::RG_Vector(bool valid)
    :valid(valid)
    , x(0.0)
    , y(0.0)
    , z(0.0)
{
}

void RG_Vector::set(double vx, double vy, double vz/*=0.0*/)
{
    x = double(vx);
    y = double(vy);
    z = double(vz);
    valid = true;
}

double RG_Vector::length() const
{
    return valid ? hypot(x, y) : 0.0;
}

double RG_Vector::squared() const
{
    return valid ? x*x + y*y + z*z : 0.0;
}

double RG_Vector::distanceTo(const RG_Vector& v) const
{
    if (!valid || !v.valid) return RG_MAXDOUBLE;
    return (*this - v).length();
}

// Скалярное произведение векторов
double RG_Vector::dot(RG_Vector &v) const
{
    return x*v.x + y*v.y; //+ z*v.z;
}

RG_Vector RG_Vector::operator +(const RG_Vector& v) const
{
    return {x + v.x, y + v.y, z + v.z};
}

RG_Vector RG_Vector::operator -(const RG_Vector& v) const
{
    return {x - v.x, y - v.y, z - v.z};
}

RG_Vector RG_Vector::operator *(double n) const
{
    return {x*n, y*n, z*n};
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


// ======================================================
// RG_VectorSolutions

void RG_VectorSolutions::push_Back(const RG_Vector &v)
{
    vector.push_back(v);
}

void RG_VectorSolutions::clear()
{
    vector.clear();
}

bool RG_VectorSolutions::empty()
{
    return vector.empty();
}

RG_Vector& RG_VectorSolutions::operator [](size_t i)
{
    return vector[i];
}
