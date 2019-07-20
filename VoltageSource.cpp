//
// Created by cipher on 13/07/19.
//

#include "Node.h"
#include "VoltageSource.h"
#include <QtMath>
#include <iostream>
#include <math.h>


void VoltageSource::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {

    painter->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    Component::paint(painter,qg,qw);
}

