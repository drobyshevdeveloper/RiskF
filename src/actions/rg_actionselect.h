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

#ifndef RG_ACTIONSELECT_H
#define RG_ACTIONSELECT_H

#include "rg_previewactioninterface.h"

class RG_ActionSelect : public RG_PreviewActionInterface
{
public:
    enum Status {
        Neutral,        // Действия отсутствуют
        FirstClick,     // Режим включается при первом нажатии левой кнопки
        SetCorner2,     // Режим выбора второго угла прямоугольной области выбора
    };

    RG_ActionSelect(RG_EntityContainer& container,
                    RG_GraphicView& graphicView);

    ~RG_ActionSelect();

    virtual void init(int status=Neutral) override;
    virtual void coordinateEvent(RG_CoordinateEvent* ce) override;

    virtual void mousePressEvent(QMouseEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;
    virtual void mouseReleaseEvent(QMouseEvent* e) override;
    virtual void keyPressEvent(QKeyEvent* e) override;
    virtual void keyReleaseEvent(QKeyEvent* e) override;
    virtual void updateMouseCursor() override;
private:
    struct Points {
        RG_Vector v1;
        RG_Vector v2;
    };
    Points points;

};

#endif // RG_ACTIONSELECT_H
