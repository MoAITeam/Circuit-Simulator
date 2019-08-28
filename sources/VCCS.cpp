//
// Created by Sierra on 2019-07-29.
//


#include "VCCS.h"
#include "ResourceManager.h"

VCCS::VCCS(float value,Component *d):ActiveComponent(0,1/value,0,d) {
    pixmap=ResourceManager::getImage(Component::types::vccs);
    sourceType=volts;
    this->value=value;
    unit="x";
    myType=vccs;
    label="VCCS";
}

void VCCS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {
    ActiveComponent::paint(painter,qg,qw);
}