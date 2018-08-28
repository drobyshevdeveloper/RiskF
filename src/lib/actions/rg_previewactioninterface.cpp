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

#include "rg_previewactioninterface.h"

#include "rg.h"
#include "rg_preview.h"
#include "rg_graphicview.h"
#include "rg_entitycontainer.h"
#include "rg_selection.h"

RG_PreviewActionInterface::RG_PreviewActionInterface(const char* name,
                                                     RG_EntityContainer &container,
                                                     RG_GraphicView &graphicView)
    : RG_ActionInterface(name, container, graphicView)
    , preview( new RG_Preview(&container) )
    , hasPreview(false)
{

}

RG_PreviewActionInterface::~RG_PreviewActionInterface()
{

}

void RG_PreviewActionInterface::init(int status)
{
    deletePreview();
    RG_ActionInterface::init(status);
}

void RG_PreviewActionInterface::cancelAction()
{
    deletePreview();

    RG_Selection s(container, graphicView);
    s.deselectAll();
    graphicView->redraw(RG::RedrawOverlay);

    RG_ActionInterface::cancelAction();
}



void RG_PreviewActionInterface::drawPreview()
{
    RG_EntityContainer* container = graphicView->getOverlayContainer(RG::ActionPreviewEntity);
    container->clear();
    container->setOwner(false); // Указать, что контейнер не является владельцем элементов (чтобы их не удалили дважды)
    container->addEntity(preview.get());

    graphicView->redraw(RG::RedrawOverlay);
    hasPreview = true;
}

void RG_PreviewActionInterface::deletePreview()
{
    if (hasPreview) {
        preview->clear();
        hasPreview = false;
    }
    graphicView->getOverlayContainer(RG::ActionPreviewEntity)->clear();
}
