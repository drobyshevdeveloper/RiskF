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

#include <vector>
#include <cstdio>
#include <iosfwd>


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
    RG_Vector operator / (double n) const;

    bool operator == (bool valid) const;
    bool operator != (bool valid) const;
    friend std::ostream& operator << (std::ostream& os, const RG_Vector& v);

public:
    double x=0.;
    double y=0.;
    double z=0.;
    bool valid=false;
};

/**
 * @brief The RG_VectorSolutions class
 * Класс содержит список нескольких векторов
 * Используется при возврате функциями списка векторов
 */
class RG_VectorSolutions
{
public:
    RG_VectorSolutions() = default;

    void push_Back(const RG_Vector& v);
    void clear();
    bool empty();
    RG_Vector& operator [] (const size_t i);

private:
    std::vector<RG_Vector> vector;

};

#endif // RG_VECTOR_H
