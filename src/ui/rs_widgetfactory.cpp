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

}
