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

#ifndef RG_LINE_H
#define RG_LINE_H

#include "rg_atomicentity.h"


#include "rg_vector.h"

class RG_Line : RG_AtomicEntity
{
public:
    RG_Line(RG_EntityContainer* parent);

private:
    RG_Vector startPoint;
    RG_Vector endPoint;
};

#endif // RG_LINE_H
