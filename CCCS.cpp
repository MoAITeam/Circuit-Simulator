//
// Created by Sierra on 2019-07-29.
//

#include "CCCS.h"

CCCS::CCCS(float value,Component *d):Component(0,1/value,0,cccs,d) {
    s=2;
}

void CCCS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {

    painter->setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    Component::paint(painter,qg,qw);
}