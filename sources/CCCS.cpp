//
// Created by Sierra on 2019-07-29.
//

#include "CCCS.h"
#include "ResourceManager.h"

CCCS::CCCS(float value,Component *d):ActiveComponent(0,1/value,0,d) {
    this->value=value;
    myType=Component::cccs;
    pixmap=ResourceManager::getImage(Component::types::cccs);
    sourceType=ampere;
    unit="number";
    label="CCCS";
}

void CCCS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {
    ActiveComponent::paint(painter,qg,qw);
}