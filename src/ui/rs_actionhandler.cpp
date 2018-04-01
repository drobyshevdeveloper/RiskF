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
#include "rg_actiondrawline.h"

RS_ActionHandler::RS_ActionHandler(QObject *parent)
    : QObject(parent)
{

}

RG_ActionInterface* RS_ActionHandler::setCurrentAction(RG::ActionType a_type)
{
    RG_ActionInterface* a = nullptr;

    switch (a_type) {
    case: RG::ActionDrawLine:
            auto a = new RG_ActionDrawLine(this->)

            break;
    }
}

void RS_ActionHandler::setView(RG_GraphicView *graphicView)
{
    this->graphicView = graphicView;
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
