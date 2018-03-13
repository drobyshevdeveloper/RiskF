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

#include "rf_mainwindow.h"

#include <QApplication>
#include <QMdiArea>
#include <QMdiSubWindow>

#include "rl_debug.h"
#include "rl_settings.h"

int main(int argc, char *argv[])
{
    RL_DEBUG << "";
    RL_DEBUG << "=======================";
    RL_DEBUG << "Запуск приложения RiskF";

    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("AWSoft");
    QCoreApplication::setApplicationName("RiskF");
//    QCoreApplication::setApplicationVersion(LC_VERSION);


    RL_DEBUG << "main: creating main window..";
    RF_MainWindow appWin;
    appWin.show();

    RL_DEBUG << "main: entering Qt event loop";
    int return_code = a.exec();
    RL_DEBUG << "main: exited Qt event loop";

    return return_code;
}
