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

#include "rg_eventhandler.h"

RG_EventHandler::RG_EventHandler(QObject *parent)
    : QObject(parent)
{
    currentAction.clear();
}

RG_EventHandler::~RG_EventHandler()
{
    for (auto a: currentAction) {
        delete a;
    }

    currentAction.clear();
}

void RG_EventHandler::setCurrentAction(RG_ActionInterface *action)
{
    if (!action) {
        return;
    }

    currentAction.append(action);
}
