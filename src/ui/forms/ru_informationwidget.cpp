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

#include "ru_informationwidget.h"
#include "ui_ru_informationwidget.h"

RU_InformationWidget::RU_InformationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RU_InformationWidget)
{
    setObjectName("InformationWidget");
    ui->setupUi(this);

    ui->lInfo->setText("RU_InformationWidget [!!! TEST !!!]");
}

RU_InformationWidget::~RU_InformationWidget()
{
    delete ui;
}

void RU_InformationWidget::setInformation(const QString &strInfo)
{
    ui->lInfo->setText(strInfo);
}
