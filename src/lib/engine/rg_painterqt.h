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

#ifndef RG_PAINTERQT_H
#define RG_PAINTERQT_H

#include <qpainter.h>
#include "rg_painter.h"

class RG_PainterQt : public QPainter, public RG_Painter
{
public:
    RG_PainterQt();

    virtual void drawLine(const RG_Vector& p1, const RG_Vector& p2);

};

#endif // RG_PAINTERQT_H
