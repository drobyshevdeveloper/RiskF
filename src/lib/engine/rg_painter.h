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

#ifndef RG_PAINTER_H
#define RG_PAINTER_H

class RG_Vector;
class QPixmap;

class RG_Painter
{
public:
    RG_Painter();

    virtual void drawLine(const RG_Vector& p1, const RG_Vector& p2) = 0;
    virtual void drawPixmap(int x, int y, QPixmap* pixmap) = 0;
};

#endif // RG_PAINTER_H
