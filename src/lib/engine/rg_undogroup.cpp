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

#include "rg_undogroup.h"

#include <algorithm>

#include "rg_undoable.h"

RG_UndoGroup::RG_UndoGroup()
{

}

void RG_UndoGroup::addUndoable(RG_Undoable *u)
{
    if (!u) {
        return;
    }
    undoables.push_back(u);
}

void RG_UndoGroup::removeUndoable(RG_Undoable *u)
{
    auto it = std::find(undoables.begin(), undoables.end(), u);
    if (it!=undoables.end()) {
        undoables.erase(it);
    }
}

void RG_UndoGroup::changeUndoState()
{
    for(RG_Undoable* u: undoables) {
        u->changeUndoState();
    }
}

void RG_UndoGroup::clear()
{
    undoables.clear();
}

std::vector<RG_Undoable*> RG_UndoGroup::getUndoables() const
{
    return undoables;
}
