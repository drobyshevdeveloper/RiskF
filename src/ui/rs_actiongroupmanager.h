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

#ifndef RS_ACTIONGROUPMANAGER_H
#define RS_ACTIONGROUPMANAGER_H

#include <QObject>
#include <QList>

class QActionGroup;

class RS_ActionGroupManager : public QObject
{
    Q_OBJECT
public:
    explicit RS_ActionGroupManager(QObject *parent = nullptr);

    QActionGroup* file;
    QActionGroup* insert;
    QActionGroup* edit;

//    QList<QActionGroup*> toolGroup();

signals:

public slots:
};

#endif // RS_ACTIONGROUPMANAGER_H
