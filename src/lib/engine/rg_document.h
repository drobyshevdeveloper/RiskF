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

#ifndef RG_DOCUMENT_H
#define RG_DOCUMENT_H

#include "rg_entitycontainer.h"
#include "rg_undo.h"

class RG_Document : public RG_EntityContainer, public RG_Undo
{
public:
    RG_Document(RG_EntityContainer* parent);
    virtual ~RG_Document();

    bool isDocument() const override {return true;}
    virtual void removeUndoable(RG_Undoable* u);
    virtual void newDoc() = 0;

};

#endif // RG_DOCUMENT_H
