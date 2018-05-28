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

#include <QRectF>

RG_OverlayRect::RG_OverlayRect(RG_EntityContainer *parent)
    : RG_AtomicEntity(parent)
{
}

RG_OverlayRect::RG_OverlayRect(RG_EntityContainer *parent, const RG_OverlayRectData &d)
    : RG_AtomicEntity(parent)
    , data(d)
{
}

RG_OverlayRect::~RG_OverlayRect()
{
}

void RG_OverlayRect::draw(RG_Painter *painter, RG_GraphicView *view)
{
    if ( !(painter && view) ) {
        return;
    }

    RG_Vector v1 = data.corner1;
    RG_Vector v2 = data.corner2;

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
        color.setRgba(qRgba(9,9,240,90));
    }
    else {
        color.setRgba(qRgba(9,240,9,90));

    }

    painter->fillRect(selectRect, color);
    painter->drawRect(selectRect);
}
