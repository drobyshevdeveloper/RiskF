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

#ifndef RG_ENTITYCONTAINER_H
#define RG_ENTITYCONTAINER_H

#include <QList>

#include "rg_entity.h"

class RG_EntityContainer;

class RG_EntityContainer : public RG_Entity
{
public:
    RG_EntityContainer(RG_EntityContainer* parent, bool owner = true);
    virtual ~RG_EntityContainer();

    virtual RG_Entity* clone();

    virtual RG::EntityType rtti() const override{return RG::EntityContainer;}
    virtual bool isContainer() const override {return true;}
    bool isOwner() const {return owner;}
    void setOwner(bool owner);
    virtual void setSelected(bool select) override;
    virtual void selectWindow(RG_Vector v1, RG_Vector v2,
                              bool select, bool cross);



    virtual void addEntity(RG_Entity* entity);
    void removeEntity(RG_Entity* entity);
    const QList<RG_Entity*> getEntityList();

    virtual RG_Vector getNearestPointOnEntity(const RG_Vector& coord,
                                              double* dist) const override;
    /**
     * @brief getNearestEntity - Поиск ближайшей от заданной точки сущности
     * @param coord - заданная точка
     * @param dist  - указатель на переменную в которую будет возвращено расстояние от заданной точки до сущности
     * @return - возвращает указатель на ближайшую к заданной точке сущность
     */
    RG_Entity* getNearestEntity(const RG_Vector& coord,
                                double* dist) const;
    virtual RG_Marker getNearestSelectedRef(const RG_Vector& coord) const override;
    virtual double getDistanceToPoint(const RG_Vector &coord,
                                      RG_Entity **entity) const override;

    virtual void clear();
    virtual void draw(RG_Painter* painter, RG_GraphicView* view) override;
    virtual void moveRef(const RG_Vector& ref, const RG_Vector& offset) override;
    virtual void moveFace(const RG_Marker& marker, const RG_Vector& offset) override;
    virtual void moveFace(const RG_Vector& ref, const RG_Vector& offset) override;
    virtual void move(const RG_Vector &offset) override;

    virtual void calculateBorders() override;
    void adjustBorders(const RG_Entity* e);

protected:
    QList<RG_Entity*> entities;

private:
    /**
     * @brief owner - флаг является ли кнтейнер владельцем элементов
     */
    bool owner;

};

#endif // RG_ENTITYCONTAINER_H
