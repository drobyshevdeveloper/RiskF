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

#include "rl_dialogfactory.h"

RL_DialogFactory* RL_DialogFactory::uniqInstance = nullptr;

RL_DialogFactory::RL_DialogFactory()
    :factoryObject( nullptr )
{
}

RL_DialogFactory* RL_DialogFactory::instance(void)
{
    if (!uniqInstance)
        uniqInstance = new RL_DialogFactory();
    return uniqInstance;
}
