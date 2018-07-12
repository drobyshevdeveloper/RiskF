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

#ifndef RG_UNDOGROUP_H
#define RG_UNDOGROUP_H

#include <vector>

class RG_Undoable;

class RG_UndoGroup
{
public:
    RG_UndoGroup();

    void removeUndoable(RG_Undoable* u);
    /**
     * @brief clear
     * Очищает список Undo
     */
    void clear();

    std::vector<RG_Undoable*> getUndoables() const;

private:
    std::vector<RG_Undoable*> undoables;
};

#endif // RG_UNDOGROUP_H
