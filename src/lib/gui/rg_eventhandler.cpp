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
    defaultAction = nullptr;
}

RG_EventHandler::~RG_EventHandler()
{
    for (auto a: currentActions) {
        delete a;
    }

    currentActions.clear();

    if (defaultAction) delete defaultAction;
}

void RG_EventHandler::setCurrentAction(RG_ActionInterface *action)
{
    if (!action) {
        return;
    }

    currentActions.append(action);

    action->init();

    cleanUp();
}

void RG_EventHandler::setDefaultAction(RG_ActionInterface *action)
{
    if (action) defaultAction = action;
}

void RG_EventHandler::onChangedAction()
{
    cleanUp();
    if (hasAction()) {
        currentActions.last()->resume();
    } else {
        defaultAction->resume();
    }
}

void RG_EventHandler::killAllActions()
{
    foreach (auto a, currentActions) {
        a->finish();
    }

    defaultAction->init();
}

void RG_EventHandler::cleanUp()
{
    for (auto it=currentActions.begin(); it != currentActions.end();)
    {
        if( (*it)->isFinished())
        {
            delete *it;
            it = currentActions.erase(it);
        }else{
            ++it;
        }
    }

    if (hasAction()) {
        currentActions.last()->resume();
    }
}

bool RG_EventHandler::hasAction()
{
    if (currentActions.empty()) {
        // Действия отсутствуют
        return false;
    }
    if (!currentActions.last()->isFinished()) {
        // Имеется активное действие
        return true;
    }
    // Проверим цепочку действий и удалим завершенные
    cleanUp(); // в данном методе вызывается hasAction, но зацикливания не произойдет
               // т.к. второй вызов hasAction не дойдет до сюда
               // потому что cleanUp либо очищает контейнер полностью (и первый return сработает)
               // либо последнее действие будет активным (сработает второй return)

    // Проверим наличие активных действий
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
    else if (defaultAction) {
        defaultAction->mouseMoveEvent(e);
    }

    RL_DEBUG << "RG_EventHandler::mouseMoveEvent Ok";
}

void RG_EventHandler::mousePressEvent(QMouseEvent *e)
{
    RL_DEBUG << "RG_EventHandler::mousePressEvent Begin";
    RL_DEBUG << "QMouseEvent =" << e;
    RL_DEBUG << "e->modifiers() =" << e->modifiers();

    if (hasAction()) {
        currentActions.last()->mousePressEvent(e);
    }
    else if (defaultAction) {
        defaultAction->mousePressEvent(e);
    }

    RL_DEBUG << "RG_EventHandler::mousePressEvent Ok";
}

void RG_EventHandler::mouseReleaseEvent(QMouseEvent *e)
{
    RL_DEBUG << "RG_EventHandler::mouseReleaseEvent Begin";

    if (hasAction()) {
        currentActions.last()->mouseReleaseEvent(e);
    }
    else if (defaultAction) {
        defaultAction->mouseReleaseEvent(e);
    }

    RL_DEBUG << "RG_EventHandler::mouseReleaseEvent Ok";
}

void RG_EventHandler::keyPressEvent(QKeyEvent *e)
{
    RL_DEBUG << "RG_EventHandler::keyPressEvent() Begin";

    if (hasAction()) {
        currentActions.last()->keyPressEvent(e);
    }
    else if (defaultAction) {
        defaultAction->keyPressEvent(e);
    }

    RL_DEBUG << "RG_EventHandler::keyPressEvent() Ok";
}

void RG_EventHandler::keyReleaseEvent(QKeyEvent *e)
{
    RL_DEBUG << "RG_EventHandler::keyReleaseEvent() Begin";

    if (hasAction()) {
        currentActions.last()->keyReleaseEvent(e);
    }
    else if (defaultAction) {
        defaultAction->keyReleaseEvent(e);
    }

    RL_DEBUG << "RG_EventHandler::keyReleaseEvent() Ok";
}
void RG_EventHandler::leaveEvent(QEvent *e)
{
    if (hasAction()) {
        currentActions.last()->deleteSnapper();
    } else if (defaultAction) {
        defaultAction->deleteSnapper();
    }
}
