
//
// Created by cipher on 25/07/19.
//

#ifndef FIRSTSIMULATORTEST_AMPEROMETER_H
#define FIRSTSIMULATORTEST_AMPEROMETER_H


#include "Component.h"

class Amperometer: public Component{

public:
    Amperometer():Component(1,0,0){};
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
};


#endif //FIRSTSIMULATORTEST_AMPEROMETER_H