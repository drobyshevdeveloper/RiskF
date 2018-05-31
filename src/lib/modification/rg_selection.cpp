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

#include "rg_selection.h"

#include "rg_entity.h"
#include "rg_entitycontainer.h"
#include "rg_graphicview.h"

RG_Selection::RG_Selection(RG_EntityContainer *container, RG_GraphicView *graphicView)
{
    this->container = container;
    this->graphicView = graphicView;
}

void RG_Selection::singleSelect(RG_Entity *entity)
{
    if (entity) {
        entity->toggleSelect();
    }
}

/**
 * @brief RG_Selection::selectWindow - выбирает или отменяет выбор сущности,
 * попавших в прямоугольную область выделения
 * @param v1 - первая точка прямоугольной области выделения
 * @param v2 - вторая точка прямоугольной точки выделения
 * @param select - true если необходимо выделить сущности, false если необходимо снять выделение
 * @param cross  - true выделить сущности полностью и частично попавшие в прямоугольную область выделения
 *                 false выделить сущности полностью поппавшие в прямоугольную область выделения
 */
void RG_Selection::selectWindow(RG_Vector v1, RG_Vector v2, bool select, bool cross)
{
    container->selectWindow(v1, v2, select, cross);

    if (graphicView) {
        graphicView->redraw();
    }
}

void RG_Selection::selectAll(bool select)
{
    foreach (RG_Entity* e, container->getEntityList()) {
        e->setSelected(select);
    }

    if (graphicView) {
        graphicView->redraw();
    }
}
