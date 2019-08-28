//
// Created by cipher on 13/07/19.
//

#include "Resistor.h"
#include "ResourceManager.h"

Resistor::Resistor(float res):ActiveComponent(1,-res,0){
    pixmap=ResourceManager::getImage((Component::types::resistor));
    resistance=res;
    this->value=res;
    unit="Ω";
    myType=resistor;
    label="R";
}

void Resistor::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    ActiveComponent::paint(painter, qg, qw);
}

void Resistor::setValue(float value){
    behavior[1]=-value;
    resistance=value;
    this->value=value;
}