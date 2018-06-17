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

#include <memory>

class RG_Document;
class QPixmap;
class RS_ScrollBar;
class QGridLayout;

class RS_GraphicView : public RG_GraphicView
{
//    Q_OBJECT
public:
    explicit RS_GraphicView(QWidget* parent = 0, Qt::WindowFlags f = 0, RG_Document* doc = 0);
    virtual ~RS_GraphicView();

    void redraw(RG::RedrawMethod method = RG::RedrawAll) override;

    int getWidth()  const override;
    int getHeight() const override;

    /**
     * @brief addScrollbars
     * Добавляет полосы прокрутки к представлению
     */
   void addScrollbars();
   void adjustOffsetControl();

   void setMouseCursor(RG::MouseCursor c) override;


protected:
    void mouseMoveEvent(QMouseEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
    void wheelEvent(QWheelEvent* e) override;

    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;

    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;



private:
    void getPixmapForView(QPixmap **pm);

/*
public slots:
    void slotHScrolled(int value);
    void slotVScrolled(int value);
*/

private:
    RG::RedrawMethod redrawMethod;
    /**
     * @brief layerPixmap1 - буфер окна вывода графики (Основные элементы)
     */
    QPixmap* layerPixmap1;
    /**
     * @brief layerPixmap3 - буфер окна вывода графики (Накладываемый слой)
     */
    QPixmap* layerPixmap3;

    bool bScrollbars;         /// Флаг наличия у представления полос прокрутки
    RS_ScrollBar* hScrollbar; /// Горизонтальная полоса прокрутки
    RS_ScrollBar* vScrollbar; /// Вертикальная полоса прокутки
    QGridLayout*  layout;     /// Компоновщих области окна - сетка (для размещения полос прокрутки)

    // Коллекция курсоров
    std::unique_ptr<QCursor> curCad;
    std::unique_ptr<QCursor> curArrow;
    std::unique_ptr<QCursor> curOpenHand;
    std::unique_ptr<QCursor> curClosedHand;
};

#endif // RS_GRAPHICVIEW_H
