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

#ifndef RS_WIDGETFACTORY_H
#define RS_WIDGETFACTORY_H

#include <QObject>
#include <QMap>
#include <QString>

class QAction;
class QMenu;
class QMenuBar;
class QToolBar;
class RF_MainWindow;
class RS_ActionGroupManager;

class RS_WidgetFactory : public QObject
{
    Q_OBJECT
public:
    explicit RS_WidgetFactory(RF_MainWindow* main_win,
                              QMap<QString, QAction *> &action_map,
                              RS_ActionGroupManager* agm);

    void createCategoriesToolBar();
    void createMenus(QMenuBar* menu_bar);

    QToolBar* option_toolbar;
    QMenu* file_menu;
    QMenu* insert_menu;
    QMenu* edit_menu;
private:
    RF_MainWindow* main_window;
    QMap<QString,QAction*>& a_map;
    RS_ActionGroupManager* ag_manager;

    QList<QAction*> file_actions;
    QList<QAction*> insert_actions;
    QList<QAction*> edit_actions;
};

#endif // RS_WIDGETFACTORY_H
