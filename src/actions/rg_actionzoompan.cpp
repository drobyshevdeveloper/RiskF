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

#include "rg_actionzoompan.h"

#include <QMouseEvent>

#include "rg_graphicview.h"

RG_ActionZoomPan::RG_ActionZoomPan(RG_EntityContainer &container, RG_GraphicView &graphicView)
    : RG_ActionInterface("Zoom Paning", container, graphicView)
{

}

void RG_ActionZoomPan::init(int status)
{
    RG_ActionInterface::init(status);
    v1 = v2 = RG_Vector(false);
    setStatus(SetPanStart);
}

void RG_ActionZoomPan::trigger()
{
    switch(getStatus()) {
    case SetPanning:
        graphicView->zoomPan(v2.x-v1.x, v2.y-v1.y);
        v1 = v2;
        break;
    case SetPanEnd:
        finish();
//        graphicView->adjustOffsetControl();
        graphicView->redraw();
        break;
    }
}

void RG_ActionZoomPan::mouseMoveEvent(QMouseEvent *e)
{
    switch(getStatus()) {
    case SetPanning:
        v2.set(e->x(), e->y());
        trigger();
        break;
    }
}

void RG_ActionZoomPan::mousePressEvent(QMouseEvent *e)
{
    if (e->button()==Qt::MiddleButton ||
            e->button()==Qt::RightButton) {
        v1.set(e->x(), e->y());
        setStatus(SetPanning);
    }
}

void RG_ActionZoomPan::mouseReleaseEvent(QMouseEvent *e)
{
    setStatus(SetPanEnd);
    trigger();
}

void RG_ActionZoomPan::updateMouseCursor()
{
    switch (getStatus()) {
    case SetPanStart:
        graphicView->setMouseCursor(RG::OpenHandCursor);
        break;
    case SetPanning:
        graphicView->setMouseCursor(RG::ClosedHandCursor);
        break;
    case SetPanEnd:
        graphicView->setMouseCursor(RG::OpenHandCursor);
        break;
    }
}
