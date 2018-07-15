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

    action = new QAction(tr("&New"), agm->file);
    action->setIcon(QIcon(":/icons/new.png"));
    connect(action, SIGNAL(triggered(bool)), main_window, SLOT(slotFileNew()));
    action->setObjectName("FileNew");
    a_map["FileNew"] = action;

    // == Insert ==
    action = new QAction(tr("&Line"), agm->insert);
    action->setIcon(QIcon(":/icons/activity.svg"));
    connect(action, SIGNAL(triggered(bool)), action_handler, SLOT(slotInsertLine()));
    action->setObjectName("InsertLine");
    a_map["InsertLine"] = action;

    action = new QAction(tr("&Room"), agm->insert);
    action->setIcon(QIcon(":/icons/square.svg"));
    connect(action, SIGNAL(triggered(bool)), action_handler, SLOT(slotInsertRoom()));
    action->setObjectName("InsertRoom");
    a_map["InsertRoom"] = action;

    // == Edit ==
    action = new QAction(tr("&Select"), agm->edit);
    action->setIcon(QIcon(":/icons/mouse cursor.ico"));
    connect(action, SIGNAL(triggered(bool)), action_handler, SLOT(slotSelect()));
    action->setObjectName("Select");
    a_map["Select"] = action;

    action = new QAction(tr("&Undo"), agm->edit);
    action->setIcon(QIcon(":/icons/file.svg"));
    connect(action, SIGNAL(triggered(bool)), action_handler, SLOT(slotUndo()));
    action->setObjectName("Undo");
    a_map["Undo"] = action;

    action = new QAction(tr("&Redo"), agm->edit);
    action->setIcon(QIcon(":/icons/file-plus.svg"));
    connect(action, SIGNAL(triggered(bool)), action_handler, SLOT(slotRedo()));
    action->setObjectName("Redo");
    a_map["Redo"] = action;
}
