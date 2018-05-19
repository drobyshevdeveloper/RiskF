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

#ifndef RG_ACTIONDEFAULT_H
#define RG_ACTIONDEFAULT_H

#include "rg_previewactioninterface.h"

class RG_ActionDefault : public RG_PreviewActionInterface
{
public:
    enum Status {
        None
    };
    RG_ActionDefault(RG_EntityContainer& container,
                     RG_GraphicView& graphicView);

    virtual ~RG_ActionDefault();

    virtual void init(int status=None) override;
    virtual void coordinateEvent(RG_CoordinateEvent* ce) override;

    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;
    virtual void mouseReleaseEvent(QMouseEvent* e) override;
    virtual void updateMouseCursor() override;
};

#endif // RG_ACTIONDEFAULT_H
