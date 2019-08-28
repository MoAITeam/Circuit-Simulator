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
    unit="x";
    label="CCCS";
}

void CCCS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {
    ActiveComponent::paint(painter,qg,qw);
}

std::string CCCS::getData() {
    return std::to_string(myType)+"/"+label.toStdString()+"/"+std::to_string(value)+"/"+std::to_string(nodes.first->x())+"/"+std::to_string(nodes.first->y())+"/"+std::to_string(nodes.second->x())+"/"+std::to_string(nodes.second->y())+"/"+controller->getLabel().toStdString()+"/";
}

void CCCS::setValue(float value) {
    behavior[1]=1/value;
    this->value=value;
}