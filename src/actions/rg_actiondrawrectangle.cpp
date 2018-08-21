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

#include "rg_actiondrawrectangle.h"

#include "rl_debug.h"
#include "rg_entitycontainer.h"
#include "rg_graphicview.h"
#include "rg_document.h"
#include "rg_preview.h"
#include "rl_dialogfactory.h"
#include "rl_dialogfactoryinterface.h"
#include "rg_coordinateevent.h"

RG_ActionDrawRectangle::RG_ActionDrawRectangle(RG_EntityContainer& container,
                                               RG_GraphicView& graphicView)
    :RG_PreviewActionInterface("DrawRectangle", container, graphicView)
{
    actionType = RG::ActionDrawRectangle;
}

RG_ActionDrawRectangle::~RG_ActionDrawRectangle()
{

}

void RG_ActionDrawRectangle::init(int status)
{
    RG_PreviewActionInterface::init(status);
    drawSnapper();
}

void RG_ActionDrawRectangle::trigger()
{
    RG_Rectangle* rect = new RG_Rectangle(container, points.data);
    container->addEntity(rect);
    document->beginUndoGroup();
    document->addUndoable(rect);
    document->endUndoGroup();
}

void RG_ActionDrawRectangle::coordinateEvent(RG_CoordinateEvent *ce)
{
    RG_Vector mouse = ce->getCoordinate();

    switch (getStatus()) {
    case SetStartPoint:
        // Режим установки первой точки прямоугольника
        points.data.corner1 = mouse;
        setStatus(SetEndPoint);
        break;
    case SetEndPoint:
        // Режим установки второй точки прямоугольника
        points.data.corner2 = mouse;

        trigger();
        deletePreview();
        graphicView->redraw(RG::RedrawDrawing);
        setStatus(SetStartPoint);
        break;
    }
}

void RG_ActionDrawRectangle::mousePressEvent(QMouseEvent *e)
{

}

void RG_ActionDrawRectangle::mouseMoveEvent(QMouseEvent *e)
{
    RL_DEBUG << "RG_ActionDrawRectangle::mouseMoveEvent Begin";

    RG_Vector mouse = snapPoint(e);
    RL_DEBUG << "getStatus() = " << getStatus();
    if (getStatus() == SetEndPoint) {
        // Выводим прямоугольник на просмотр если текущий режим - установка второй точки прямоугольника
        deletePreview();
        RG_Rectangle* rect = new RG_Rectangle(nullptr, {points.data.corner1,
                                              mouse});
        preview->addEntity(rect);
        drawPreview();
        RL_DIALOGFACTORY->updateCoordinateWidget(points.data.corner1, mouse);

    }

    if (getStatus() == SetStartPoint) {
        RL_DIALOGFACTORY->updateCoordinateWidget(mouse, mouse);
    }

    RL_DEBUG << "RG_ActionDrawRectangle::mouseMoveEvent Ok";
}

void RG_ActionDrawRectangle::mouseReleaseEvent(QMouseEvent *e)
{
    RL_DEBUG << "RG_ActionDrawRectangle::mouseReleaseEvent Begin";

    if (e->button() == Qt::LeftButton) {
        // Нажата левая кнопка мыши
        RG_Vector snapped = snapPoint(e);
        RG_CoordinateEvent ce(snapped);
        coordinateEvent(&ce);
    }
    RL_DEBUG << "RG_ActionDrawRectangle::mouseReleaseEvent Ok";
}

void RG_ActionDrawRectangle::updateMouseCursor()
{
//    RG::SnapperType oldSt = getSnapperType();

    if (getStatus()==SetStartPoint) {
        setSnapperType(RG::SnapperDefault);
        graphicView->setMouseCursor(RG::ArrowCursor);
    }
    if (getStatus()==SetEndPoint) {
        setSnapperType(RG::SnapperMiddleCross);
        graphicView->setMouseCursor(RG::ArrowCursor);
    }

//    if (oldSt != getSnapperType()) {
//        drawSnapper();
//    }
}
