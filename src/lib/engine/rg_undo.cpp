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

#include "rg_undo.h"

#include "rl_debug.h"
#include "rg_undogroup.h"
#include "rg_undoable.h"

RG_Undo::RG_Undo()
{
    RL_DEBUG << "RG_Undo::RG_Undo()";
    undoIndex = -1;
    undoList.clear();
}

void RG_Undo::undo()
{
    if (undoIndex < 0) {
        RL_DEBUG << "RG_Undo::undo() Нет элементов в списке Undo";
        return;
    }

    undoList[undoIndex--]->changeUndoState();
}

void RG_Undo::redo()
{
    if (undoIndex+1 >= undoList.size()) {
        RL_DEBUG << "RG_Undo::redo() Нет элементов в списке Undo для повторения";
        return;
    }
    undoList[++undoIndex]->changeUndoState();
}

void RG_Undo::beginUndoGroup()
{
    RL_DEBUG << "RG_Undo::beginUndoGroup() undoList.size() =" << undoList.size();
    while (undoList.size() > undoIndex+1) {
        // Если текущая позиция в списке отмененных операций
        // меньше размера списка Undo (т.е. после отмены нескольких
        // операций вновь происходит изменение документа)
        // необходимо удалить хвост списка Undo и удалить элементы
        std::shared_ptr<RG_UndoGroup> ug = undoList.back();
        for (RG_Undoable* u: ug->getUndoables()) {
            if (u) {
                if (u->isUndone()) {
                    // Удалим все ссылки на сущность из списка Undo
                    // просматриваем все группы, кроме текущей
                    for (auto ug2: undoList) {
                        if (ug2!=ug) {
                            ug2->removeUndoable(u);
                        }
                    }
                    // Удалим сущность из документа
                    removeUndoable(u);
                }
            }
        }
        // Очищаем список одного шага (группы)
        ug->clear();
        // Удаляем один шаг (группу) списка Undo
        undoList.pop_back();
    }

    // Создаем новую группу
    currentGroup = std::make_shared<RG_UndoGroup>();
}

void RG_Undo::endUndoGroup()
{
    if (!currentGroup) {
        RL_DEBUG << "RG_Undo::endUndoGroup() ERROR: currentGroup = nullptr";
        return;
    }

    // записываем группу в список Undo
    addUndoGroup(currentGroup);
    // Создаем новую группу
    currentGroup = std::make_shared<RG_UndoGroup>();
}

void RG_Undo::addUndoable(RG_Undoable* u)
{
    if (!currentGroup) {
        RL_DEBUG << "RG_Undo::addUndoable ERROR: RG_Undoable = nullptr";
        return;
    }
    currentGroup->addUndoable(u);
}

void RG_Undo::addUndoGroup(std::shared_ptr<RG_UndoGroup> ug)
{
    if (!ug) {
        RL_DEBUG << "RG_Undo::addUndoGroup ERROR: RG_UndoGroup = nullptr";
        return;
    }
    undoList.push_back(ug);
    undoIndex++;
}
