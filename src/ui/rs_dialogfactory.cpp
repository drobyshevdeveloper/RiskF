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

#include "rs_dialogfactory.h"

#include "ru_coordinatewidget.h"
#include "ru_informationwidget.h"

RS_DialogFactory::RS_DialogFactory(QWidget *parent, QToolBar *ow)
    : RL_DialogFactoryInterface()
{
    coordinateWidget = nullptr;
    informationWidget = nullptr;
}

void RS_DialogFactory::updateCoordinateWidget(const RG_Vector &coord1, const RG_Vector &coord2)
{
    if (coordinateWidget) {
        coordinateWidget->setCoordinate(coord1, coord2);
    }
}

void RS_DialogFactory::setCoordinateWidget(RU_CoordinateWidget *cw)
{
    coordinateWidget = cw;
}

void RS_DialogFactory::setInformationWidget(RU_InformationWidget *iw)
{
    informationWidget = iw;
}

void RS_DialogFactory::updateInformationWidget(const QString &strInfo)
{
    if (informationWidget) {
        informationWidget->setInformation(strInfo);
    }
}
