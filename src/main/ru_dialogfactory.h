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

#ifndef RU_DIALOGFACTORY_H
#define RU_DIALOGFACTORY_H

#include "rs_dialogfactory.h"

class RU_DialogFactory : public RS_DialogFactory
{
public:
    RU_DialogFactory(QWidget* parent, QToolBar* ow);
};

#endif // RU_DIALOGFACTORY_H
