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

#include "rg_graphicview.h"

#include "rl_debug.h"
#include "rg_painter.h"
#include "rg_eventhandler.h"
#include "rg_entitycontainer.h"

RG_GraphicView::RG_GraphicView(QWidget *parent)
    : QWidget(parent)
    , eventHandler(new RG_EventHandler(this))
{
    setScale(RG_Vector{1.0, 1.0});
    setOffset(0 ,0);
}

RG_GraphicView::~RG_GraphicView()
{
    if (!overlayEntities.empty()) {
        for (auto a : overlayEntities) {
            delete a;
        }
        overlayEntities.clear();
    }
    if (eventHandler) {
        delete eventHandler;
    }
}

void RG_GraphicView::setContainer(RG_EntityContainer *c)
{
    container = c;
}

void RG_GraphicView::killAllActions()
{
    if (eventHandler) {
        eventHandler->killAllActions();
    }
}
// Смещение начала координат документа относительно левого нижнего угла представления
void RG_GraphicView::setOffset(double ox, double oy)
{
    setOffsetX(ox);
    setOffsetY(oy);
}

void RG_GraphicView::setOffsetX(double ox)
{
    offsetX = ox;
}

void RG_GraphicView::setOffsetY(double oy)
{
    offsetY = oy;
}

double RG_GraphicView::getOffsetX() const
{
    return offsetX;
}

double RG_GraphicView::getOffsetY() const
{
    return offsetY;
}

void RG_GraphicView::setScale(const RG_Vector &sv)
{
    scale = sv;
}

RG_Vector RG_GraphicView::getScale() const
{
    return scale;
}

/**
 * @brief RG_GraphicView::zoomWindow
 * Масштабирует заданную область документа на весь экран
 * @param v1
 * @param v1
 */
void RG_GraphicView::zoomWindow(RG_Vector v1, RG_Vector v2)
{
    if (v1.x > v2.x) {
        std::swap(v1.x, v2.x);
    }
    if (v1.y > v2.y) {
        std::swap(v1.y, v2.y);
    }

    double zoomX = 1000.0;
    double zoomY = 1000.0;

    if (v2.x-v1.x > 1.0e-2) {
        zoomX = getWidth() / (v2.x - v1.x);
    }
    if (v2.y-v1.y > 1.0e-2) {
        zoomY = getHeight() / (v2.y - v1.y);
    }

    // Выберем наименьший масштаб, чтобы веся выбранная область поместилась в окно
    zoomX = std::min(zoomX, zoomY);
    zoomY = zoomX;

    // Вычислим новое смещение
    double halfPixel = 0;//0.5 / zoomX;
    RG_Vector center = RG_Vector((v2.x+v1.x)/2 - halfPixel, (v2.y+v1.y)/2 - halfPixel);
    offsetX = std::round(center.x * zoomX  - getWidth()/2 +.5);
    offsetY = std::round(getHeight()/2 - center.y * zoomY);

    setScale({zoomX, zoomY});

    adjustOffsetControl();

    redraw(RG::RedrawAll);
}

void RG_GraphicView::zoomIn(double zoom, const RG_Vector &center)
{
    // найдем границы отображения в координатах документа
    RG_Vector v1 = toGraph({0.0, getHeight()});
    RG_Vector v2 = toGraph({getWidth(), 0.0});
    RG_Vector pos = toGraph(center);
    // Определим границы отображаемой части документа
    // в соответствии с вычисленным масштабом
    // и положением курсора мыши
    v1 = pos - (pos - v1) * zoom;
    v2 = pos + (v2 - pos) * zoom;
    // применим масштаб
    zoomWindow(v1, v2);    
}

