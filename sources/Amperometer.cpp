//
// Created by cipher on 25/07/19.
//

#include "Amperometer.h"

void Amperometer::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw){

    painter->setPen(QPen(Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    Component::paint(painter,qg,qw);
}