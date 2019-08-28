//
// Created by cipher on 13/07/19.
//

#include "CurrentSource.h"
#include "ResourceManager.h"

void CurrentSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *qg, QWidget *qw) {
    ActiveComponent::paint(painter,qg,qw);
}

CurrentSource::CurrentSource(float value):ActiveComponent(0,1,value) {
    pixmap=ResourceManager::getImage(Component::types::currentSource);
    current=value;
    this->value=value;
    unit="A";
    label="CS";
    myType=currentSource;
}

void CurrentSource::setValue(float value){
    behavior[2]=value;
    current=value;
    this->value=value;
}