void RG_GraphicView::zoomOut(double zoom, const RG_Vector &center)
{
    // найдем границы отображения в координатах документа
    RG_Vector v1 = toGraph({0.0, getHeight()});
    RG_Vector v2 = toGraph({getWidth(), 0.0});
    RG_Vector pos = toGraph(center);
    // Определим границы отображаемой части документа
    // в соответствии с вычисленным масштабом
    // и положением курсора мыши
    v1 = pos - (pos - v1) / zoom;
    v2 = pos + (v2 - pos) / zoom;
    // применим масштаб
    zoomWindow(v1, v2);
}

void RG_GraphicView::zoomPan(int dx, int dy)
{
    offsetX -= dx;
    offsetY -= dy;

    adjustOffsetControl();
    redraw();
}

// Преобразование координат документа в координаты окна
RG_Vector RG_GraphicView::toGui(const RG_Vector& v) const
{
    return {toGuiX(v.x), toGuiY(v.y)};
}
double RG_GraphicView::toGuiX(const double x) const
{
    return ( x ) * scale.x - offsetX;
}
double RG_GraphicView::toGuiY(const double y) const
{
    return ( - y ) * scale.y + getHeight() - offsetY;
}
double RG_GraphicView::toGuiDX(const double dx) const
{
    return dx * scale.x;
}
double RG_GraphicView::toGuiDY(const double dy) const
{
    return dy * scale.y;
}
// Преобразование координат окна в координаты документа
RG_Vector RG_GraphicView::toGraph(const RG_Vector& v) const
{
    return {toGraphX(std::round(v.x)),
            toGraphY(std::round(v.y))};
}
RG_Vector RG_GraphicView::toGraph(const double x, const double y) const
{
    return {toGraphX(std::round(x)),
            toGraphY(std::round(y))};
}
double RG_GraphicView::toGraphX(const double x) const
{
    return (x + offsetX) / scale.x;
}
double RG_GraphicView::toGraphY(const double y) const
{
    return - ( y - getHeight() + offsetY) / scale.y;
}
double RG_GraphicView::toGraphDX(const double dx) const
{
    return dx / scale.x;
}
double RG_GraphicView::toGraphDY(const double dy) const
{
    return dy / scale.y;
}



void RG_GraphicView::setCurrentAction(RG_ActionInterface *action)
{
    if (eventHandler) {
        eventHandler->setCurrentAction(action);
    }
}

RG_EntityContainer* RG_GraphicView::getOverlayContainer(RG::OverlayGraphics position)
{
    if (overlayEntities[position]) {
        return overlayEntities[position];
    }

    overlayEntities[position] = new RG_EntityContainer(nullptr);
    return overlayEntities[position];
}

void RG_GraphicView::drawLayer2(RG_Painter *painter)
{
    RL_DEBUG << "RG_GraphicView::drawLayer2 Begin";

    foreach (RG_Entity* e, container->getEntityList()) {
        if (!e->isContainer() && (e->isSelected()!=painter->getDrawSelectOnlyMode()))  {
            continue;
        }
        e->draw(painter, this);
    }

    RL_DEBUG << "RG_GraphicView::drawLayer2 Ok";
}

void RG_GraphicView::drawLayer3(RG_Painter *painter)
{
    RL_DEBUG << "RG_GraphicView::drawLayer3 Begin";
    if (overlayEntities.empty()) {
        RL_DEBUG << "Empty";
        return;
    }

    foreach (RG_EntityContainer* oe, overlayEntities) {
        foreach (RG_Entity* e, oe->getEntityList()) {
            RL_DEBUG << e;
            e->draw(painter, this);
        }
    }

    RL_DEBUG << "RG_GraphicView::drawLayer3 Ok";
}


void RG_GraphicView::slotHScrolled(int value)
{
    setOffsetX(value);//*scale.x);
//    adjustOffsetControl();
    redraw();

}

void RG_GraphicView::slotVScrolled(int value)
{
    setOffsetY(value);//*scale.y);
//    adjustOffsetControl();
    redraw();
}

void RG_GraphicView::slotSliderReleased()
{
    RL_DEBUG << "RG_GraphicView::slotSliderReleased()";
    adjustOffsetControl();
}
