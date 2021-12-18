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

#ifndef RU_MDIWINDOW_H
#define RU_MDIWINDOW_H

#include <QMdiSubWindow>

class QMdiArea;
class RG_Document;
class RG_Graphic;
class RS_GraphicView;

class RU_MDIWindow : public QMdiSubWindow
{
public:
    RU_MDIWindow(RG_Document* doc,
                 QWidget* parent,
                 Qt::WindowFlags wflags={});
    virtual ~RU_MDIWindow();


    RS_GraphicView* getGraphicView() const;

    RG_Document* getDocument() const;

    RG_Graphic* getGraphic() const;

private:
    /* window id */
    unsigned int id;
    static unsigned int idCounter;

    QMdiArea* cadMDIArea;
    RG_Document* document;
    RS_GraphicView* graphicView;
    /**
     * @brief owner: true  - документ создан в окне
     *               false - готовый документ передан в окно
     */
    bool owner;
};

#endif // RU_MDIWINDOW_H
