//
// Created by Sierra on 2019-07-29.
//

#include "CCCS.h"
#include "ResourceManager.h"

CCCS::CCCS(float value,Component *d):ActiveComponent(0,1/value,0,d) {
    this->value=value;
    pixmap=ResourceManager::getImage(Component::types::cccs);
    sourceType=ampere;
    unit="number";
}

void CCCS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {

    painter->setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    Component::paint(painter,qg,qw);
}