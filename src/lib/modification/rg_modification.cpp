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

#include "rg_modification.h"

#include "rl_debug.h"
#include "rg_vector.h"
#include "rg_entitycontainer.h"
#include "rg_graphicview.h"
#include "rg_document.h"

RG_Modification::RG_Modification(RG_EntityContainer *container, RG_GraphicView* graphicView)
    : container(container)
    , graphicView(graphicView)
{
    document = container->getDocument();
    if (!document) {
        RL_DEBUG << "RG_Modification::RG_Modification() ERROR: RG_Document is not find";
        qFatal("RG_Modification::RG_Modification() ERROR: RG_Document is not find");
    }
}

void RG_Modification::moveRef(const RG_Vector &ref, const RG_Vector &offset)
{
    /*
    RG_EntityContainer addList;
    for (RG_Entity* en: container->getEntityList()) {
        if (en->isSelected()) {
            RG_Entity* en_copy = en->clone();
            en_copy->moveRef(ref, offset);
            en_copy->setSelected(false);
            addList.addEntity(en_copy);
        }
    }
    */
}

void RG_Modification::moveRef(const RG_MoveRefData &data)
{
    std::vector<RG_Entity*> addList;

    for (RG_Entity* en: container->getEntityList()) {
        if (en->isSelected()) {
            RG_Entity* en_copy = en->clone();
            en_copy->moveRef(data.ref, data.offset);
            //en_copy->setSelected(false);
            addList.push_back(en_copy);
        }
    }
    applyModification(addList);
}

void RG_Modification::moveFace(const RG_MoveFaceData &data)
{
/*
    std::vector<RG_Entity*> addList;

    for (RG_Entity* en: container->getEntityList()) {
        if (en->isSelected()) {
            RG_Entity* en_copy = en->clone();
            en_copy->moveFace(data.marker, data.offset);
            //en_copy->setSelected(false);
            addList.push_back(en_copy);
        }
    }
*/
    if (data.marker.entity->isSelected()) {
        RG_Entity* en_copy = data.marker.entity->clone();
        en_copy->moveFace(data.marker, data.offset);
        applyModification(data.marker.entity, en_copy);
    }
}

void RG_Modification::move(const RG_MovingData &data)
{
    std::vector<RG_Entity*> addList;

    for (RG_Entity* en: container->getEntityList()) {
        if (en->isSelected()) {
            RG_Entity* en_copy = en->clone();
            en_copy->move(data.offset);
            //en_copy->setSelected(false);
            addList.push_back(en_copy);
        }
    }
    applyModification(addList);
}

void RG_Modification::applyModification(std::vector<RG_Entity *> &list)
{
    document->beginUndoGroup();
    deselectOriginals();
    addNewEntities(list);
    document->endUndoGroup();
    graphicView->redraw(RG::RedrawDrawing);
}

void RG_Modification::applyModification(RG_Entity* oldEntity, RG_Entity* newEntity)
{
    document->beginUndoGroup();
    oldEntity->setSelected(false);
    oldEntity->changeUndoState();
    document->addUndoable(oldEntity);
    container->addEntity(newEntity);
    document->addUndoable(newEntity);
    document->endUndoGroup();
    graphicView->redraw(RG::RedrawDrawing);
}

void RG_Modification::deselectOriginals()
{
    for (RG_Entity* en: container->getEntityList()) {
        if (en->isSelected()) {
            en->setSelected(false);
            en->changeUndoState();
            document->addUndoable(en);
        }
    }
}

void RG_Modification::addNewEntities(std::vector<RG_Entity *> &list)
{
    for (RG_Entity* en: list) {
        container->addEntity(en);
        document->addUndoable(en);
    }
}
