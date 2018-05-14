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
        EntityGraphic,          // Графический документ
        EntityLine,
        EntityPreview           // Контейнер предпросмотра
    };

    /**
     * @brief The ActionType enum
     * Перечисление типов действия (Actions)
     */
    enum ActionType {
        ActionNone,
        ActionDrawLine
    };

    /**
     * @brief The RedrawMethod enum
     * Перечисление методов перерисовки представления
     */
    enum RedrawMethod {
        RedrawNone = 0,
        RedrawGrid = 2,
        RedrawOverlay = 4,      // Перерисовать накладываемые слои
        RedrawDrawing = 8,      // Перерисовать основные элемнты рисунка
        RedrawAll = 0xFFF
    };
    /**
     * @brief The OverlayGraphic enum
     * Перечисление прозрачных временных слоев отображения
     */
    enum OverlayGraphics {
        ActionPreviewEntity,       // Слой элементов просмотра для текущего действия
        Snapper                    // Слой курсора графичского модуля
    };
};

#endif // RG_H
