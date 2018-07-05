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

#include "rg_painterqt.h"

#include <QPen>

#include "rg.h"
#include "rg_vector.h"


RG_PainterQt::RG_PainterQt(QPaintDevice* pd)
    :QPainter(pd)
{

}

void RG_PainterQt::setPen(RG_Pen &pen)
{
    this->pen  = pen;
    QPen p(this->pen.getColor());
    QPainter::setPen(p);
}

void RG_PainterQt::drawLine(const RG_Vector &p1, const RG_Vector &p2)
{
    QPainter::drawLine(p1.x, p1.y, p2.x, p2.y);
}

void RG_PainterQt::drawRect(const QRectF &rect)
{
    QPainter::drawRect(rect);
}

void RG_PainterQt::fillRect(const QRectF &rect, const QColor &color)
{
    QPainter::fillRect(rect, color);
}

void RG_PainterQt::drawPixmap(int x, int y, QPixmap *pixmap)
{
    QPainter::drawPixmap(QPoint(x,y),(*pixmap));
}

void RG_PainterQt::drawMarker(const RG_Vector &p)
{
    QRectF rect(p.x - RG_MARKER_SIZE_2,
                p.y - RG_MARKER_SIZE_2,
                RG_MARKER_SIZE,
                RG_MARKER_SIZE);
    QPainter::fillRect(rect,QColor(Qt::blue));
}
