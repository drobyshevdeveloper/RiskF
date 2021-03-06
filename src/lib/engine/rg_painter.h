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

#ifndef RG_PAINTER_H
#define RG_PAINTER_H

class RG_Vector;
class RG_Pen;
class QPixmap;
class QRectF;
class QColor;

class RG_Painter
{
public:
    RG_Painter();

    virtual void setPen(RG_Pen& pen) = 0;

    virtual void drawLine(const RG_Vector& p1, const RG_Vector& p2) = 0;
    virtual void drawRect(const QRectF& rect) = 0;
    virtual void fillRect(const QRectF& rect, const QColor& color) = 0;
    virtual void drawPixmap(int x, int y, QPixmap* pixmap) = 0;
    virtual void drawMarker(const RG_Vector& p) = 0;

    /**
     * @brief setDrawSelectOnlyMode -
     * @param smode - true - Режим вывода только выделенных объектов
     *               false - Режим вывода только не выделенных объектов
     */
    void setDrawSelectOnlyMode(bool smode);
    bool getDrawSelectOnlyMode();
private:
    /**
     * @brief bDrawSelectOnlyMode - флаг
     */
    bool bDrawSelectOnlyMode;
};

#endif // RG_PAINTER_H
