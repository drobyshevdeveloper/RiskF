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

#ifndef RS_CENTRALWIDGET_H
#define RS_CENTRALWIDGET_H

#include <QFrame>
#include <QMdiArea>

class RS_CentralWidget : public QFrame
{
public:
    RS_CentralWidget(QWidget* parent);
    QMdiArea* getMdiArea();

private:

    QMdiArea* mdi_area;
};

#endif // RS_CENTRALWIDGET_H
