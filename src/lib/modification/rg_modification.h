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

#ifndef RG_MODIFICATION_H
#define RG_MODIFICATION_H

#include <vector>

#include "rg_vector.h"
#include "rg_marker.h"

class RG_Entity;
class RG_EntityContainer;
class RG_GraphicView;
class RG_Document;

class RG_MoveRefData
{
public:
    RG_Vector ref;
    RG_Vector offset;
};

class RG_MoveFaceData
{
public:
    RG_Marker marker;
    RG_Vector offset;
};

class RG_MovingData
{
public:
    RG_Vector offset;
};

struct RG_RotateData {
    RG_Vector ptBase;
    RG_Vector ptAngle;
};

struct RG_AddVertexData {
    RG_Marker marker;
    RG_Vector ptAddVertex;
};

struct RG_DelVertexData {
    RG_Marker marker;
    RG_Vector ptDelVertex;
};

class RG_Modification
{
public:
    RG_Modification(RG_EntityContainer* container, RG_GraphicView* graphicView);

    void moveRef(const RG_Vector& ref, const RG_Vector& offset);
    void moveRef(const RG_MoveRefData &data);
    void moveFace(const RG_MoveFaceData& data);
    void move(const RG_MovingData& data);
    void rotate(const RG_RotateData& data);
    void addVertex(const RG_AddVertexData& data);
    void delVertex(const RG_DelVertexData& data);
protected:
    /**
     * @brief applyModification
     * Применить изменения для группы выделенных сущностей
     * @param list
     */
    void applyModification(std::vector<RG_Entity*>& list);
    /**
     * @brief applyModification
     * Применить изменения для одного выделенной сущности
     * @param oldEntity
     * @param newEntity
     */
    void applyModification(RG_Entity *oldEntity, RG_Entity *newEntity);
    void deselectOriginals();
    void addNewEntities(std::vector<RG_Entity*>& list);

private:
    RG_EntityContainer* container;
    RG_GraphicView* graphicView;
    RG_Document* document;
};

#endif // RG_MODIFICATION_H
