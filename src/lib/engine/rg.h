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

#ifndef RG_H
#define RG_H


class RG
{
public:
    /**
     * @brief The EntityType enum
     * Перечисление типов сущностей
     */
    enum EntityType {
        EntityUnknow,           // Неизвестный
        EntityContainer,        // Контейнер
        EntityGraphic           // Графический документ
    };

    /**
     * @brief The ActionType enum
     * Перечисление типов действия (Actions)
     */
    enum ActionType {
        ActionNone,
        ActionDrawLine
    };
};

#endif // RG_H
