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

#include "rg_line.h"
#include "rg_painter.h"
#include "rg_graphicview.h"

RG_Line::RG_Line(RG_EntityContainer *parent)
    : RG_AtomicEntity(parent)
{

}

RG_Line::RG_Line(RG_EntityContainer *parent, const RG_LineData &d)
    : RG_AtomicEntity(parent), data(d)
{

}


void RG_Line::draw(RG_Painter *painter, RG_GraphicView *view)
{
    if ( !(painter && view) ) {
        return;
    }


}
