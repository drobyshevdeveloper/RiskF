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

#ifndef RG_GRAPHICVIEW_H
#define RG_GRAPHICVIEW_H

#include <QWidget>

class RG_EntityContainer;

class RG_GraphicView : public QWidget
{
    Q_OBJECT
public:
    explicit RG_GraphicView(QWidget *parent = nullptr);



    void setContainer(RG_EntityContainer* c);

signals:

public slots:

protected:
    RG_EntityContainer* container;  // Коллекция всех объектов
};

#endif // RG_GRAPHICVIEW_H
