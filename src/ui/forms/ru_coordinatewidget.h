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

#ifndef RU_COORDINATEWIDGET_H
#define RU_COORDINATEWIDGET_H

//#include <QWidget>
class RG_Vector;

#include "ui_ru_coordinatewidget.h"

class RU_CoordinateWidget : public QWidget, public Ui::RU_CoordinateWidget
{
    Q_OBJECT

public:
    RU_CoordinateWidget(QWidget* parent = 0, Qt::WindowFlags fl = {});
    ~RU_CoordinateWidget();

    void setCoordinate(const RG_Vector& coord1, const RG_Vector& coord2);
};

#endif // RU_COORDINATEWIDGET_H
