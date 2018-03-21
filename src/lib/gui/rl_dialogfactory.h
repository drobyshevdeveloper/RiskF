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

#ifndef RL_DIALOGFACTORY_H
#define RL_DIALOGFACTORY_H

#define RL_DIALOGFACTORY RL_DialogFactory::instance()->getFactoryObject()

class RL_DialogFactory;
class RL_DialogFactoryInterface;

class RL_DialogFactory
{
public:
    RL_DialogFactory();

    RL_DialogFactoryInterface* getFactoryObject() {return factoryObject;}
    void setFactoryObject(RL_DialogFactoryInterface* fo) {factoryObject = fo;}
    static RL_DialogFactory* instance(void);
private:
    static RL_DialogFactory* uniqInstance;
    RL_DialogFactoryInterface* factoryObject;
};

#endif // RL_DIALOGFACTORY_H
