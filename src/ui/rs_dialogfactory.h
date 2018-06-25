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

#ifndef RS_DIALOGFACTORY_H
#define RS_DIALOGFACTORY_H

#include "rl_dialogfactoryinterface.h"

class QWidget;
class QToolBar;
class RU_CoordinateWidget;

/**
 * @brief The RS_DialogFactory class - реализация интерфейса создания и отображения диалогов
 */
class RS_DialogFactory : public RL_DialogFactoryInterface
{
public:
    RS_DialogFactory(QWidget* parent, QToolBar* ow);

    void updateCoordinateWidget(const RG_Vector& coord1, const RG_Vector& coord2) override;

    void setCoordinateWidget(RU_CoordinateWidget* cw) override;
protected:
    RU_CoordinateWidget* coordinateWidget;
};

#endif // RS_DIALOGFACTORY_H
