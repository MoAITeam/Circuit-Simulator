//
// Created by cipher on 13/07/19.
//

#ifndef FIRSTSIMULATORTEST_WIRE_H
#define FIRSTSIMULATORTEST_WIRE_H


#include "Component.h"

class Wire :public Component{

public:
    Wire(bool isGround=false);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
};


#endif //FIRSTSIMULATORTEST_WIRE_H