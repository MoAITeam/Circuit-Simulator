//
// Created by cipher on 13/07/19.
//

#include "VoltageSource.h"
#include "ResourceManager.h"
#include "Component.h"

void VoltageSource::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {
    ActiveComponent::paint(painter,qg,qw);
}

VoltageSource::VoltageSource(float value):ActiveComponent(1,0,value) {  //voltage,current,value
    unit="V";
    label="VS";
    pixmap=ResourceManager::getImage(Component::types::voltageSource);
    voltage=value;
    this->value=value;
    myType=voltageSource;
}