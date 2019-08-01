//
// Created by Sierra on 2019-07-29.
//

#include "CCVS.h"
#include "ResourceManager.h"

CCVS::CCVS(float value,Component *d):Component(1/value,0,0,d) {
    pixmap=QPixmap(":/images/ccvs.png");
    s=2;
    hasValue=true;
}

void CCVS::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw) {

    painter->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    Component::paint(painter,qg,qw);
}