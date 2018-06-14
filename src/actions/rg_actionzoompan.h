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

#ifndef RG_ACTIONZOOMPAN_H
#define RG_ACTIONZOOMPAN_H

#include "rg_actioninterface.h"

class RG_ActionZoomPan : public RG_ActionInterface
{
public:
    enum Status {
        SetPanStart,
        SetPanning,
        SetPanEnd
    };

    RG_ActionZoomPan(RG_EntityContainer& container,
                     RG_GraphicView& graphicView);

    void init(int status=0) override;

    void trigger();

    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
//    void keyPressEvent(QKeyEvent* e) override;
//    void keyReleaseEvent(QKeyEvent* e) override;
    void updateMouseCursor() override;
private:
    RG_Vector v1;
    RG_Vector v2;

};

#endif // RG_ACTIONZOOMPAN_H
