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

#ifndef RG_ACTIONINTERFACE_H
#define RG_ACTIONINTERFACE_H

#include <QObject>

#include "rg.h"
#include "rg_snapper.h"

class QMouseEvent;
class QKeyEvent;
class RG_EntityContainer;
class RG_GraphicView;
class RG_Graphic;
class RG_Document;
class RG_CoordinateEvent;

class RG_ActionInterface : public QObject, public RG_Snapper
{
    Q_OBJECT
public:
    explicit RG_ActionInterface(const char* name,
                                RG_EntityContainer& container,
                                RG_GraphicView& graphicView);
    virtual ~RG_ActionInterface();

    virtual void init(int status=0) override;
    virtual void resume();
    virtual void cancelAction();
    void setStatus(int status=0);
    int getStatus();

    virtual void coordinateEvent(RG_CoordinateEvent* ce);

    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void keyPressEvent(QKeyEvent* e);
    virtual void keyReleaseEvent(QKeyEvent* e);
    virtual void updateMouseCursor();

signals:

public slots:

protected:
    const char* name;
    RG_Graphic* graphic;
    RG_Document* document;

    RG::ActionType actionType;
private:
    int status;
};

/**
 * @brief The RG_ISenderAction class
 * Интерфейс класса действия, который принимает данные от дочернего действия
 * Например, RG_ActionEditRotate для выбора сущностей, которых нужно повернуть
 * вызывает действие RG_ActionSelect, которое, если нажата клавиша ESC, должно
 * отменить свое и родительское действие, для этого необходимо передать в
 * родительское действие код завершения
 */
class RG_IRecipientFromChildAction
{
public:
    virtual void setChildActionExitCode(int cod) = 0;
};

#endif // RG_ACTIONINTERFACE_H
