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

#ifndef RG_GRAPHIC_H
#define RG_GRAPHIC_H

#include "rg_document.h"

class RG_Graphic : public RG_Document
{
public:
    RG_Graphic(RG_EntityContainer* parent = nullptr);
    virtual ~RG_Graphic();

    virtual RG::EntityType rtti() {return RG::EntityGraphic;}
    virtual void newDoc();


};

#endif // RG_GRAPHIC_H
