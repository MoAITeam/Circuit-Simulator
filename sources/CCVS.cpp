//
// Created by Sierra on 2019-07-29.
//

#include "CCVS.h"

CCVS::CCVS(float value,Component *d):Component(1/value,0,0,ccvs,d) {
    s=2;
}

void CCVS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {

    painter->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    Component::paint(painter,qg,qw);
}