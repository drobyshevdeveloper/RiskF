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

#ifndef RG_PEN_H
#define RG_PEN_H

#include <QColor>

class RG_Pen
{
public:
    RG_Pen();

    void setWidth(double w);
    double getWidth() const;
    void setColor(const QColor& c);
    const QColor& getColor() const;

protected:
    double width;
    QColor color;
};

#endif // RG_PEN_H
