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

#ifndef RG_ACTIONDRAWLINE_H
#define RG_ACTIONDRAWLINE_H

#include "rg_previewactioninterface.h"

class RG_ActionDrawLine : public RG_PreviewActionInterface
{
public:
    RG_ActionDrawLine(RG_EntityContainer& container,
                      RG_GraphicView& graphicView);

    virtual ~RG_ActionDrawLine();

    virtual void init() override;

    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
};

#endif // RG_ACTIONDRAWLINE_H
