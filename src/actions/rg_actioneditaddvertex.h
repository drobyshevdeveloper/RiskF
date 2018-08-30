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

#ifndef RG_ACTIONEDITADDVERTEX_H
#define RG_ACTIONEDITADDVERTEX_H

#include "rg_actioninterface.h"

class RG_ActionEditAddVertex : public RG_ActionInterface
{
public:
    enum {
        SetStartPoint,
        SetNextPoint,
        SetEndPoint
    };

    RG_ActionEditAddVertex(RG_EntityContainer& container, RG_GraphicView& graphicView);

    virtual ~RG_ActionEditAddVertex();

//    virtual void init(int status=Neutral) override;
//    virtual void coordinateEvent(RG_CoordinateEvent* ce) override;

    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;
    virtual void mouseReleaseEvent(QMouseEvent* e) override;
    virtual void keyPressEvent(QKeyEvent* e) override;
    virtual void keyReleaseEvent(QKeyEvent* e) override;
    virtual void updateMouseCursor() override;

};

#endif // RG_ACTIONEDITADDVERTEX_H