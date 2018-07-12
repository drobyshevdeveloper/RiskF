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

#include "rg_vector.h"
#include "rg_entitycontainer.h"
#include "rg_graphicview.h"

RG_Modification::RG_Modification(RG_EntityContainer *container, RG_GraphicView* graphicView)
    : container(container)
    , graphicView(graphicView)
{

}

void RG_Modification::moveRef(const RG_Vector &ref, const RG_Vector &offset)
{

}
