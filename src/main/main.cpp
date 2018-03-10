#include "mainwindow.h"
#include <QApplication>

#include "../lib/debug/rl_debug.h"
#include "../lib/rl_settings.h"

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
    MainWindow appWin;
    appWin.show();

    RL_DEBUG << "main: entering Qt event loop";
    int return_code = a.exec();
    RL_DEBUG << "main: exited Qt event loop";

    return return_code;
}
