//
// Created by Sierra on 2019-07-28.
//

#include "VCVS.h"
#include "ResourceManager.h"

VCVS::VCVS(float value,Component *d):ActiveComponent(1/value,0,0,d) {
    pixmap=ResourceManager::getImage(Component::types::vcvs);
    sourceType=volts;
    this->value=value;
    unit="x";
    componentType=vcvs;
    label="VCVS";
}

void VCVS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {
    ActiveComponent::paint(painter,qg,qw);
}

void VCVS::setValue(float value){
    behavior[0]=1/value;
    this->value=value;
}
std::string VCVS::getData(){
    return std::to_string(componentType)+"/"
    +label.toStdString()+"/"
    +std::to_string(value)+"/"
    +std::to_string(nodes.first->x())+"/"
    +std::to_string(nodes.first->y())+"/"
    +std::to_string(nodes.second->x())+"/"
    +std::to_string(nodes.second->y())+"/"
    +controller->getLabel().toStdString()+"/";
}