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

#include "rg_actiondefault.h"

#include <QMouseEvent>

#include "rg_selection.h"
#include "rg_graphicview.h"
#include "rg_overlayrect.h"
#include "rg_preview.h"
#include "rg_actionzoompan.h"
#include "rl_dialogfactory.h"
#include "rl_dialogfactoryinterface.h"

struct RG_ActionDefault::Points {
    RG_Vector v1;
    RG_Vector v2;
};

RG_ActionDefault::RG_ActionDefault(RG_EntityContainer &container,
                                   RG_GraphicView &graphicView)
    : RG_PreviewActionInterface("Default", container, graphicView)
{
    actionType = RG::ActionDefault;
    pPoints = new Points;
}

RG_ActionDefault::~RG_ActionDefault()
{
    if (pPoints) {
        delete pPoints;
        pPoints = nullptr;
    }
}

void RG_ActionDefault::init(int status)
{
    RG_PreviewActionInterface::init(status);
}

void RG_ActionDefault::coordinateEvent(RG_CoordinateEvent *ce)
{

}

void RG_ActionDefault::mouseMoveEvent(QMouseEvent *e)
{
    RG_Vector mouse = graphicView->toGraph(e->x(), e->y());
    pPoints->v2 = mouse;

    switch (getStatus()) {
    case Neutral:
        break;
    case FirstClick:
        // Реализовать проверку перемещения выбранных сущностей

        // Если перемещения сущностей нет включаем режим выбора прямогольной областью
        setStatus(SetCorner2);
        break;
    case SetCorner2:
        deletePreview();

        RG_OverlayRect* rect = new RG_OverlayRect(nullptr, {pPoints->v1,pPoints->v2});

        preview->addEntity(rect);
        drawPreview();

        break;
//    case Panning:

//        break;
    }

    RG_Vector snapper = snapPoint(e);

    RL_DIALOGFACTORY->updateCoordinateWidget(snapper, snapper);
}

void RG_ActionDefault::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        switch (getStatus()) {
        case Neutral:
            pPoints->v1 = graphicView->toGraph(e->x(), e->y());
            if (e->modifiers() == Qt::ControlModifier) {
                //setStatus(Panning);
                RG_ActionZoomPan* actionZoomPan = new RG_ActionZoomPan(*container, *graphicView);
                graphicView->setCurrentAction(actionZoomPan);
                actionZoomPan->mousePressEvent(e);

            } else {
                setStatus(FirstClick);
            }
            break;
        default:
            break;
        }
    }
}

void RG_ActionDefault::mouseReleaseEvent(QMouseEvent *e)
{
    RG_Vector mouse = graphicView->toGraph(e->x(), e->y());
    pPoints->v2 = mouse;
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
            s.selectWindow(pPoints->v1, pPoints->v2,
                           true,
                           (pPoints->v1.x > pPoints->v2.x)?true:false);

            deletePreview();
            setStatus(Neutral);

            break;
        }
        default:
            break;
        }
    }
}

void RG_ActionDefault::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Escape:
        setStatus(Neutral);
        deletePreview();
        graphicView->redraw(RG::RedrawOverlay);
        e->accept();
        break;
    default:
        e->ignore();
    }
}

void RG_ActionDefault::keyReleaseEvent(QKeyEvent *e)
{

}

void RG_ActionDefault::updateMouseCursor()
{
//    RG::SnapperType oldSt = getSnapperType();

    setSnapperType(RG::SnapperDefault);
    if (getStatus()==Panning) {
        graphicView->setMouseCursor(RG::ClosedHandCursor);
        return;
    }
    graphicView->setMouseCursor(RG::ArrowCursor);

//    if (oldSt != getSnapperType()) {
//        drawSnapper();
//    }
}
