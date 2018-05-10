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

#include "rl_debug.h"
#include "rg_actioninterface.h"

RG_EventHandler::RG_EventHandler(QObject *parent)
    : QObject(parent)
{
    currentActions.clear();
}

RG_EventHandler::~RG_EventHandler()
{
    for (auto a: currentActions) {
        delete a;
    }

    currentActions.clear();
}

void RG_EventHandler::setCurrentAction(RG_ActionInterface *action)
{
    if (!action) {
        return;
    }

    currentActions.append(action);
}

bool RG_EventHandler::hasAction()
{
    foreach (RG_ActionInterface* a, currentActions) {
        if (!a->isFinished())
            return true;
    }
    return false;
}

void RG_EventHandler::mouseMoveEvent(QMouseEvent *e)
{
    RL_DEBUG << "RG_EventHandler::mouseMoveEvent Begin";

    if (hasAction()) {
        currentActions.last()->mouseMoveEvent(e);
    }

    RL_DEBUG << "RG_EventHandler::mouseMoveEvent Ok";
}

void RG_EventHandler::mousePressEvent(QMouseEvent *e)
{

}

void RG_EventHandler::mouseReleaseEvent(QMouseEvent *e)
{

}
