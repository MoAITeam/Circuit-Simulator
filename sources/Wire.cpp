//
// Created by cipher on 13/07/19.
//

#include "Wire.h"

void Wire::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw){

    painter->setPen(QPen(Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    Component::paint(painter,qg,qw);
}