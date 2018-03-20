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

#ifndef RS_ACTIONHANDLER_H
#define RS_ACTIONHANDLER_H

#include <QObject>

class RS_ActionHandler : public QObject
{
    Q_OBJECT
public:
    RS_ActionHandler(QObject *parent);

signals:

public slots:
    // === Insert ===
    void slotInsertLine(); // временный инструмент
    void slotInsertRoom();
};

#endif // RS_ACTIONHANDLER_H