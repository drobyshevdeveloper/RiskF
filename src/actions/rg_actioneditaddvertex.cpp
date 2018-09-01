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

#include "rg_actioneditaddvertex.h"

#include <QMouseEvent>

#include "rg_marker.h"
#include "rg_entitycontainer.h"
#include "rg_graphicview.h"
#include "rg_information.h"
#include "rg_modification.h"
#include "rg_polygon.h"


RG_ActionEditAddVertex::RG_ActionEditAddVertex(RG_EntityContainer& container, RG_GraphicView& graphicView)
    : RG_ActionInterface("Add anchor point", container, graphicView)
{

}

RG_ActionEditAddVertex::~RG_ActionEditAddVertex()
{

}

void RG_ActionEditAddVertex::trigger()
{
//    RG_Polygon* poly = new RG_Polygon(container, points.data);
//    container->addEntity(line);
//    document->beginUndoGroup();
//    document->addUndoable(line);
//    document->endUndoGroup();
}

void RG_ActionEditAddVertex::mouseMoveEvent(QMouseEvent *e)
{
/*
    RG_Marker marker;
    RG_Vector mouse = graphicView->toGraph(e->x(), e->y());
    pPoints->v2 = mouse;

    switch (getStatus()) {
    case Neutral:
        break;
    case FirstClick:
        // Реализовать проверку перемещения выбранных сущностей

        // Проверить изменение размеров сущностей перемещением маркеров
        marker = container->getNearestSelectedRef(pPoints->v1);
        if (marker.valid) {
            if (marker.type == RG_Marker::Vertex) {
                // Найден маркер изменения вершин сущности
                RG_Vector d(RG_MARKER_SIZE_2, RG_MARKER_SIZE_2);
                if (pPoints->v1.isInWindow(marker.coord-d, marker.coord+d)) {
                    marker.offset = marker.coord - pPoints->v1;
                    pPoints->marker = marker;
                    setStatus(MoveRef);
                    break;
                }
            }
            if (marker.type == RG_Marker::Face) {
                // Найден маркер изменения граней сущности
                if (marker.dist < 3.0) {
                    marker.offset = marker.coord - pPoints->v1;
                    pPoints->marker = marker;
                    setStatus(MoveFace);
                    break;
                }
            }
            if (marker.type == RG_Marker::Move) {
                // Найден маркер перемещения сущности целиком
                marker.offset = marker.coord - pPoints->v1;
                pPoints->marker = marker;
                setStatus(Moving);
                break;
            }
            if (marker.type == RG_Marker::Rotate) {
                // Найден маркер изменения угла поворота сущности
            }
        }

        // Если перемещения сущностей нет включаем режим выбора прямогольной областью
        setStatus(SetCorner2);
        break;
    case SetCorner2:
    {
        deletePreview();

        RG_OverlayRect* rect = new RG_OverlayRect(nullptr, {pPoints->v1,pPoints->v2});

        preview->addEntity(rect);
        drawPreview();

        break;
    }
    case MoveRef:
        deletePreview();
        preview->addSelectionFrom(container);
        preview->moveRef(pPoints->marker.coord,
                         pPoints->v2 - pPoints->v1);
        drawPreview();
        /*
        pPoints->marker.entity->moveRef(pPoints->marker, pPoints->v2 - pPoints->v1);
        graphicView->redraw();
        */
//    }

    RG_Vector snapper = snapPoint(e);

//    RL_DIALOGFACTORY->updateCoordinateWidget(snapper, snapper);
}

void RG_ActionEditAddVertex::mousePressEvent(QMouseEvent *e)
{
    RG_Vector mouse = graphicView->toGraph(e->x(), e->y());

    if (e->button() == Qt::LeftButton) {
        RG_Marker marker = container->getNearestSelectedRef(mouse);
        if (marker.valid) {
            if (marker.type == RG_Marker::Face) {
                if (marker.dist < 3.0) {
                    // Найден маркер изменения граней сущности
                    // Определим тип объекта
                    if (marker.entity->rtti()==RG::EntityPolygon) {
                        // Найден соответствующий объект
                        // Найдем ближайшую точку на грани/ребре
                        RG_Polygon* poly = dynamic_cast<RG_Polygon*>(marker.entity);
                        if (!poly->isRect()) {
                            // Многоугольник
                            RG_VectorSolutions vs = poly->getRefPoints();
                            RG_Vector pt  = RG_Information::getNearestPointOnLineSegment(mouse,
                                          vs[marker.index],
                                          vs[(marker.index+1)%vs.count()],
                                          nullptr);
                            RG_Modification m(container, graphicView);
                            m.addVertex({marker, pt});
                            graphicView->redraw(RG::RedrawDrawing);
                        }
                    }

 //                   if (

                    // добавить ее в список вершин объекта

                    // заменить объект через RG_Modification

                }
            }
        }
    }
}

void RG_ActionEditAddVertex::mouseReleaseEvent(QMouseEvent *e)
{
    /*
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
        case MoveRef: {
            RG_Modification m(container, graphicView);
            RG_MoveRefData data;
            data.ref = pPoints->marker.coord;
            data.offset = pPoints->v2 - pPoints->v1;
            m.moveRef(data);
            deletePreview();
            setStatus(Neutral);
            break;
        }
        case MoveFace: {
            RG_Modification m(container, graphicView);
            RG_MoveFaceData data;
            data.marker = pPoints->marker;
            data.offset = pPoints->v2 - pPoints->v1;
            m.moveFace(data);
            deletePreview();
            setStatus(Neutral);
            break;
        }
        case Moving: {
            RG_Modification m(container, graphicView);
            RG_MovingData data;
            data.offset = pPoints->v2 - pPoints->v1;
            m.move(data);
            deletePreview();
            setStatus(Neutral);
            break;
        }
        default:
            break;
        }
    }
    */
}

