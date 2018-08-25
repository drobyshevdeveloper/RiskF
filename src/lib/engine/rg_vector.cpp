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
#include <cmath>
#include <iostream>

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

bool RG_Vector::isEqu(const RG_Vector &v) const
{
    if (std::abs(x - v.x)<RG_TOLERANCE)
        if (std::abs(y - v.y)<RG_TOLERANCE)
            if (std::abs(z - v.z)<RG_TOLERANCE)
                return true;
    return false;
}

bool RG_Vector::isEquX(const RG_Vector &v) const
{
    return std::abs(x - v.x)<RG_TOLERANCE;
}

bool RG_Vector::isEquY(const RG_Vector &v) const
{
    return std::abs(y - v.y)<RG_TOLERANCE;
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

bool RG_Vector::isInWindow(const RG_Vector &v1, const RG_Vector &v2) const
{
    return (x>=std::min(v1.x, v2.x) &&
            x<=std::max(v1.x, v2.x) &&
            y>=std::min(v1.y, v2.y) &&
            y<=std::max(v1.y, v2.y));
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

RG_Vector RG_Vector::operator /(double n) const
{
    return {x/n, y/n, z/n};
}

RG_Vector::operator bool() const
{
    return valid;
}

bool RG_Vector::operator == (bool valid) const
{
    return this->valid == valid;
}

bool RG_Vector::operator == (const RG_Vector& v) const
{
    if (!valid) {
        return false;
    }
    return ((v.x==x)&&(v.y==y)&&(v.z==z));
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

int RG_VectorSolutions::count() const
{
    return vector.count();
}

bool RG_VectorSolutions::empty()
{
    return vector.empty();
}

/**
 * @brief RG_VectorSolutions::getClosest
 * найти ближайшую точку из набора к заданной
 * @param v - заданная точка
 * @return
 */
RG_Vector RG_VectorSolutions::getClosest(const RG_Vector &v)
{
    double minDist = RG_MAXDOUBLE;
    RG_Vector ret = RG_Vector(false);

    foreach (RG_Vector pt, vector) {
        double dist = pt.distanceTo(v);
        if (dist<minDist) {
            ret = pt;
            minDist = dist;
        }
    }

    return ret;
}

RG_Vector& RG_VectorSolutions::operator [](size_t i)
{
    return vector[i];
}

std::ostream& operator << (std::ostream& os, const RG_Vector& v)
{
    if(v.valid) {
        os << v.x << "/" << v.y; // << "/" << v.z;
    } else {
        os << "invalid vector";
    }
    return os;
}
