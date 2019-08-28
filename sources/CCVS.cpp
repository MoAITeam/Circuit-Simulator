//
// Created by Sierra on 2019-07-29.
//

#include "CCVS.h"
#include "ResourceManager.h"

CCVS::CCVS(float value,Component *d):ActiveComponent(1/value,0,0,d) {
    pixmap=ResourceManager::getImage(Component::types::ccvs);
    sourceType=ampere;
    this->value=value;
    myType=ccvs;
    unit="number";
    label="CCVS";
}

void CCVS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {
    ActiveComponent::paint(painter,qg,qw);
}

std::string CCVS::getData(){
    return std::to_string(myType)+"/"+label.toStdString()+"/"+std::to_string(value)+"/"+std::to_string(nodes.first->x())+"/"+std::to_string(nodes.first->y())+"/"+std::to_string(nodes.second->x())+"/"+std::to_string(nodes.second->y())+"/"+controller->getLabel().toStdString()+"/";
}

void CCVS::setValue(float value){
    behavior[0]=1/value;
    this->value=value;
}