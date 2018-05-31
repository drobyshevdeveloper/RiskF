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

#ifndef RG_VECTOR_H
#define RG_VECTOR_H


class RG_Vector;

class RG_Vector
{
public:
    RG_Vector()=default;
    RG_Vector(double vx, double vy, double vz=0.0);
//    RG_Vector(int vx, int vy, int vz=0);
    RG_Vector(bool valid);

    void set(double vx, double vy, double vz=0.0);

    // Длина вектора
    double length() const;
    // Квадрат длины вектора (или скалярное произведение вектора самого на себя
    double squared() const;
    // Определить расстояние до заданной точки
    double distanceTo(const RG_Vector& v) const;
    // Определить скалярное произведение векторов
    double dot(RG_Vector& v) const;

    operator bool() const;
    RG_Vector operator + (const RG_Vector& v) const;
    RG_Vector operator - (const RG_Vector& v) const;
    RG_Vector operator * (double n) const;
    bool operator == (bool valid) const;
    bool operator != (bool valid) const;

public:
    double x=0.;
    double y=0.;
    double z=0.;
    bool valid=false;
};

#endif // RG_VECTOR_H
