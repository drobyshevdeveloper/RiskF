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

#include "rg_overlayrect.h"

#include "rg_vector.h"
#include "rg_pen.h"
#include "rg_painter.h"
#include "rg_graphicview.h"

#include <QRectF>

RG_OverlayRect::RG_OverlayRect(RG_EntityContainer *parent)
    : RG_AtomicEntity(parent)
{
}

RG_OverlayRect::RG_OverlayRect(RG_EntityContainer *parent, const RG_OverlayRectData &d)
    : RG_AtomicEntity(parent)
    , data(d)
{
    calculateBorders();
}

RG_OverlayRect::~RG_OverlayRect()
{
}

RG_Entity* RG_OverlayRect::clone()
{
    RG_OverlayRect* rect = new RG_OverlayRect(*this);
    rect->initID();
    return rect;
}

void RG_OverlayRect::calculateBorders()
{
    vMin.x = data.corner1.x;
    vMax.x = data.corner2.x;
    if (vMin.x > vMax.x) {
        std::swap(vMin.x, vMax.x);
    }
    vMin.y = data.corner1.y;
    vMax.y = data.corner2.y;
    if (vMin.y > vMax.y) {
        std::swap(vMin.y, vMax.y);
    }
}

void RG_OverlayRect::draw(RG_Painter *painter, RG_GraphicView *view)
{
    if ( !(painter && view) ) {
        return;
    }

    RG_Vector v1 = view->toGui(data.corner1);
    RG_Vector v2 = view->toGui(data.corner2);

    QRectF selectRect(
                v1.x,
                v1.y,
                v2.x - v1.x,
                v2.y - v1.y);

    RG_Pen pen;
    pen.setColor(QColor(Qt::blue));
    painter->setPen(pen);

    QColor color;
    if (v1.x > v2.x) {
        color.setRgba(qRgba(9,240,9,90));
    }
    else {
        color.setRgba(qRgba(9,9,240,90));

    }

    painter->fillRect(selectRect, color);
    painter->drawRect(selectRect);
}
