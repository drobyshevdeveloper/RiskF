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

#include <QDebug>
#include <QCoreApplication>

#include "rl_settings.h"

RL_Settings*         RL_Settings::uniqueInstance = nullptr;
RL_SettingsDestroyer RL_Settings::destroyer;

// Автоматическое разрушение объекта
RL_SettingsDestroyer::~RL_SettingsDestroyer()
{
    delete instance;
}

void RL_SettingsDestroyer::initialize(RL_Settings *p)
{
    instance = p;
}

// RL_Settings
RL_Settings::RL_Settings()
    :QSettings( QCoreApplication::organizationName(),
                QCoreApplication::applicationName() )
{

}

RL_Settings &RL_Settings::instance()
{
    if (!uniqueInstance) {
        uniqueInstance = new RL_Settings();
        destroyer.initialize( uniqueInstance );
    }
    return *uniqueInstance;
}
