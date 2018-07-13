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

#ifndef RG_ACTIONUNDO_H
#define RG_ACTIONUNDO_H

#include "rg_actioninterface.h"

class RG_ActionUndo : public RG_ActionInterface
{
public:
    RG_ActionUndo(RG_EntityContainer& container,
                  RG_GraphicView& graphicView,
                  bool bUndo);

    virtual ~RG_ActionUndo();

    void init(int status=0) override;

    void trigger();
private:
    bool bUndo_;
};

#endif // RG_ACTIONUNDO_H
