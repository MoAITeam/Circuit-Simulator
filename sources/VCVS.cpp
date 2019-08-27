//
// Created by Sierra on 2019-07-28.
//

#include "VCVS.h"
#include "ResourceManager.h"

VCVS::VCVS(float value,Component *d):ActiveComponent(1/value,0,0,d) {
    pixmap=ResourceManager::getImage(Component::types::vcvs);
    sourceType=volts;
    this->value=value;
    unit="number";
    myType=vcvs;
    label="VCVS";
}

void VCVS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {
    ActiveComponent::paint(painter,qg,qw);
}