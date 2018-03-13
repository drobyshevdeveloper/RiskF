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

#include "rs_actiongroupmanager.h"

#include <QActionGroup>

RS_ActionGroupManager::RS_ActionGroupManager(QObject *parent)
    : QObject(parent)
    , file( new QActionGroup(this))
    , insert(new QActionGroup(this))
{
    file->setObjectName(tr("file"));
    insert->setObjectName(tr("insert"));

    foreach (auto ag, findChildren<QActionGroup*>()) {
        ag->setExclusive(false);
        // В будущем необходимо связать сигналами главное окно с QAction
    }
}


/*
QList<QActionGroup*> RS_ActionGroupManager::toolGroup()
{
    QList<QActionGroup*> ag_list;
    ag_list << file
            << insert;

    return ag_list;
}
*/
