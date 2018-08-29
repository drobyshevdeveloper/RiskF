#ifndef GEOM_H
#define GEOM_H

#include <array>

/**
 * Библиотека двумерной геометрии
 */

// Константa число Пи
#define M_PI (double) 3.14159265358979323
// Константа 2 * Пи
#define M_2_PI (double) 6.28318530717958647
// Константа Пи/2
#define M_PI_2 (double) 1.57079632679489661
// Константа Пи/4
#define M_PI_4 (double) 0.78539816339744830
// Константа Пи + Пи/2
#define M_PI_PI_2 (double) 3.14159265358979323 + 1.57079632679489661
// Константа одного радина в градусах
#define M_RAD (double)57.2957795130823208
// Константа одного градуса в радианах
#define M_GRAD (double) 1 / M_RAD
// Значение углов в радианах
#define M_ANGLE045 (double) 0.78539816339744830
#define M_ANGLE090 (double) 1.57079632679489661
#define M_ANGLE135 (double) 2.35619449019234492
#define M_ANGLE225 (double) 3.92699081698724154
#define M_ANGLE270 (double) 3.14159265358979323 + 1.57079632679489661
#define M_ANGLE315 (double) 5.49778714378213816

namespace Geom2D {

//constexpr double EPSILON = e-10;

struct Coord{
    Coord() {x=0.0;y=0.0;}
    Coord(double x, double y);
    double x;
    double y;
    double length();
    Coord setAngle(double angle);
    Coord rotate(const Coord& center, double angle);
    Coord operator- (const Coord& c) const;
    Coord operator+ (const Coord& c) const;
    Coord operator* (const double d) const;
//    Coord operator*() const;
};

struct Line{
    Coord p1;
    Coord p2;
};
//typedef std::array<double, 2> Coord;
//typedef std::array<Coord, 2>  Line;

bool getIntersection(const Line &line1, const Line& line2, Coord* result);

// По двум диаганальным вершинам вычислить третюю и четвертую вершину
// прямоугольника, наклоненного на угол (angle) в радианах
void getRectVertex(Coord pt1, Coord pt2, double angle,
                   Coord* ptIntersect1, Coord* ptIntersect2);


} // namespace Geom2D

#endif // GEOM_H

