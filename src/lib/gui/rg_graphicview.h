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

#ifndef RG_GRAPHICVIEW_H
#define RG_GRAPHICVIEW_H

#include <QWidget>
#include <QMap>

#include "rg.h"

class RG_ActionInterface;
class RG_EntityContainer;
class RG_EventHandler;
class RG_Painter;

class RG_GraphicView : public QWidget
{
    Q_OBJECT
public:
    explicit RG_GraphicView(QWidget *parent = nullptr);

    virtual ~RG_GraphicView();



    void setContainer(RG_EntityContainer* c);
    void setCurrentAction(RG_ActionInterface* action);

    void killAllActions();

    virtual void redraw(RG::RedrawMethod method = RG::RedrawAll) = 0;

    virtual int getWidth() = 0;
    virtual int getHeight() = 0;

    RG_EntityContainer* getOverlayContainer(RG::OverlayGraphics position);

protected:
    void drawLayer2(RG_Painter* painter);
    void drawLayer3(RG_Painter* painter);

signals:

public slots:

protected:
    RG_EntityContainer* container;    // Коллекция всех объектов
    RG_EventHandler*    eventHandler; // получатель сообщений от интерфейса пользователя
private:
    QMap<RG::OverlayGraphics, RG_EntityContainer*> overlayEntities;
};

#endif // RG_GRAPHICVIEW_H
