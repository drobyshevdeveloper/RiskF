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

#ifndef RG_SELECTION_H
#define RG_SELECTION_H

class RG_Entity;
class RG_EntityContainer;
class RG_GraphicView;

class RG_Selection
{
public:
    RG_Selection(RG_EntityContainer* container, RG_GraphicView* graphicView);

    ~RG_Selection() {}

    void singleSelect(RG_Entity* entity);
    void selectAll(bool select=true);
    void deselectAll(){selectAll(false);}
private:
    RG_EntityContainer* container;
    RG_GraphicView* graphicView;
};

#endif // RG_SELECTION_H
