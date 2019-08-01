//
// Created by Sierra on 2019-07-29.
//


#include "VCCS.h"
#include "ResourceManager.h"

VCCS::VCCS(float value,Component *d):Component(0,1/value,0,d) {
    pixmap=ResourceManager::getImage(Component::types::vccs);
    sourceType=1;
}

void VCCS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {

    painter->setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    Component::paint(painter,qg,qw);
}