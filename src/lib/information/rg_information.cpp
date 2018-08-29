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

#include "rg_information.h"

#include <math.h>

#include "rl_debug.h"
#include "rg_entity.h"
#include "rg_line.h"
#include "rg_rectangle.h"
#include "rg_polygon.h"
#include "geom.h"

RG_Information::RG_Information()
{

}

RG_VectorSolutions RG_Information::getIntersection(RG_Entity const *e1, RG_Entity const *e2)
{
    RG_VectorSolutions ret;

    if (!(e1 && e2) ) {
        RL_DEBUG << "RG_Information::getIntersection() for nullptr entities";
        return ret;
    }
    // Line vs Line
    if (e1->rtti()==RG::EntityLine && e2->rtti()==RG::EntityLine) {
        RG_Vector ret2 = getIntersectionLineLine((RG_Line*)e1, (RG_Line*)e2);
        if (ret2.valid) {
            ret.push_Back(ret2);
        }
        return ret;
    }
    // Line vs Rectangle
    if (e1->rtti()==RG::EntityLine && e2->rtti()==RG::EntityRectangle) {
        return getIntersectionLineRectangle((RG_Line*)e1, (RG_Rectangle*)e2);
    }
    if (e2->rtti()==RG::EntityLine && e1->rtti()==RG::EntityRectangle) {
        return getIntersectionLineRectangle((RG_Line*)e2, (RG_Rectangle*)e1);
    }
    // Line vs Polygon
    if (e1->rtti()==RG::EntityLine && e2->rtti()==RG::EntityPolygon) {
        return getIntersectionLinePolygon((RG_Line*)e1, (RG_Polygon*)e2);
    }
    if (e2->rtti()==RG::EntityLine && e1->rtti()==RG::EntityPolygon) {
        return getIntersectionLinePolygon((RG_Line*)e2, (RG_Polygon*)e1);
    }
    return ret;
}

/**
 * @brief RG_Information::getIntersectionLineLine
 * Алгоритм подсмотрен тут: http://forum.algolist.ru/algorithm-geometry/2453-nahojdenie-tochki-peresecheniia-2-otrezkov.html
 * @param l1
 * @param l2
 * @return
 */
RG_Vector RG_Information::getIntersectionLineLine(const RG_Line* l1, const RG_Line* l2)
{
    using namespace Geom2D;
        Coord pt;
        bool res = Geom2D::getIntersection({{l1->getStartPoint().x,l1->getStartPoint().y},
                                    {l1->getEndPoint().x, l1->getEndPoint().y}},
                                   {{l2->getStartPoint().x,l2->getStartPoint().y},
                                    {l2->getEndPoint().x, l2->getEndPoint().y}},
                                   &pt);
        if (!res) return RG_Vector(false);
        return {pt.x,pt.y};


/*    RG_Vector ret;

    double x1 = l1->getStartPoint().x;
    double y1 = l1->getStartPoint().y;
    double x2 = l1->getEndPoint().x;
    double y2 = l1->getEndPoint().y;
    double x3 = l2->getStartPoint().x;
    double y3 = l2->getStartPoint().y;
    double x4 = l2->getEndPoint().x;
    double y4 = l2->getEndPoint().y;

    double	dx1 = x2 - x1;
    double	dy1 = y2 - y1;
    double	dx2 = x4 - x3;
    double	dy2 = y4 - y3;
        double x = dy1 * dx2 - dy2 * dx1;
        if(!x || !dx2)
            return RG_Vector(false);

    double y = x3 * y4 - y3 * x4;
    x = ((x1 * y2 - y1 * x2) * dx2 - y * dx1) / x;
    y = (dy2 * x - y) / dx2;

    ret.set(x, y);
    ret.valid = ((x1 <= x && x2 >= x) ||
                 (x2 <= x && x1 >= x)) &&
                ((x3 <= x && x4 >= x) ||
                 (x4 <= x && x3 >= x));
    return ret;*/
}

/**
 * @brief RG_Information::getIntersectionLineRectangle
 * Вычислить точки пересечения линии и прямоугольника
 * @param l
 * @param r
 * @return
 */
RG_VectorSolutions RG_Information::getIntersectionLineRectangle(const RG_Line* l,
                                                                const RG_Rectangle* r)
{
    RG_VectorSolutions vs;
    Geom2D::Coord pt;
    Geom2D::Line line = {{l->getStartPoint().x, l->getStartPoint().y},
                         {l->getEndPoint().x, l->getEndPoint().y}};
    RG_VectorSolutions rectPts = r->getRefPoints();

    for (int i=0; i<4; i++) {
        if (Geom2D::getIntersection(line,
                                    {{rectPts[i].x, rectPts[i].y},
                                     {rectPts[(i+1)%4].x, rectPts[(i+1)%4].y}},
                                    &pt))
        {
            vs.push_Back(RG_Vector(pt.x,pt.y));
        }
    }

    return vs;
}

