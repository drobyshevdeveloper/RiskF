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

#include "rg_actioneditrotate.h"

#include <QMouseEvent>

#include "rg_selection.h"
#include "rg_graphicview.h"
#include "rg_overlayrect.h"
#include "rg_preview.h"
#include "rg_actionzoompan.h"
#include "rl_dialogfactory.h"
#include "rl_dialogfactoryinterface.h"
#include "rg_modification.h"
#include "rg_actionselect.h"
#include "rg_document.h"
#include "rg_line.h"

RG_ActionEditRotate::RG_ActionEditRotate(RG_EntityContainer &container,
                                         RG_GraphicView &graphicView)
    : RG_PreviewActionInterface("EditRotate", container, graphicView)
{
    actionType = RG::ActionEditRotate;
//    pPoints = new Points;
}

RG_ActionEditRotate::~RG_ActionEditRotate()
{
 /*   if (pPoints) {
        delete pPoints;
        pPoints = nullptr;
    }
    */
}

void RG_ActionEditRotate::init(int status)
{
    // В зависимости наличия выбранных объектов установим статус
    // Нет выбранных объектов    - SelectEntity
    // Имеются выбранные объекты - SetBasePoint
//    if (container->countSelection()>0) RG_PreviewActionInterface::init(SelectEntity);
//    else                               RG_PreviewActionInterface::init(SetBasePoint);

    // Если нет выбранных объектов включим инструмент выбора
    if (container->countSelection()==0) {
        graphicView->setCurrentAction(new RG_ActionSelect(*container, *graphicView, this));
    }
    RG_PreviewActionInterface::init(SetBasePoint);
}

void RG_ActionEditRotate::coordinateEvent(RG_CoordinateEvent *ce)
{

}

void RG_ActionEditRotate::mouseMoveEvent(QMouseEvent *e)
{
//    RG_Marker marker;
    RG_Vector mouse = graphicView->toGraph(makeVector(e->position()));
//    points.v2 = mouse;

    switch (getStatus()) {
    case SetBasePoint:
        points.basePoint = mouse;
        break;
    case SetAngle:
    {
        points.anglePoint = mouse;
        deletePreview();

        preview->addSelectionFrom(container);
        preview->rotate(points.basePoint, points.anglePoint);

        RG_Line* line = new RG_Line(nullptr, {points.basePoint, points.anglePoint});
        preview->addEntity(line);
        line = new RG_Line(nullptr, {points.basePoint+RG_Vector(5.0, 5.0),
                                     points.basePoint+RG_Vector(-5.0, -5.0)});
        preview->addEntity(line);
        line = new RG_Line(nullptr, {points.basePoint+RG_Vector(5.0, -5.0),
                                     points.basePoint+RG_Vector(-5.0, 5.0)});
        preview->addEntity(line);

        drawPreview();

        break;
    }

    default:

        break;
    }

    RG_Vector snapper = snapPoint(e);

    RL_DIALOGFACTORY->updateCoordinateWidget(snapper, snapper);
}

void RG_ActionEditRotate::mousePressEvent(QMouseEvent *e)
{
/*    if (e->button() == Qt::LeftButton) {
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
    */
}

void RG_ActionEditRotate::mouseReleaseEvent(QMouseEvent *e)
{
    RG_Vector mouse = graphicView->toGraph(makeVector(e->position()));
//    points->v2 = mouse;
//    RG_Entity* en = nullptr;

    if (e->button() == Qt::LeftButton) {
        switch (getStatus()) {
        case SetBasePoint:
            points.basePoint = mouse;
            setStatus(SetAngle);
            graphicView->redraw(RG::RedrawDrawing);
            e->accept();
            break;
        case SetAngle: {
            RG_Modification m(container, graphicView);

            m.rotate({points.basePoint, points.anglePoint});

/*            RG_Selection s(container, graphicView);
            s.selectWindow(pPoints->v1, pPoints->v2,
                           true,
                           (pPoints->v1.x > pPoints->v2.x)?true:false);
*/
            deletePreview();
            setStatus(SetBasePoint);
            graphicView->redraw(RG::RedrawDrawing);
            e->accept();
            break;
        }
        default:
            break;
        }
    }
}

void RG_ActionEditRotate::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Escape:
        cancelAction();
//        finish();
        init();
        e->accept();
        break;
    default:
        e->ignore();
    }
}

void RG_ActionEditRotate::keyReleaseEvent(QKeyEvent *e)
{

}

void RG_ActionEditRotate::updateMouseCursor()
{
//    RG::SnapperType oldSt = getSnapperType();

    setSnapperType(RG::SnapperDefault);
/*    if (getStatus()==Panning) {
        graphicView->setMouseCursor(RG::ClosedHandCursor);
        return;
    }
    */
    graphicView->setMouseCursor(RG::ArrowCursor);

//    if (oldSt != getSnapperType()) {
//        drawSnapper();
//    }
}

void RG_ActionEditRotate::setChildActionExitCode(int cod)
{
    if (cod == RG_ActionSelect::ActionCancel) {
        graphicView->killAllActions();
    }
}
