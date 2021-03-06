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

#ifndef RG_UNDOABLE_H
#define RG_UNDOABLE_H


class RG_Undoable
{
public:
    RG_Undoable();
    virtual ~RG_Undoable();

    bool isUndone() const {return undoState;}
    void setUndoState(bool undoState);
    void changeUndoState();

    virtual void onChangeUndoState() = 0;
private:
    bool undoState;
};

#endif // RG_UNDOABLE_H
