//
// Created by Sierra on 2019-07-25.
//

#include "Voltmeter.h"

void Voltmeter::paint(QPainter *painter, const QStyleOptionGraphicsItem *qg, QWidget *qw) {

    painter->setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    Component::paint(painter,qg,qw);

}

Voltmeter::Voltmeter():Component(0,1,0,voltmeter) {
    current=0;
}