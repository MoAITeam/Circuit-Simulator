//
// Created by Sierra on 2019-07-28.
//

#include "VCVS.h"

VCVS::VCVS(float value,Component *d):Component(1/value,0,0,vcvs,d) {
s=1;
}

void VCVS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {

    painter->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    Component::paint(painter,qg,qw);
}