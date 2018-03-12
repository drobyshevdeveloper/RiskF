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

#include "rs_centralwidget.h"

#include <QVBoxLayout>

RS_CentralWidget::RS_CentralWidget(QWidget *parent)
    : QFrame(parent)
    , mdi_area(new QMdiArea(this))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(mdi_area);

    mdi_area->setObjectName("mdi_area");
    mdi_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdi_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdi_area->setFocusPolicy(Qt::ClickFocus);
    mdi_area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mdi_area->setActivationOrder(QMdiArea::ActivationHistoryOrder);
    mdi_area->setTabsMovable(true);
    mdi_area->setTabsClosable(true);

    setLayout(layout);

}

QMdiArea* RS_CentralWidget::getMdiArea()
{
    return mdi_area;
}
