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

#include "ru_coordinatewidget.h"

#include <QString>

#include "rg_vector.h"

RU_CoordinateWidget::RU_CoordinateWidget(QWidget *parent, Qt::WindowFlags fl)
    : QWidget(parent, fl)
{
    setObjectName("CoordinateWidget");
    setupUi(this);

    lCoord1->setText("---");
    lCoord1a->setText("---");

}

RU_CoordinateWidget::~RU_CoordinateWidget()
{
    // Необходимо для Q_OBJECT
}

void RU_CoordinateWidget::setCoordinate(const RG_Vector &coord1, const RG_Vector &coord2)
{
    QString str1;
    str1 = "X=" + QString::number(coord1.x) +
           "; Y=" + QString::number(coord1.y);
    lCoord1->setText(str1);
    QString str2;
    str2 = "X=" + QString::number(coord2.x) +
           "; Y=" + QString::number(coord2.y);
    lCoord1a->setText(str2);

}
