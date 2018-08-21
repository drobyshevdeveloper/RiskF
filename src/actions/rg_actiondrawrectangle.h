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

#ifndef RG_ACTIONDRAWRECTANGLE_H
#define RG_ACTIONDRAWRECTANGLE_H

#include "rg_previewactioninterface.h"

#include "rg_rectangle.h"

class RG_ActionDrawRectangle: public RG_PreviewActionInterface
{
public:
    enum {
        SetStartPoint,
        SetEndPoint
    };

    RG_ActionDrawRectangle(RG_EntityContainer& container,
                           RG_GraphicView& graphicView);

    virtual ~RG_ActionDrawRectangle();

    virtual void init(int status=SetStartPoint) override;
    void trigger();
    virtual void coordinateEvent(RG_CoordinateEvent* ce) override;

    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;
    virtual void mouseReleaseEvent(QMouseEvent* e) override;
    virtual void updateMouseCursor() override;
private:
    struct Points {
        RG_RectangleData data;
    };
    Points points;

};

#endif // RG_ACTIONDRAWRECTANGLE_H
