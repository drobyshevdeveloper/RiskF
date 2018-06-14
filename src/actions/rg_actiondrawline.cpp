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

#include "rg_actiondrawline.h"

#include <QMouseEvent>

#include "rl_debug.h"
#include "rg_previewactioninterface.h"
#include "rg_actioninterface.h"
#include "rg_preview.h"
#include "rg_line.h"
#include "rg_graphicview.h"
#include "rg_coordinateevent.h"

RG_ActionDrawLine::RG_ActionDrawLine(RG_EntityContainer &container, RG_GraphicView &graphicView)
    : RG_PreviewActionInterface("Draw line", container, graphicView)
{
    actionType = RG::ActionDrawLine;
}

RG_ActionDrawLine::~RG_ActionDrawLine()
{

}

void RG_ActionDrawLine::init(int status)
{
    RG_PreviewActionInterface::init(status);
    drawSnapper();
}

void RG_ActionDrawLine::coordinateEvent(RG_CoordinateEvent *ce)
{
    RG_Vector mouse = ce->getCoordinate();

    switch (getStatus()) {
    case SetStartpoint:
        // Режим установки первой точки линии
        points.data.startPoint = mouse;
        setStatus(SetEndpoint);
        break;
    case SetEndpoint:
        // Режим установки второй точки линии
        points.data.endPoint = mouse;

        RG_Line* line = new RG_Line(container, points.data);
        container->addEntity(line);
        deletePreview();
        graphicView->redraw(RG::RedrawDrawing);
        setStatus(SetStartpoint);
        break;
//        default:
//            break;
    }

}

void RG_ActionDrawLine::mousePressEvent(QMouseEvent *e)
{

}

void RG_ActionDrawLine::mouseMoveEvent(QMouseEvent *e)
{
    RL_DEBUG << "RG_ActionDrawLine::mouseMoveEvent Begin";

    RG_Vector mouse = snapPoint(e);
    RL_DEBUG << "getStatus() = " << getStatus();
    if (getStatus() == SetEndpoint) {
        // Выводим линию на просмотр если текущий режим - установка второй точки линии
        deletePreview();
        RG_Line* line = new RG_Line(nullptr, {points.data.startPoint
                                              ,mouse});
        preview->addEntity(line);
        drawPreview();
    }

    RL_DEBUG << "RG_ActionDrawLine::mouseMoveEvent Ok";
}

void RG_ActionDrawLine::mouseReleaseEvent(QMouseEvent *e)
{
    RL_DEBUG << "RG_ActionDrawLine::mouseReleaseEvent Begin";

    if (e->button() == Qt::LeftButton) {
        // Нажата левая кнопка мыши
        RG_Vector snapped = snapPoint(e);
        RG_CoordinateEvent ce(snapped);
        coordinateEvent(&ce);
    }
    RL_DEBUG << "RG_ActionDrawLine::mouseReleaseEvent Ok";
}

void RG_ActionDrawLine::updateMouseCursor()
{
//    RG::SnapperType oldSt = getSnapperType();

    if (getStatus()==SetStartpoint) {
        setSnapperType(RG::SnapperDefault);
        graphicView->setMouseCursor(RG::ArrowCursor);
    }
    if (getStatus()==SetEndpoint) {
        setSnapperType(RG::SnapperMiddleCross);
        graphicView->setMouseCursor(RG::ArrowCursor);
    }

//    if (oldSt != getSnapperType()) {
//        drawSnapper();
//    }
}
