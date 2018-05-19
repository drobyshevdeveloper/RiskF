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

#ifndef RG_COORDINATEEVENT_H
#define RG_COORDINATEEVENT_H

#include "rg_vector.h"


class RG_CoordinateEvent
{
public:
    RG_CoordinateEvent(const RG_Vector &pos) :pos(pos) {}

    RG_Vector getCoordinate() {return pos;}

protected:
    RG_Vector pos;
};

#endif // RG_COORDINATEEVENT_H
