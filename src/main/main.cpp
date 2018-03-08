#include "mainwindow.h"
#include <QApplication>

#include "../lib/debug/rl_debug.h"

int main(int argc, char *argv[])
{
    FL_DEBUG << __func__ << "Begin";

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
