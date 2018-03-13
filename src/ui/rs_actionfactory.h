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

#ifndef RS_ACTIONFACTORY_H
#define RS_ACTIONFACTORY_H

#include <QObject>
#include <QMap>
#include <QString>

class QAction;
class RS_ActionGroupManager;

class RS_ActionFactory : public QObject
{
    Q_OBJECT
public:
    RS_ActionFactory(QObject *parent, QObject *a_handler);

    void fillActionContainer(QMap<QString, QAction*>&a_map, RS_ActionGroupManager* agm);

private:
    QObject* action_handler;
    QObject* main_window;
};

#endif // RS_ACTIONFACTORY_H
