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

#include "rg_previewactioninterface.h"

RG_PreviewActionInterface::RG_PreviewActionInterface(const char* name,
                                                     RG_EntityContainer &container,
                                                     RG_GraphicView &graphicView)
    : RG_ActionInterface(name, container, graphicView)
{

}

RG_PreviewActionInterface::~RG_PreviewActionInterface()
{

}
