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

#include "rg_pen.h"

RG_Pen::RG_Pen()
{

}

void RG_Pen::setWidth(double w)
{
    width = w;
}

double RG_Pen::getWidth() const
{
    return width;
}

void RG_Pen::setColor(const QColor &c)
{
    color = c;
}

const QColor &RG_Pen::getColor() const
{
    return color;
}
