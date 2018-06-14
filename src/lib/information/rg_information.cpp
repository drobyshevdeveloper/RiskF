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
    if (e1->rtti()==RG::EntityLine && e2->rtti()==RG::EntityLine) {
        RG_Vector ret2 = getIntersectionLineLine((RG_Line*)e1, (RG_Line*)e2);
        if (ret2.valid) {
            ret.push_Back(ret2);
        }
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
