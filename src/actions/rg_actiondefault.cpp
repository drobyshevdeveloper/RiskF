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
    RG_Vector mouse = RG_Vector(e->x(), e->y());
    pPoints->v2 = mouse;

    RG_Vector snapper = snapPoint(e);
}

void RG_ActionDefault::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        switch (getStatus()) {
        case Neutral:
            pPoints->v1 = RG_Vector(e->x(), e->y());
            setStatus(FirstClick);
            break;
        default:
            break;
        }
    }
}

void RG_ActionDefault::mouseReleaseEvent(QMouseEvent *e)
{
    RG_Vector mouse = RG_Vector(e->x(), e->y());
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
        default:
            break;
        }
    }
}

void RG_ActionDefault::updateMouseCursor()
{
//    RG::SnapperType oldSt = getSnapperType();

    setSnapperType(RG::SnapperDefault);

//    if (oldSt != getSnapperType()) {
//        drawSnapper();
//    }
}
