//
// Created by cipher on 13/07/19.
//

#ifndef FIRSTSIMULATORTEST_RESISTOR_H
#define FIRSTSIMULATORTEST_RESISTOR_H


#include "ActiveComponent.h"

class Resistor: public ActiveComponent{

public:
    Resistor(float res);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
    void setValue(float value) override{
        behavior[1]=-value;
        resistance=value;
        this->value=value;
    }

private:
    float resistance;

};


#endif //FIRSTSIMULATORTEST_RESISTOR_H
