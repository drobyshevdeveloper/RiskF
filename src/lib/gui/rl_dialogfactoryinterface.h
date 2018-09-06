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

#ifndef RL_DIALOGFACTORYINTERFACE_H
#define RL_DIALOGFACTORYINTERFACE_H

class QString;
class RU_CoordinateWidget;
class RU_InformationWidget;
class RG_Vector;

/**
 * @brief The RL_DialogFactoryInterface class - Класс интерфейса для вызова диалогов
 */
class RL_DialogFactoryInterface
{
public:
    virtual ~RL_DialogFactoryInterface() = default;

    virtual void updateCoordinateWidget(const RG_Vector& coord1, const RG_Vector& coord2) = 0;

    virtual void setCoordinateWidget(RU_CoordinateWidget* cw) = 0;

    virtual void setInformationWidget(RU_InformationWidget* iw) = 0;

    virtual void updateInformationWidget(const QString& strInfo) = 0;
};

#endif // RL_DIALOGFACTORYINTERFACE_H
