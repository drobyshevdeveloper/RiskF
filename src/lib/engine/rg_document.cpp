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

#include "rg_document.h"

RG_Document::RG_Document(RG_EntityContainer *parent)
    : RG_EntityContainer(parent)
{

}

RG_Document::~RG_Document()
{

}

void RG_Document::removeUndoable(RG_Undoable *u)
{
    if (u) {
        removeEntity((RG_Entity*)u);
    }
}
