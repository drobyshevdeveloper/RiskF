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

#ifndef RL_SETTINGS_H
#define RL_SETTINGS_H

#include <QSettings>
#include <QString>

#define RL_SETTINGS RL_Settings::instance()

class RL_Settings;  // Опережающее объявление

/**
 * @brief RL_SettingsDestroyer - класс автоматического разрушения объекта RL_Settings
 */
class RL_SettingsDestroyer
{
private:
    RL_Settings* instance;
public:
    ~RL_SettingsDestroyer();
    void initialize( RL_Settings* p );
};

/**
 * @brief RL_Settings - класс поддержки сохранения настроек приложения
 */
class RL_Settings : public QSettings
{
public:
    RL_Settings();

    /**
     * @brief instance
     * @return - возвращает единственный экземпляр объекта
     */
    static RL_Settings& instance();

    friend class RL_SettingsDestroyer;
private:
    static RL_Settings* uniqueInstance;
    static RL_SettingsDestroyer destroyer;
};

#endif // RL_SETTINGS_H
