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
#include "rg_document.h"
#include "rg_graphicview.h"

RS_ActionHandler::RS_ActionHandler(QObject *parent)
    : QObject(parent)
{

}

RG_ActionInterface* RS_ActionHandler::setCurrentAction(RG::ActionType a_type)
{
    RG_ActionInterface* a = nullptr;

    switch (a_type) {
    case RG::ActionDefault:
        if (graphicView) {
            graphicView->killAllActions();
        }
        break;
    case RG::ActionDrawLine:
        a = new RG_ActionDrawLine(*document, *graphicView);

        break;
    }

    if (a) {
        graphicView->setCurrentAction(a);
    }

    return a;
}

void RS_ActionHandler::setView(RG_GraphicView *graphicView)
{
    this->graphicView = graphicView;
}

void RS_ActionHandler::setDocument(RG_Document *document)
{
    this->document = document;
}

// ==========================================
// === Insert ===
void RS_ActionHandler::slotInsertLine()
{
    RL_DEBUG << "RS_ActionHandler::slotInsertLine() Begin";
    setCurrentAction(RG::ActionDrawLine);
    RL_DEBUG << "RS_ActionHandler::slotInsertLine() Ok";
}

void RS_ActionHandler::slotInsertRoom()
{
    RL_DEBUG << "RS_ActionHandler::slotInsertRoom() Begin";

    RL_DEBUG << "RS_ActionHandler::slotInsertRoom() Ok";
}

// === Edit ===
void RS_ActionHandler::slotSelect()
{
    setCurrentAction(RG::ActionDefault);
}
