//
// Created by Sierra on 2019-07-29.
//


#include "VCCS.h"
#include "ResourceManager.h"

VCCS::VCCS(float value,Component *d):ActiveComponent(0,1/value,0,d) {
    pixmap=ResourceManager::getImage(Component::types::vccs);
    sourceType=volts;
    this->value=value;
    unit="number";
    myType=vccs;
    label="VCCS";
}

void VCCS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {
    ActiveComponent::paint(painter,qg,qw);
}

void VCCS::setValue(float value) {
    behavior[1]=1/value;
    this->value=value;
}
std::string VCCS::getData() {
    return std::to_string(myType)+"/"+label.toStdString()+"/"+std::to_string(value)+"/"+std::to_string(nodes.first->x())+"/"+std::to_string(nodes.first->y())+"/"+std::to_string(nodes.second->x())+"/"+std::to_string(nodes.second->y())+"/"+controller->getLabel().toStdString()+"/";
}