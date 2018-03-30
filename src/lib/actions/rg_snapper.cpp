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

#include "rg_snapper.h"

#include "rg_entitycontainer.h"
#include "rg_graphicview.h"

RG_Snapper::RG_Snapper(RG_EntityContainer *container, RG_GraphicView *graphicView)
{
    this->container = container;
    this->graphicView = graphicView;

}

RG_Snapper::~RG_Snapper()
{

}
