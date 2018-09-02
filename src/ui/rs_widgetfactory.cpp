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

#include "rs_widgetfactory.h"

#include <QToolBar>
#include <QToolButton>
#include <QMenu>
#include <QMenuBar>

#include "rf_mainwindow.h"
#include "rs_actiongroupmanager.h"

RS_WidgetFactory::RS_WidgetFactory(RF_MainWindow* main_win,
                                   QMap<QString,QAction*>& action_map,
                                   RS_ActionGroupManager* agm)
    : QObject(nullptr)
    , main_window(main_win)
    , a_map(action_map)
    , ag_manager(agm)
{
    file_actions
            << a_map["FileNew"];
    insert_actions
            << a_map["InsertLine"]
            << a_map["InsertRoom"]
            << a_map["InsertRectangle"]
            << a_map["InsertPolygon"];
    edit_actions
            << a_map["Select"]
            << a_map["Copy"]
            << a_map["Rotate"]
            << a_map["AddVertex"]
            << a_map["DelVertex"]
            << a_map["Undo"]
            << a_map["Redo"];

}

void RS_WidgetFactory::createCategoriesToolBar()
{
    QSizePolicy toolBarPolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QToolBar* insert_toolbar = new QToolBar(RF_MainWindow::tr("Insert"), main_window);
    insert_toolbar->setSizePolicy(toolBarPolicy);
    insert_toolbar->setObjectName("insert_toolbar");
    insert_toolbar->addActions(edit_actions);     // Временно !!! пока у нас один инструмент Select
    insert_toolbar->addActions(insert_actions);

    main_window->addToolBar(Qt::LeftToolBarArea, insert_toolbar);

    option_toolbar = nullptr; // временно !!!
}

void RS_WidgetFactory::createMenus(QMenuBar *menu_bar)
{
    QMenu* sub_menu;
    
    // == File ==
    file_menu = new QMenu(RF_MainWindow::tr("&File"), menu_bar);
    file_menu->setObjectName("File");
    file_menu->setTearOffEnabled(false); // false - неоткрепляемое меню
    file_menu->addActions(file_actions);

    // == Insert ==
    insert_menu = new QMenu(RF_MainWindow::tr("&Insert"), menu_bar);
    insert_menu->setObjectName("Insert");
    insert_menu->setTearOffEnabled(false);
    insert_menu->addActions(insert_actions);

    // == Edit ==
    edit_menu = new QMenu(RF_MainWindow::tr("&Edit"), menu_bar);
    insert_menu->setObjectName("Edit");
    insert_menu->setTearOffEnabled(false);
    insert_menu->addActions(edit_actions);

    // ...


    // ...
    menu_bar->addMenu(file_menu);
    menu_bar->addMenu(insert_menu);
    menu_bar->addMenu(edit_menu);

}
