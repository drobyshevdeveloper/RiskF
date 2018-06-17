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

#include "rg_actionzoom.h"
#include "rg_graphicview.h"

RG_ActionZoom::RG_ActionZoom(RG_EntityContainer& container,
                             RG_GraphicView& graphicView,
                             RG::Direction dir,
                             RG_Vector pos,
                             double zoom)
    : RG_ActionInterface("Zoom", container, graphicView)
{
    dir_ = dir;
    pos_ = pos;
    zoom_ = zoom;
}

RG_ActionZoom::~RG_ActionZoom()
{

}

void RG_ActionZoom::init(int status)
{
    RG_ActionInterface::init(status);
    trigger();
}

void RG_ActionZoom::trigger()
{
    if (dir_ == RG::Out) {
        graphicView->zoomOut(zoom_, pos_);
    }
    if (dir_ == RG::In) {
        graphicView->zoomIn(zoom_, pos_);
    }

    finish();
}
