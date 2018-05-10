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

    virtual RG::EntityType rtti() const {
        return RG::EntityContainer;
    }
    virtual bool isContainer() const {
        return true;
    }
    bool isOwner() const {
        return owner;
    }
    void setOwner(bool owner);


    virtual void addEntity(RG_Entity* entity);
    const QList<RG_Entity*> getEntityList();

    virtual void clear();
    virtual void draw(RG_Painter* painter, RG_GraphicView* view) override;


protected:
    QList<RG_Entity*> entities;

private:
    /**
     * @brief owner - флаг является ли кнтейнер владельцем элементов
     */
    bool owner;

};

#endif // RG_ENTITYCONTAINER_H
