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

#ifndef RG_PREVIEWACTIONINTERFACE_H
#define RG_PREVIEWACTIONINTERFACE_H

#include "rg_actioninterface.h"

class RG_PreviewActionInterface : public RG_ActionInterface
{
public:
    RG_PreviewActionInterface(const char* name,
                              RS_EntityContainer& container,
                              RS_GraphicView& graphicView);

    virtual ~RG_PreviewActionInterface();
};

#endif // RG_PREVIEWACTIONINTERFACE_H
