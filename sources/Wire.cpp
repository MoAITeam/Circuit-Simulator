//
// Created by cipher on 13/07/19.
//

#include "Wire.h"

void Wire::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw){
    Component::paint(painter,qg,qw);
}

Wire::Wire(bool isGround):Component(1,0,0){
    label="wire";
    if(isGround)
        componentType=ground;
}