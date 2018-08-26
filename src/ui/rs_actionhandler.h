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

#ifndef RS_ACTIONHANDLER_H
#define RS_ACTIONHANDLER_H

#include <QObject>

#include "rg_actioninterface.h"

class RG_GraphicView;
class RG_Document;

class RS_ActionHandler : public QObject
{
    Q_OBJECT
public:
    RS_ActionHandler(QObject *parent);

    /**
     * @brief setCurrentAction - Устанавливает текущее действие
     * @return указатель на объект действия
     */
    RG_ActionInterface* setCurrentAction(RG::ActionType);

    void setView(RG_GraphicView* graphicView);
    void setDocument(RG_Document* document);
signals:

public slots:
    // === Insert ===
    void slotInsertLine(); // временный инструмент
    void slotInsertRoom();
    void slotInsertRectangle();
    void slotInsertPolygon();

    // === Edit ===
    void slotSelect();    // инструмент по умолчанию
    void slotUndo();
    void slotRedo();

private:
    RG_GraphicView* graphicView;
    RG_Document*    document;
};

#endif // RS_ACTIONHANDLER_H
