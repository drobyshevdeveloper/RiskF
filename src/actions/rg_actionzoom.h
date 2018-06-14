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

#ifndef RG_ACTIONZOOM_H
#define RG_ACTIONZOOM_H

#include "rg_actioninterface.h"

class RG_ActionZoom : public RG_ActionInterface
{
public:
    RG_ActionZoom(RG_EntityContainer& container,
                  RG_GraphicView& graphicView,
                  RG::Direction dir,
                  RG_Vector pos);

    virtual ~RG_ActionZoom();

    void init(int status=0) override;

    void trigger();
private:
    RG_Vector pos_;
    RG::Direction dir_;

};

#endif // RG_ACTIONZOOM_H
