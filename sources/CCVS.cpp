//
// Created by Sierra on 2019-07-29.
//

#include "CCVS.h"
#include "ResourceManager.h"

CCVS::CCVS(float value,Component *d):ActiveComponent(1/value,0,0,d) {
    pixmap=ResourceManager::getImage(Component::types::ccvs);
    sourceType=ampere;
    this->value=value;
    unit="number";
}

void CCVS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {

    painter->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    ActiveComponent::paint(painter,qg,qw);
}