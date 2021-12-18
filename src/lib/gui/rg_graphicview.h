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
#include "rg_vector.h"

class RG_ActionInterface;
class RG_EntityContainer;
class RG_EventHandler;
class RG_Painter;
class RG_Entity;

class RG_GraphicView : public QWidget
{
    Q_OBJECT
public:
    explicit RG_GraphicView(QWidget *parent = nullptr);

    virtual ~RG_GraphicView();



    void setContainer(RG_EntityContainer* c);
    void setCurrentAction(RG_ActionInterface* action);
    virtual void onChangedAction();

    void killAllActions();

    virtual void adjustOffsetControl() = 0;
    virtual void redraw(RG::RedrawMethod method = RG::RedrawAll) = 0;

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual void setMouseCursor(RG::MouseCursor c) = 0;
    /**
     * @brief setOffset
     * Установить смещение  начала координат документа
     * относительно левого нижнего угла представления
     * @param ox - смещение по горизонтали в экранных координатах
     * @param oy - смещение по вертикали в экранных координатах
     */
    void setOffset(double ox, double oy);
    void setOffsetX(double ox);
    void setOffsetY(double oy);
    double getOffsetX() const;
    double getOffsetY() const;
    // Установить масштаб отображения
    void setScale(const RG_Vector& sv);
    RG_Vector getScale() const;
    // Масштабирует заданную область документа на весь экран
    void zoomWindow(RG_Vector v1, RG_Vector v2);
    void zoomWindowGui(RG_Vector v1, RG_Vector v2);
    // Инструменты масштабирования
    void zoomIn(double zoom, const RG_Vector& center);
    void zoomOut(double zoom, const RG_Vector& center);
    void zoomPan(int dx, int dy);

    // Преобразование координат документа в координаты окна
    RG_Vector toGui(const RG_Vector& v) const;
    double toGuiX(const double x) const;
    double toGuiY(const double y) const;
    double toGuiDX(const double dx) const;
    double toGuiDY(const double dy) const;
    // Преобразование координат окна в координаты документа
    RG_Vector toGraph(const RG_Vector& v) const;
    RG_Vector toGraph(const double x, const double y) const;
    double toGraphX(const double x) const;
    double toGraphY(const double y) const;
    double toGraphDX(const double dx) const;
    double toGraphDY(const double dy) const;


    RG_EntityContainer* getOverlayContainer(RG::OverlayGraphics position);

    void drawEntity(RG_Painter* painter, RG_Entity* e);

protected:
    void drawLayer2(RG_Painter* painter);
    void drawLayer3(RG_Painter* painter);

    // ==========================================================
    // Механизм стабилизации представления при изменении масштаба
    /**
     * @brief saveOffsetPosition
     * Сохраняет позицию экрана и соответствующую позицию документа
     * @param pos - экранная позиция, по которой будет проводится синхронизация
     */
    void saveOffsetPosition(const RG_Vector& pos);
    /**
     * @brief resetOffsetPosition
     * Сбрасывает сохраненные позиции экрана
     */
    void resetOffsetPosition();
    /**
     * @brief syncOffsetPosition
     * Синхронизирует представление с сохраненными позициями
     */
    void syncOffsetPosition();

signals:

public slots:
    void slotHScrolled(int value);
    void slotVScrolled(int value);
    void slotSliderReleased();

protected:
    RG_EntityContainer* container;    // Коллекция всех объектов
    RG_EventHandler*    eventHandler; // получатель сообщений от интерфейса пользователя
    // Смещение начала координат документа относительно левого нижнего угла представления
    double offsetX;
    double offsetY;
    // Масштаб отображения
    RG_Vector scale;
private:
    std::map<RG::OverlayGraphics, RG_EntityContainer> overlayEntities;
    // Переменные механизма стабилизации представления при изменении масштаба
    RG_Vector vGui   = RG_Vector(false);
    RG_Vector vGraph = RG_Vector(false);
};

#endif // RG_GRAPHICVIEW_H
