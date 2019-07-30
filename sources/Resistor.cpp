//
// Created by cipher on 13/07/19.
//

#include "Resistor.h"

Resistor::Resistor(float res):Component(1,-res,0,resistor){
    resistance=res;

}

void Resistor::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    Component::paint(painter, qg, qw);
}