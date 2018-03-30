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

#ifndef RS_GRAPHICVIEW_H
#define RS_GRAPHICVIEW_H

#include "rg_graphicview.h"

class RG_Document;

class RS_GraphicView : public RG_GraphicView
{
public:
    RS_GraphicView(QWidget* parent = 0, Qt::WindowFlags f = 0, RG_Document* doc = 0);
};

#endif // RS_GRAPHICVIEW_H
