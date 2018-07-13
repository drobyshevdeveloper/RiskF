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

#ifndef RG_UNDO_H
#define RG_UNDO_H

#include <vector>
#include <memory>

class RG_UndoGroup;
class RG_Undoable;
#include "rg_undogroup.h"
#include "rg_undoable.h"

class RG_Undo
{
public:
    RG_Undo();

    virtual void undo();
    virtual void redo();

    void beginUndoGroup();
    void endUndoGroup();
    void addUndoable(RG_Undoable* u);
    virtual void removeUndoable(RG_Undoable* u) = 0;
    void addUndoGroup(std::shared_ptr<RG_UndoGroup> ug);


private:
    int undoIndex;
    std::vector<std::shared_ptr<RG_UndoGroup>> undoList;
    std::shared_ptr<RG_UndoGroup> currentGroup;
};

#endif // RG_UNDO_H
