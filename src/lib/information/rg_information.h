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

#ifndef RG_INFORMATION_H
#define RG_INFORMATION_H

#include <vector>

#include "rg_vector.h"

class RG_Entity;
class RG_Line;


/**
 * @brief The RG_Information class
 * Класс, предоставляющий информацию о сущностях,
 * например, о взаимном расположении двух сущностей
 */
class RG_Information
{
public:
    RG_Information();

    /**
     * @brief getIntersection
     * Определяет точки пересечения двух сущностей
     * @param e1
     * @param e2
     * @return возвращает массив точек пересечения, если массив пустой - точек пересечения нет
     */
    //    static std::vector<RG_Vector> getIntersection(RG_Entity const* e1,
    //                                                  RG_Entity const* e2);
    static RG_VectorSolutions getIntersection(RG_Entity const* e1,
                                              RG_Entity const* e2);
    /**
     * @brief getIntersectionLineLine
     * Определяет точку пересечения двух линий, если точки пересечения нет
     * возвращает RG_Vector(false)
     * @param l1
     * @param l2
     * @return
     */
    static RG_Vector getIntersectionLineLine(const RG_Line* l1,
                                             const RG_Line* l2);

    /**
     * @brief getNearestPointOnLine
     * Определяет ближайшую точку от заданной (coord), лежащей на прямой, определенной двумя точками (p1,p2)
     * Ближайшей точкой будет перпендикуляр, опущеный из заданной точки на прямую
     * @param coord
     * @param p1
     * @param p2
     * @param dist - указатель на double для получения расстояния от заданной точки (coord) до вычисленной (return)
     * @return - найденая точка
     */
    static RG_Vector getNearestPointOnLine(const RG_Vector &coord,
                                           const RG_Vector &p1,
                                           const RG_Vector &p2,
                                           double *dist);

    /**
     * @brief getNearestPointOnLineSegment
     * Определяет ближайшую точку от заданной (coord), лежащей на отрезке, определенном двумя точками (p1,p2)
     * @param coord
     * @param p1
     * @param p2
     * @param dist - указатель на double для получения расстояния от заданной точки (coord) до вычисленной (return)
     * Если найденая точка
     * @return
     */
    static RG_Vector getNearestPointOnLineSegment(const RG_Vector &coord,
                                                  const RG_Vector &p1,
                                                  const RG_Vector &p2,
                                                  double *dist);

    /**
     * @brief isPointInPolygon
     * Определяет находится ли заданная точка (pt) внутри замкнутого многоугольника
     * заданного списком векторов (vs)
     * @param pt
     * @param vs
     * @return
     */
    static bool isPointInPolygon(const RG_Vector& pt,
                                 RG_VectorSolutions &vs);
    /**
     * @brief isPointUnderLine
     * Определяет находится ли точка (pt) под/на заданной линии (p1,p2)
     * @param pt
     * @param l1
     * @param l2
     * @return
     */
    static bool isPointUnderLine(const RG_Vector& pt,
                                 const RG_Vector& l1,
                                 const RG_Vector& l2);
};

#endif // RG_INFORMATION_H
