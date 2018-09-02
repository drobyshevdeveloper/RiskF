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

#ifndef RU_INFORMATIONWIDGET_H
#define RU_INFORMATIONWIDGET_H

#include <QWidget>

namespace Ui {
class RU_InformationWidget;
}

class RU_InformationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RU_InformationWidget(QWidget *parent = 0);
    ~RU_InformationWidget();

    void setInformation(const QString& strInfo);

private:
    Ui::RU_InformationWidget *ui;
};

#endif // RU_INFORMATIONWIDGET_H
