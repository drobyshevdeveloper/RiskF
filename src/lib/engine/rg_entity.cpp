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

#include "rg_entity.h"

#include "rg_graphic.h"

RG_Entity::RG_Entity(RG_EntityContainer *parent)
    : RG_Undoable()
{
    this->parent = parent;
    bSelected = false;
    bVisible = true;
    initID();
}

RG_Entity::~RG_Entity()
{

}

void RG_Entity::reparent(RG_EntityContainer *parent)
{
    this->parent = parent;
}

void RG_Entity::onChangeUndoState()
{
    setSelected(false);
}

void RG_Entity::initID()
{
    static unsigned long int idCounter = 0;
    id = ++idCounter;
}

void RG_Entity::setSelected(bool select)
{
    bSelected = select;
}

bool RG_Entity::isSelected() const
{
    return bSelected;
}

void RG_Entity::toggleSelect()
{
    setSelected(!isSelected());
}

bool RG_Entity::isVisible() const
{
    if (!bVisible) {
        return false;
    }

    if (isUndone()) {
        return false;
    }

    return true;
}

void RG_Entity::setVisible(bool v)
{
    bVisible = v;
}

/**
 * @brief RG_Entity::getGraphic - поиск объекта графического документа, которому принадлежить сущность
 * @return ссылку на объект документа, или nullptr
 */
RG_Graphic* RG_Entity::getGraphic() const
{
    if (rtti()==RG::EntityGraphic) {
        RG_Graphic const* ret=static_cast<RG_Graphic const*>(this);
        return const_cast<RG_Graphic*>(ret);
    } else if (!parent) {
        return nullptr;
    }
    return parent->getGraphic();
}

RG_Document* RG_Entity::getDocument() const
{
    if (isDocument()) {
        RG_Document const* ret=static_cast<RG_Document const*>(this);
        return const_cast<RG_Document*>(ret);
    }
    if (!parent) {
        return nullptr;
    }
    return parent->getDocument();
}

RG_Vector RG_Entity::getStartPoint() const
{
    return {};
}

RG_Vector RG_Entity::getEndPoint() const
{
    return {};
}

RG_Marker RG_Entity::getNearestSelectedRef(const RG_Vector &coord) const
{
    if (!isSelected()) {
        // Сущность не выделена, возвращаем пустой маркер
        return RG_Marker();
    }

    RG_Marker marker;
    marker.entity = (RG_Entity*)this;
    marker.dist = RG_MAXDOUBLE;
    double distRef;

    RG_VectorSolutions vs = getRefPoints();

    int i = 0;
    foreach (RG_Vector v, vs.getVector()) {
        distRef = v.distanceTo(coord);
        if (marker.dist > distRef) {
            marker.coord = v;
            marker.dist = distRef;
            marker.index = i;
            marker.valid = true;
        }
        i++;
    }

    return marker;
}

/**
 * @brief getDistanceToPoint - возвращает расстояние от заданной точки до сущности
 * @param coord - заданная точка
 * @param entity - после выполнения метода заполняет указателем на сущность
 *                 (в данном случае на саму себя, при использовании данного метода для
 *                  контейнера сущностей заполняет указателем на сущность к которой ближе всех
 *                  заданная точка)
 * @return
 */
double RG_Entity::getDistanceToPoint(const RG_Vector &coord, RG_Entity **entity) const
{
    double dist = RG_MAXDOUBLE;
    if (entity) {
        (*entity) = const_cast<RG_Entity*>(this);
    }
    if (!isVisible()) {
        return dist;
    }
    (void) getNearestPointOnEntity(coord, &dist);
    return dist;
}

bool RG_Entity::isInWindow(RG_Vector v1, RG_Vector v2)
{
    double left = std::min(v1.x, v2.x);
    double right = std::max(v1.x, v2.x);
    double top = std::min(v1.y, v2.y);
    double bottom = std::max(v1.y, v2.y);

    return (getMin().x >= left &&
            getMax().x <= right &&
            getMin().y >= top &&
            getMax().y <= bottom);
}

void RG_Entity::resetBorders()
{
    double dmax = RG_MAXDOUBLE;
    double dmin = RG_MINDOUBLE;
    vMin.set(dmax, dmax);
    vMax.set(dmin, dmin);
}

RG_VectorSolutions RG_Entity::getRefPoints() const
{
    return RG_VectorSolutions();
}

RG_Vector RG_Entity::getNearestPointOnLine(const RG_Vector &coord,
                                           const RG_Vector &p1,
                                           const RG_Vector &p2,
                                           double *dist) const
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
