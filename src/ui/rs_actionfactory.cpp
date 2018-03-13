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

#include "rs_actionfactory.h"

#include <QAction>

#include "rs_actiongroupmanager.h"

RS_ActionFactory::RS_ActionFactory(QObject *parent, QObject *a_handler)
    : QObject(parent)
    , main_window(parent)
    , action_handler(a_handler)
{

}

void RS_ActionFactory::fillActionContainer(QMap<QString, QAction *> &a_map, RS_ActionGroupManager *agm)
{
    QAction* action;


    // == File ==

    action = new QAction("Новый документ", agm->file);
    action->setIcon(QIcon(":/icons/new.png"));
    connect(action, SIGNAL(triggered(bool)), main_window, SLOT(slotFileNew()));
    action->setObjectName("FileNew");
    a_map["FileNew"] = action;


}
