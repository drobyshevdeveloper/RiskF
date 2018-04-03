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

#include "rg_graphicview.h"

#include "rg_eventhandler.h"

RG_GraphicView::RG_GraphicView(QWidget *parent)
    : QWidget(parent)
    , eventHandler(new RG_EventHandler(this))
{

}

void RG_GraphicView::setContainer(RG_EntityContainer *c)
{
    container = c;
}

void RG_GraphicView::setCurrentAction(RG_ActionInterface *action)
{
    if (eventHandler) {
        eventHandler->setCurrentAction(action);
    }
}
