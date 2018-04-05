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

#ifndef RG_PREVIEW_H
#define RG_PREVIEW_H

#include "rg_entitycontainer.h"

class RG_Preview : RG_EntityContainer
{
public:
    RG_Preview(RG_EntityContainer* parent);

    virtual ~RG_Preview();

    virtual void addEntity(RG_Entity* entity) override;
};

#endif // RG_PREVIEW_H
