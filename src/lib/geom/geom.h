#ifndef GEOM_H
#define GEOM_H

#include <array>
#include <cmath>

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

constexpr double EPSILON = +1.0E-10;
//IMPL: NearConcept
inline bool are_near(double a, double b, double eps=EPSILON) { return fabs(a-b) <= eps; }
inline double sqr(double a) {return a * a;}

struct Coord{
    Coord() {x=0.0;y=0.0;}
    Coord(double x, double y);
    double x;
    double y;
//    double x() {return x;}
//    double y() {return y;}
//    void setX(double x_) {this->x = x_;}
//    void setY(double y_) {this->y = y_;}
    double length();
    double distanceTo(const Coord& c);
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

/**
 * @brief The LineABC class
 * Класс линии, заданной параметрическим уравнением прямой Ax+By+C=0
 */
class LineABC;
class LineABC {
public:
    LineABC();
    // Конструктор линии по точке и углу наклона в радианах
    LineABC (const Coord& point, double angle);
    // Конструктор линии по двум точкам
    LineABC (const Coord& pt1, const Coord& pt2 );

    // установить линию перпендикулярно заданной, проходящую через заданную точку
    void setPerpendicular(const LineABC& line, const Coord& point);
    // Установить линию параллельно заданной, проходящей через заданную точку
    void setParallel(const LineABC& line, const Coord& point);

    // Проверить горизонтальная-ли линия
    bool isHorz() const {return are_near( B_, 0.0 );}
    // Проверить вертикальная-ли линия
    bool isVert() const {return are_near( A_, 0.0 );}
    // Вернуть коэффициенты
    double A() const {return A_;}
    double B() const {return B_;}
    double C() const {return C_;}
    // Установить коэффициенты А B C
    void setABC (double A, double B, double C);

    // Возвращает точку пересечения прямой с указанной прямой
    bool computeIntersect(const LineABC& line, Coord *point);
    // Возвращает расстояние от указанной точки до прямой
    double distance(Coord point) {return point.distanceTo(computeProjection(point));}
    // Возвращает точку проекции указаной точки на прямую
    Coord computeProjection(const Coord& point);
    // Возвращает точку, лежащую на прямой на расстоянии (l) от
    // проекции на данную прямую заданной точки (point) в заданном направлении (dir)
    Coord computeSection(double l, const Coord& point, int dir);

private:
    double A_;  // Коэффициенты уравнения прямой Ax+By+C=0
    double B_;
    double C_;
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

