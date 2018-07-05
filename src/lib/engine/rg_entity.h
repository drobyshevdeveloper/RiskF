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

#ifndef RG_ENTITY_H
#define RG_ENTITY_H

#include "rg.h"
#include "rg_undoable.h"
#include "rg_vector.h"
#include "rg_marker.h"

class RG_EntityContainer;
class RG_Graphic;
class RG_Painter;
class RG_GraphicView;

class RG_Entity : public RG_Undoable
{
public:
    RG_Entity(RG_EntityContainer* parent);
    virtual ~RG_Entity();

    virtual RG::EntityType rtti() const {return RG::EntityUnknow;}
    virtual bool isContainer() const = 0;

    virtual void setSelected(bool select);
    virtual bool isSelected() const;
    virtual void toggleSelect();

    virtual bool isVisible() const;
    virtual void setVisible(bool v);



    /**
     * @brief getNearestPointOnEntity Определяет расстояние от заданной точки до сущности
     * @param coord - заданная точка
     * @param dist  - указатель на переменную в которую будет записано вычисленное расстояние
     * @return - возвращает координаты точки сущности, ближайшей к заданной точке
     */
    virtual RG_Vector getNearestPointOnEntity(const RG_Vector& coord,
                                              double* dist) const = 0;

    /**
     * @brief isClickSelectedRef
     * Определяет находится ли заданная точка внутри маркера (точки-указателя)
     * @param coord - заданная точка
     * @param marker - после выполнения метода заполняет описание найденного маркера
     * по переданному указателю на такой описатель
     * @return - true - маркер найден
     *           false - маркер не найден
     */
    virtual RG_Marker getNearestSelectedRef(const RG_Vector& coord) const;

    /**
     * @brief getDistanceToPoint - определяет расстояние от заданной точки до сущности
     * @param coord - заданная точка
     * @param entity - после выполнения метода заполняет указателем на сущность
     *                 (в данном случае на саму себя, при использовании данного метода для
     *                  контейнера сущностей заполняет указателем на сущность к которой ближе всех
     *                  заданная точка)
     * @return - расстояние до заданной точки
     */
    virtual double getDistanceToPoint(const RG_Vector& coord, RG_Entity **entity = nullptr) const;

    /**
     * @brief isInWindow
     * Определяет находится ли сущность внутри заданной прямоугольной области
     * @param v1 - первый угол прямоугольной области
     * @param v2 - второй угол прямоугольной области
     * @return true - если сущность находится внутри прямоугольной области
     */
    virtual bool isInWindow(RG_Vector v1, RG_Vector v2);
    /**
     * @brief isInCrossWindow
     * Определяет находится ли сущьность частично внутри заданной прямоугольной области
     * @param v1 - первый угол прямоугольной области
     * @param v2 - второй угол прямоугольной области
     * @return true - если сущность частично находится внутри прямоугольной области
     */
//    virtual bool isInCrossWindow(RG_Vector v1, RG_Vector v2) = 0;

    virtual void draw(RG_Painter* painter, RG_GraphicView* view) = 0;

    virtual void moveRef(RG_Marker& marker, const RG_Vector& offset) {};

    RG_Graphic* getGraphic() const;

    virtual RG_Vector getStartPoint() const;
    virtual RG_Vector getEndPoint() const;
    RG_Vector getMin() const {return vMin;}
    RG_Vector getMax() const {return vMax;}
    /**
     * @brief getRefPoints
     * Возвращает список ключевых точек сущности
     * @return
     */
    virtual RG_VectorSolutions getRefPoints() const;

    /**
     * @brief calculateBorders
     * Вычисляет координаты прямоугольной области, которая ограничивает сущность
     * и записывает результат в vMin, vMax
     */
    virtual void calculateBorders() = 0;
    void resetBorders();

protected: void initID();

protected:
    RG_EntityContainer* parent = nullptr;
    unsigned long int id;

    RG_Vector vMin; /// Первый угол прямоугольника, ограничивающего сущность
    RG_Vector vMax; /// Второй угол прямоугольника, ограничивающего сущность

    bool bSelected;
    bool bVisible;


};

#endif // RG_ENTITY_H
