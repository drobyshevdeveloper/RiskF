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

class RG_Preview;

class RG_PreviewActionInterface : public RG_ActionInterface
{
public:
    RG_PreviewActionInterface(const char* name,
                              RG_EntityContainer& container,
                              RG_GraphicView& graphicView);

    virtual ~RG_PreviewActionInterface();

    virtual void init(int status=0) override;

    void drawPreview();
    void deletePreview();
protected:
    std::unique_ptr<RG_Preview> preview;

private:
    /**
     * @brief hasPreview: флаг наличия элементов в слое предпросмотра
     * true - элементы есть
     * false - пусто
     */
    bool hasPreview;
};

#endif // RG_PREVIEWACTIONINTERFACE_H
