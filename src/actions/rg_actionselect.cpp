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

#include "rg_actionselect.h"

#include <QMouseEvent>

#include "rl_dialogfactory.h"
#include "rl_dialogfactoryinterface.h"
#include "rg_overlayrect.h"
#include "rg_entitycontainer.h"
#include "rg_graphicview.h"
#include "rg_selection.h"
#include "rg_preview.h"

RG_ActionSelect::RG_ActionSelect(RG_EntityContainer &container,
                                 RG_GraphicView &graphicView)
    : RG_PreviewActionInterface("Select", container, graphicView)
{
    actionType = RG::ActionSelect;
}

RG_ActionSelect::~RG_ActionSelect()
{

}

void RG_ActionSelect::init(int status)
{
    RG_ActionInterface::init(status);
}

void RG_ActionSelect::coordinateEvent(RG_CoordinateEvent *ce)
{

}

void RG_ActionSelect::mouseMoveEvent(QMouseEvent *e)
{

    RG_Vector mouse = graphicView->toGraph(e->x(), e->y());
    points.v2 = mouse;

    switch (getStatus()) {
    case Neutral:
        break;
    case FirstClick:
        // Движение курсора при нажатой кнопке => включаем режим выбора прямогольной областью
        setStatus(SetCorner2);
        break;
    case SetCorner2:
    {
        deletePreview();

        RG_OverlayRect* rect = new RG_OverlayRect(nullptr, {points.v1,points.v2});

        preview->addEntity(rect);
        drawPreview();

        break;
    }
    }

    RG_Vector snapper = snapPoint(e);

    RL_DIALOGFACTORY->updateCoordinateWidget(snapper, snapper);
}

void RG_ActionSelect::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
 //       switch (getStatus()) {
 //       case Neutral:
            points.v1 = graphicView->toGraph(e->x(), e->y());
            if (e->modifiers() == Qt::ControlModifier) {
            } else {
                setStatus(FirstClick);
            }
 //           break;
 //       default:
 //           break;
 //       }
    }
}

void RG_ActionSelect::mouseReleaseEvent(QMouseEvent *e)
{
    RG_Vector mouse = graphicView->toGraph(e->x(), e->y());
    points.v2 = mouse;
    RG_Entity* en = nullptr;

    if (e->button() == Qt::LeftButton) {
        switch (getStatus()) {
        case FirstClick:
            en = catchEntity(mouse);
            if (en) {
                RG_Selection s(container, graphicView);
                s.singleSelect(en);
            }
            e->accept();
            setStatus(Neutral);
            graphicView->redraw(RG::RedrawDrawing);

            break;
        case SetCorner2: {
            RG_Selection s(container, graphicView);
            s.selectWindow(points.v1, points.v2,
                           true,
                           (points.v1.x > points.v2.x)?true:false);

            deletePreview();
            setStatus(Neutral);

            break;
        }
        default:
            break;
        }
    }
}

void RG_ActionSelect::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Escape:
        setStatus(Neutral);
        deletePreview();

        {
            RG_Selection s(container, graphicView);
            s.deselectAll();
        }

        graphicView->redraw(RG::RedrawOverlay);
        e->accept();
        finish();
        break;
    case Qt::Key_Enter:
        finish();
        e->accept();
        break;
    default:
        e->ignore();
    }
}

void RG_ActionSelect::keyReleaseEvent(QKeyEvent *e)
{

}

void RG_ActionSelect::updateMouseCursor()
{
/*
    setSnapperType(RG::SnapperDefault);
    if (getStatus()==Panning) {
        graphicView->setMouseCursor(RG::ClosedHandCursor);
        return;
    }
    graphicView->setMouseCursor(RG::ArrowCursor);
*/
}
