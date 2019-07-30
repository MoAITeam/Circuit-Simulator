//
// Created by cipher on 13/07/19.
//

#ifndef FIRSTSIMULATORTEST_RESISTOR_H
#define FIRSTSIMULATORTEST_RESISTOR_H


#include "Component.h"

class Resistor: public Component{

public:
    Resistor(float res);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;



private:
    float resistance;

};


#endif //FIRSTSIMULATORTEST_RESISTOR_H
