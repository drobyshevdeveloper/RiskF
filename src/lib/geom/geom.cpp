#include "geom.h"

namespace Geom2D {

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
    if (seg1_line2_start * seg1_line2_end > 0 || seg2_line1_start * seg2_line1_end > 0)
        return false;

    // Если есть куда, вычислим точку пересечения и запишем в память
    if (result) {
        double u = seg1_line2_start / (seg1_line2_start - seg1_line2_end);
        *result =  line1.p1 + dir1*u;
    }
    return true;
}

} // namespace Geom2D
