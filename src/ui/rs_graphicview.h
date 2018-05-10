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

#ifndef RS_GRAPHICVIEW_H
#define RS_GRAPHICVIEW_H

#include "rg_graphicview.h"

class RG_Document;
class QPixmap;

class RS_GraphicView : public RG_GraphicView
{
public:
    RS_GraphicView(QWidget* parent = 0, Qt::WindowFlags f = 0, RG_Document* doc = 0);
    virtual ~RS_GraphicView();

    virtual void redraw(RG::RedrawMethod method = RG::RedrawAll) override;

    virtual int getWidth() override;
    virtual int getHeight() override;

protected:
    virtual void mouseMoveEvent(QMouseEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;

    void paintEvent(QPaintEvent* event) override;

private:
    void getPixmapForView(QPixmap **pm);

private:
    RG::RedrawMethod redrawMethod;
    /**
     * @brief layerPixmap3 - буфер окна вывода графики (Накладываемый слой)
     */
    QPixmap* layerPixmap3;
};

#endif // RS_GRAPHICVIEW_H
