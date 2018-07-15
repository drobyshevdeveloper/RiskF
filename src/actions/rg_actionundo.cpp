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

#include "rg_actionundo.h"

#include "rg_graphic.h"
#include "rg_graphicview.h"

RG_ActionUndo::RG_ActionUndo(RG_EntityContainer &container,
                             RG_GraphicView &graphicView,
                             bool bUndo)
    : RG_ActionInterface("Action Undo", container, graphicView)
    , bUndo_(bUndo)
{

}

RG_ActionUndo::~RG_ActionUndo()
{

}

void RG_ActionUndo::init(int status)
{
    RG_ActionInterface::init(status);
    trigger();
}

void RG_ActionUndo::trigger()
{
    if (bUndo_) {
        // Undo
        graphic->undo();
    } else {
        // Redo
        graphic->redo();
    }
    graphicView->redraw(RG::RedrawDrawing);
    finish();
}
