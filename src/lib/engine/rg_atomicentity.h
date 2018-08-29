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

#ifndef RG_ATOMICENTITY_H
#define RG_ATOMICENTITY_H

#include "rg_entity.h"

class RG_AtomicEntity : public RG_Entity
{
public:
    RG_AtomicEntity(RG_EntityContainer* parent);

    virtual ~RG_AtomicEntity();

    virtual bool isContainer() const override {
        return false;
    }

    virtual void calculateBorders() override;

};

#endif // RG_ATOMICENTITY_H
