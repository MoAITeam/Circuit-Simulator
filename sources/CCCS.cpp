//
// Created by Sierra on 2019-07-29.
//

#include "CCCS.h"
#include "ResourceManager.h"

CCCS::CCCS(float value,Component *d):ActiveComponent(0,1/value,0,d) {
    pixmap=ResourceManager::getImage(Component::types::cccs);
    sourceType=2;
}

void CCCS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {

    painter->setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    Component::paint(painter,qg,qw);
}