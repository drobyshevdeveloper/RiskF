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

#ifndef RG_POLYGON_H
#define RG_POLYGON_H

#include "rg_atomicentity.h"
#include "rg_vector.h"


struct RG_PolygonData {
    RG_VectorSolutions vertexes;
    double angle=0;
};

/**
 * @brief The RG_Polygon class
 * Класс многоугольника - базовый класс для различных элементов документа
 * Данный примитив может быть как правильным прямогольником, повернутым на любой угол,
 * так и любым многоугольником, тип примитива определяется методом isRect(),
 * который возвращает true, если примитив является прямоугольником
 *                    false, если примитив является многоугольником
 * Прямоугольник может быть преобразован в многоугольник, если виртуальны метод
 * isCanByPolygon() возвращает true, который может быть перегружен
 * Многоугольник не может быть преобразован в прямоугольник
 */
class RG_Polygon : public RG_AtomicEntity
{
public:
    RG_Polygon(RG_EntityContainer* parent);
    RG_Polygon(RG_EntityContainer *parent,
               const RG_PolygonData &d,
               bool isRect);

    virtual RG_Entity* clone() override;

    virtual RG::EntityType rtti() const override {
        return RG::EntityPolygon;
    }

    // Возвращает true, если примитив является прямоугольником
    bool isRect() const {return fRect;}
    // Возвращает ширину примитива, если он является прямоугольником
    double getWidth();
    // Возвращает высоту примитива, если он является прямоугольником
    double getHeight();
    // Возможно-ли преобразовать примитив в многоугольник
    virtual bool isCanByPolygon() {return true;}

    virtual RG_Vector getNearestPointOnEntity(const RG_Vector &coord,
                                              double *dist) const override;

//    virtual void calculateBorders() override;

    virtual void draw(RG_Painter* painter, RG_GraphicView* view) override;
    virtual void moveRef(const RG_Vector& ref, const RG_Vector& offset) override;
    virtual void moveFace(const RG_Vector& ref, const RG_Vector& offset) override;
    virtual void move(const RG_Vector &offset) override;
    virtual void rotate(const RG_Vector& ptBase, const RG_Vector& ptAngle);
    void moveVertex(int index, const RG_Vector &offset, RG_VectorSolutions& vs);
    virtual void addVertex(const RG_Vector& coord, int index) override;
    virtual void delVertex(const RG_Vector& coord) override;

    virtual RG_VectorSolutions getRefPoints() const override;

protected:
    /**
     * @brief transformToPolygon
     * Преобразует прямоугольник в многоугольник, если это возможно
     */
    void transformToPolygon();

protected:
    RG_PolygonData data;
private:
    bool fRect;
};

#endif // RG_POLYGON_H
