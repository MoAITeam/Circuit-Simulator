//
// Created by Sierra on 2019-07-28.
//

#include "VCVS.h"
#include "ResourceManager.h"

VCVS::VCVS(float value,Component *d):Component(1/value,0,0,d) {
    pixmap=ResourceManager::getImage(vcvs);
    s=1;
    hasValue=true;
}

void VCVS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {

    painter->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    Component::paint(painter,qg,qw);
}