RG_VectorSolutions RG_Information::getIntersectionLinePolygon(const RG_Line* l,
                                                              const RG_Polygon* p)
{
    RG_VectorSolutions vs;
    Geom2D::Coord pt;
    Geom2D::Line line = {{l->getStartPoint().x, l->getStartPoint().y},
                         {l->getEndPoint().x, l->getEndPoint().y}};
    RG_VectorSolutions polyPts = p->getRefPoints();

    for (int i=0; i<polyPts.count(); i++) {
        if (Geom2D::getIntersection(line,
                                    {{polyPts[i].x, polyPts[i].y},
                                     {polyPts[(i+1)%polyPts.count()].x, polyPts[(i+1)%polyPts.count()].y}},
                                    &pt))
        {
            vs.push_Back(RG_Vector(pt.x,pt.y));
        }
    }

    return vs;
}


RG_Vector RG_Information::getNearestPointOnLine(const RG_Vector &coord,
                                                const RG_Vector &p1,
                                                const RG_Vector &p2,
                                                double *dist)
{
    // Используем формулу: proj_b_to_a = a * dot(a, b)/dot(a,a) (dot - скалярное произведение векторов)
    // Преобразуем линию в вектор (a)
    RG_Vector direction = p2 - p1;
    // Квадрат длины вектора (dot(a,a))
    double len2 = direction.squared();
    // Преобразуем указанную точку в вектор (b)
    RG_Vector vct = coord - p1;
    // Найдем dot(a,b)/dot(a,a)
    double t = vct.dot(direction) / len2;
    // Умножим вектор линии на полученный t и перенесем на линию получив точку
    RG_Vector result = p1 + direction * t;
    if (dist) {
        *dist = coord.distanceTo(result);
    }
    return result;
}

RG_Vector RG_Information::getNearestPointOnLineSegment(const RG_Vector &coord,
                                                       const RG_Vector &p1,
                                                       const RG_Vector &p2,
                                                       double *dist)
{
    // Определим ближайшую точку на прямой
    RG_Vector result = getNearestPointOnLine(coord, p1, p2, dist);

    // Проверим, лежит ли точка в пределах указанного отрезка?
    if (!result.isInWindow(p1,p2)) {
        // Точка не лежит в пределах указанного отрезка
        // Вернем отрицательный результат
        if (dist) {
            *dist = RG_MAXDOUBLE;
        }
        return RG_Vector(false);
    }

    // Точка лежит в пределах указанного отрезка
    // Вернем полученный результат
    if (dist) {
        *dist = coord.distanceTo(result);
    }
    return result;
}

void RG_Information::calculateRectVertex(const RG_Vector& v1, const RG_Vector& v2,
                                         double angle,
                                         RG_Vector* v3, RG_Vector* v4)
{
    // вычислим вторые точки прямых, проходящих через v1 и лежащих на гранях
    // прямоугольника с общей вершиной v1
    RG_Vector v1_1 = v1 + RG_Vector(1000.0, 0.0).setAngle(angle);
    RG_Vector v1_2 = v1 + RG_Vector(1000.0, 0.0).setAngle(angle + M_PI_2);
    // Найдем точки пересечения нормалей из v2, опущенных на найденные прямые
    // (v1,v1_1) и (v1, v1_2)
    *v3 = getNearestPointOnLine(v2, v1, v1_1, nullptr);
    *v4 = getNearestPointOnLine(v2, v1, v1_2, nullptr);
}

bool RG_Information::isPointInPolygon(const RG_Vector &pt,
                                      RG_VectorSolutions &vs)
{
   int res = 0;
   for (int i=0; i<vs.count();i++) {
       if (isPointUnderLine(pt, vs[i], vs[(i+1) % vs.count()])) res++;
   }
   return res & 1;
}

// Функция определения совместного положения точки (pt)
// и линии (l1)-(l2)
// true  - Точка находиться на/под линией
// false - Точка не находиться под линией
bool RG_Information::isPointUnderLine(const RG_Vector& pt,
                                      const RG_Vector& l1,
                                      const RG_Vector& l2)
{
   // Последняя точка линии не в счет
   if (l2.isEquX(pt)) return false;

   // Введем рабочие переменные точки линии
   RG_Vector l1_ = l1;
   RG_Vector l2_ = l2;
   if (l1_.x>l2_.x) {
      // Поменять местами точки
       l1_ = l2;
       l2_ = l1;
   }

   if (pt.x<l1_.x || pt.x>l2_.x) return false; // Точка находится вне тени линии
   if (l1_.isEqu(l2_)) {
      // Тень от линии - точка
      if (std::min(l1_.y, l2_.y) > pt.y) return false;
      return true;
   }

   double k, b;
   k = (l2.y - l1_.y) / (l2_.x - l1_.x);
   b = l1_.y - k * l1_.x;

   double y = pt.x * k + b;
   if (y>pt.y) return false;
   return true;
}
