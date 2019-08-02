//
// Created by Sierra on 2019-07-25.
//

#ifndef FIRSTSIMULATORTEST_VOLTMETER_H
#define FIRSTSIMULATORTEST_VOLTMETER_H


#include "Component.h"

class Voltmeter : public Component{

public:
    Voltmeter();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override  final;
};


#endif //FIRSTSIMULATORTEST_VOLTMETER_H