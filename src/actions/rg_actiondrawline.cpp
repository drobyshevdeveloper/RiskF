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

RG_ActionDrawLine::RG_ActionDrawLine(RG_EntityContainer &container, RG_GraphicView &graphicView)
    : RG_PreviewActionInterface("Draw line", container, graphicView)
{
    actionType = RG::ActionDrawLine;
}

RG_ActionDrawLine::~RG_ActionDrawLine()
{

}

void RG_ActionDrawLine::init()
{
    RG_PreviewActionInterface::init();
    drawSnapper();
}

void RG_ActionDrawLine::mousePressEvent(QMouseEvent *e)
{

}

void RG_ActionDrawLine::mouseMoveEvent(QMouseEvent *e)
{
    RL_DEBUG << "RG_ActionDrawLine::mouseMoveEvent Begin";

    RG_Vector mouse = snapPoint(e);
    deletePreview();
    RG_Line* line = new RG_Line(nullptr, {{0,0},mouse});
    preview->addEntity(line);
    drawPreview();

    RL_DEBUG << "RG_ActionDrawLine::mouseMoveEvent Ok";
}

void RG_ActionDrawLine::mouseReleaseEvent(QMouseEvent *e)
{

}
