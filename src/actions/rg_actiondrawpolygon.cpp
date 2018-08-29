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

#include "rg_actiondrawpolygon.h"

#include "rl_debug.h"
#include "rg_entitycontainer.h"
#include "rg_graphicview.h"
#include "rg_document.h"
#include "rg_preview.h"
#include "rl_dialogfactory.h"
#include "rl_dialogfactoryinterface.h"
#include "rg_coordinateevent.h"

RG_ActionDrawPolygon::RG_ActionDrawPolygon(RG_EntityContainer& container,
                                           RG_GraphicView& graphicView,
                                           bool isRect)
    :RG_PreviewActionInterface("DrawPolygon", container, graphicView)
{
    actionType = RG::ActionDrawPolygon;
    this->isRect = isRect;
}

RG_ActionDrawPolygon::~RG_ActionDrawPolygon()
{

}

void RG_ActionDrawPolygon::init(int status)
{
    RG_PreviewActionInterface::init(status);
    drawSnapper();
}

void RG_ActionDrawPolygon::trigger()
{
    RG_PolygonData polyData;
    polyData.vertexes = points.vs;
    RG_Polygon* poly = new RG_Polygon(container, polyData, isRect);
    container->addEntity(poly);
    document->beginUndoGroup();
    document->addUndoable(poly);
    document->endUndoGroup();
}

void RG_ActionDrawPolygon::coordinateEvent(RG_CoordinateEvent *ce)
{
    RG_Vector mouse = ce->getCoordinate();

    switch (getStatus()) {
    case SetStartPoint:
        // Режим установки первой точки прямоугольника/многоугольника
        points.vs.push_Back(mouse);
        // В зависимости от типа сущности (прямоугольник/многоугольник)
        // установим статус
        if (isRect) {
            setStatus(SetEndPoint);
        } else {
            setStatus(SetNextPoint);
        }
        break;
    case SetNextPoint:
        // Режим установки следующей точки многоугольника

        // Необходимо реализовать !!!
        points.vs.push_Back(mouse);

        break;
    case SetEndPoint:
        // Режим установки второй точки прямоугольника
        points.vs.push_Back(mouse);

        trigger();
        deletePreview();
        graphicView->redraw(RG::RedrawDrawing);
        points.vs.clear();
        setStatus(SetStartPoint);
        break;
    }
}

void RG_ActionDrawPolygon::mousePressEvent(QMouseEvent *e)
{

}

void RG_ActionDrawPolygon::mouseMoveEvent(QMouseEvent *e)
{
    RL_DEBUG << "RG_ActionDrawPolygon::mouseMoveEvent Begin";

    RG_Vector mouse = snapPoint(e);
    RL_DEBUG << "getStatus() = " << getStatus();
    if (getStatus() == SetNextPoint) {
        // Выводим многоугольник на просмотр если текущий режим - установка следующей точки многоугольника
        deletePreview();
        RG_PolygonData polyData;
        polyData.vertexes = points.vs;
        polyData.vertexes.push_Back(mouse);
        RG_Polygon* poly = new RG_Polygon(nullptr, polyData, isRect);
        preview->addEntity(poly);
        drawPreview();
        RL_DIALOGFACTORY->updateCoordinateWidget(points.vs[0], mouse);

    }

    if (getStatus() == SetEndPoint) {
        // Выводим прямоугольник на просмотр если текущий режим - установка второй точки прямоугольника
        deletePreview();
        RG_PolygonData polyData;
        polyData.vertexes = points.vs;
        polyData.vertexes.push_Back(mouse);
        RG_Polygon* poly = new RG_Polygon(nullptr, polyData, isRect);
        preview->addEntity(poly);
        drawPreview();
        RL_DIALOGFACTORY->updateCoordinateWidget(points.vs[0], mouse);

    }


    if (getStatus() == SetStartPoint) {
        RL_DIALOGFACTORY->updateCoordinateWidget(mouse, mouse);
    }

    RL_DEBUG << "RG_ActionDrawPolygon::mouseMoveEvent Ok";
}

void RG_ActionDrawPolygon::mouseReleaseEvent(QMouseEvent *e)
{
    RL_DEBUG << "RG_ActionDrawPolygon::mouseReleaseEvent Begin";

    if (e->button() == Qt::LeftButton) {
        // Нажата левая кнопка мыши
        RG_Vector snapped = snapPoint(e);
        RG_CoordinateEvent ce(snapped);
        coordinateEvent(&ce);
    }
    RL_DEBUG << "RG_ActionDrawPolygon::mouseReleaseEvent Ok";
}

void RG_ActionDrawPolygon::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
/*
    case Qt::Key_Escape:
        setStatus(Neutral);
        deletePreview();

        {
            RG_Selection s(container, graphicView);
            s.deselectAll();
        }

        graphicView->redraw(RG::RedrawOverlay);
        e->accept();
        break;
*/
    case Qt::Key_Return:
        if (getStatus()==SetNextPoint) {
            trigger();
            deletePreview();
            graphicView->redraw(RG::RedrawDrawing);
            points.vs.clear();
            setStatus(SetStartPoint);
            e->accept();
        }
    default:
        e->ignore();
    }
}

void RG_ActionDrawPolygon::updateMouseCursor()
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
