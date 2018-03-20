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

#include "rs_actionhandler.h"

#include "rl_debug.h"

RS_ActionHandler::RS_ActionHandler(QObject *parent)
    : QObject(parent)
{

}

// ==========================================
// === Insert ===
void RS_ActionHandler::slotInsertLine()
{
    RL_DEBUG << "RS_ActionHandler::slotInsertLine() Begin";

    RL_DEBUG << "RS_ActionHandler::slotInsertLine() Ok";
}

void RS_ActionHandler::slotInsertRoom()
{
    RL_DEBUG << "RS_ActionHandler::slotInsertRoom() Begin";

    RL_DEBUG << "RS_ActionHandler::slotInsertRoom() Ok";
}