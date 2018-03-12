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

#ifndef RF_MAINWINDOW_H
#define RF_MAINWINDOW_H

#include <QMainWindow>

class RS_ActionHandler;

class RF_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    RF_MainWindow(QWidget *parent = 0);
    ~RF_MainWindow();


public slots:
    void slotWindowActivated(QMdiSubWindow* w);
private:
    QMdiArea* mdiAreaCAD;

    RS_ActionHandler* action_handler;

};

#endif // RF_MAINWINDOW_H
