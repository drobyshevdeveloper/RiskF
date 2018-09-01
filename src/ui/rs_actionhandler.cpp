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
#include "rg_document.h"
#include "rg_graphicview.h"
#include "rg_actiondrawline.h"
#include "rg_actionundo.h"
#include "rg_actiondrawrectangle.h"
#include "rg_actiondrawpolygon.h"
#include "rg_actioneditrotate.h"
#include "rg_actioneditaddvertex.h"

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
    case RG::ActionEditRotate:
        a = new RG_ActionEditRotate(*document, *graphicView);
        break;
    case RG::ActionDrawLine:
        a = new RG_ActionDrawLine(*document, *graphicView);
        break;

    case RG::ActionUndo:
        a = new RG_ActionUndo(*document, *graphicView, true);
        break;

    case RG::ActionRedo:
        a = new RG_ActionUndo(*document, *graphicView, false);
        break;

    case RG::ActionDrawRectangle:
//        a = new RG_ActionDrawRectangle(*document, *graphicView);
        a = new RG_ActionDrawPolygon(*document, *graphicView, true);
        break;
    case RG::ActionDrawPolygon:
        a = new RG_ActionDrawPolygon(*document, *graphicView, false);
        break;
    case RG::ActionEditAddVertex:
        a = new RG_ActionEditAddVertex(*document, *graphicView);
        break;
    case RG::ActionEditDelVertex:
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
    setCurrentAction(RG::ActionDrawRectangle);
    RL_DEBUG << "RS_ActionHandler::slotInsertRoom() Ok";
}

void RS_ActionHandler::slotInsertRectangle()
{
    RL_DEBUG << "RS_ActionHandler::slotInsertRectangle() Begin";
    setCurrentAction(RG::ActionDrawRectangle);
    RL_DEBUG << "RS_ActionHandler::slotInsertRectangle() Ok";
}

void RS_ActionHandler::slotInsertPolygon()
{
    RL_DEBUG << "RS_ActionHandler::slotInsertPolygon() Begin";
    setCurrentAction(RG::ActionDrawPolygon);
    RL_DEBUG << "RS_ActionHandler::slotInsertPolygon() Ok";
}

// === Edit ===
void RS_ActionHandler::slotSelect()
{
    setCurrentAction(RG::ActionDefault);
}

void RS_ActionHandler::slotEditRotate()
{
    setCurrentAction(RG::ActionEditRotate);
}

void RS_ActionHandler::slotEditAddVertex()
{
    setCurrentAction(RG::ActionEditAddVertex);
}

void RS_ActionHandler::slotEditDelVertex()
{
    setCurrentAction(RG::ActionEditDelVertex);
}

void RS_ActionHandler::slotUndo()
{
    setCurrentAction(RG::ActionUndo);
}

void RS_ActionHandler::slotRedo()
{
    setCurrentAction(RG::ActionRedo);
}
