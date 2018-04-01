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

#include "ru_mdiwindow.h"

#include <QMdiArea>

#include "rg_graphic.h"
#include "rs_graphicview.h"

unsigned int RU_MDIWindow::idCounter = 0;

RU_MDIWindow::RU_MDIWindow(RG_Document *doc, QWidget *parent, Qt::WindowFlags wflags)
    : QMdiSubWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setMinimumSize(QSize(100,100));

    cadMDIArea = (QMdiArea*) parent;

    if (!doc) {
        document = new RG_Graphic();
        document->newDoc();
        owner = true;
    } else {
        document = doc;
        owner = false;
    }

    graphicView = new RS_GraphicView(this, 0, document);
    setWidget(graphicView);

    id = ++idCounter;
}

RU_MDIWindow::~RU_MDIWindow()
{
    if (document) {
        if (owner) delete document;
        document = nullptr;
    }
}

RS_GraphicView* RU_MDIWindow::getGraphicView()
{
    return graphicView;
}
