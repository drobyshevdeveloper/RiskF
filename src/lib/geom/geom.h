#ifndef GEOM_H
#define GEOM_H

#include <array>

/**
 * Библиотека двумерной геометрии
 */
namespace Geom2D {

//constexpr double EPSILON = e-10;

struct Coord{
    double x;
    double y;
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

} // namespace Geom2D

#endif // GEOM_H

