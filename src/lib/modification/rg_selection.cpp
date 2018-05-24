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

void RG_Selection::selectAll(bool select)
{
    foreach (RG_Entity* e, container->getEntityList()) {
        e->setSelected(select);
    }

    if (graphicView) {
        graphicView->redraw();
    }
}
