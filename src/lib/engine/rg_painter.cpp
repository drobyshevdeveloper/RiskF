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

#include "rg_painter.h"

RG_Painter::RG_Painter()
{
    setDrawSelectOnlyMode(false);
}

void RG_Painter::setDrawSelectOnlyMode(bool smode)
{
    bDrawSelectOnlyMode = smode;
}

bool RG_Painter::getDrawSelectOnlyMode()
{
    return bDrawSelectOnlyMode;
}
