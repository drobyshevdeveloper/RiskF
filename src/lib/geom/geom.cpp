#include "geom.h"
#include <cmath>

namespace Geom2D {

Coord::Coord(double x, double y)
{
    this->x = x;
    this->y = y;
}

// Функция возвращает длину вектора
double Coord::length()
{
    return hypot(x, y);
}

// Возвращает координату повернутую на угол (angle) относительно оси абцисс
//
Coord Coord::setAngle(double angle)
{
    double l = length();
    x = l * cos(angle);
    y = l * sin(angle);
    return *this;
}

// Функция возвращает точку pt1 повернутую
// на угол dAngle относительно точки pt0
Coord Coord::rotate(const Coord &center, double angle) // (POINT *pt0, ANGLEPOINT *pt1, double dAngle)
{
/*
   long dX, dY;
   long dR;

   dX = pt1->x - pt0->x;
   dY = pt0->y - pt1->y;
   dR = (long)sqrt(dX*dX + dY*dY);

   pt1->Angle += dAngle;
   if (pt1->Angle < 0)   pt1->Angle += M_2_PI;
   if (pt1->Angle > M_2_PI) pt1->Angle -= M_2_PI;

   pt1->x = long(pt0->x + cos(pt1->Angle)*dR);
   pt1->y = long(pt0->y - sin(pt1->Angle)*dR);
*/
} // Rotate

Coord Coord::operator-(const Coord& c) const
{
    return {x-c.x, y-c.y};
}

Coord Coord::operator+(const Coord& c) const
{
    return {x+c.x, y+c.y};
}

Coord Coord::operator*(const double d) const
{
    return {x*d, y*d};
}
/*
Coord Coord::operator*() const
{
    return {x,y};
}*/

/**
 * @brief getIntersection
 * Нахождение точки пересечения двух отрезков
 * Алгоритм предложен https://users.livejournal.com/-winnie/152327.html
 * @param line1
 * @param line2
 * @return
 */
bool getIntersection(const Line &line1, const Line &line2,
                     Coord* result)
{
    Coord dir1 = line1.p2 - line1.p1;
    Coord dir2 = line2.p2 - line2.p1;

    //считаем уравнения прямых проходящих через отрезки
    double a1 = -dir1.y;
    double b1 = +dir1.x;
    double d1 = -(a1*line1.p1.x + b1*line1.p1.y);

    double a2 = -dir2.y;
    double b2 = +dir2.x;
    double d2 = -(a2*line2.p1.x + b2*line2.p1.y);

    //подставляем концы отрезков, для выяснения в каких полуплоскотях они
    double seg1_line2_start = a2*line1.p1.x + b2*line1.p1.y + d2;
    double seg1_line2_end = a2*line1.p2.x + b2*line1.p2.y + d2;

    double seg2_line1_start = a1*line2.p1.x + b1*line2.p1.y + d1;
    double seg2_line1_end = a1*line2.p2.x + b1*line2.p2.y + d1;

    //если концы одного отрезка имеют один знак, значит он в одной полуплоскости и пересечения нет.
 //   if (seg1_line2_start * seg1_line2_end > 0 || seg2_line1_start * seg2_line1_end > 0)
 //       return false;

    // Если есть куда, вычислим точку пересечения и запишем в память
    if (result) {
        double u = seg1_line2_start / (seg1_line2_start - seg1_line2_end);
        *result =  line1.p1 + dir1*u;
    }
    return true;
}

// По двум диаганальным вершинам вычислить третюю и четвертую вершину
// прямоугольника, наклоненного на угол (angle) в радианах
void getRectVertex(Coord pt1, Coord pt2, double angle,
                   Coord* ptIntersect1, Coord* ptIntersect2)
{
    Line lineFace1;
    Line lineFace2;

    Coord offset1 = Coord(1000.0, 0.0).setAngle(angle);
    Coord offset2 = Coord(1000.0, 0.0).setAngle(angle + M_PI_2);
    // Формируем первую грань (от первой точки)
    lineFace1.p1 = pt1;
    lineFace1.p2 = pt1 + offset1;

    // Формируем вторую грань
    lineFace2.p1 = pt2;
    lineFace2.p2 = pt2 + offset2;

    // Первая точка пересечения
    getIntersection(lineFace1, lineFace2, ptIntersect1);
    // Перевернем линии
    lineFace1.p2 = pt1 + offset2;
    lineFace2.p2 = pt2 + offset1;
    // Вторая точка пересечения
    getIntersection(lineFace1, lineFace2, ptIntersect2);
}


} // namespace Geom2D
