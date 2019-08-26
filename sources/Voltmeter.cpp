//
// Created by Sierra on 2019-07-25.
//

#include "Voltmeter.h"
#include "ResourceManager.h"
#include "Node.h"

void Voltmeter::paint(QPainter *painter, const QStyleOptionGraphicsItem *qg, QWidget *qw) {
    painter->save();
    Component::paint(painter,qg,qw);
    painter->restore();

    QPointF center((nodes.first->x()+nodes.second->x())/2, (nodes.first->y()+nodes.second->y())/2);
    painter->translate(center-pos());
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QFont font=painter->font();
    font.setPixelSize(12);
    painter->setFont(font);
    painter->drawText(-12,5," "+QString().number(round(voltage*100)/100)+"V");
}

Voltmeter::Voltmeter():Component(0,1,0) {
    pixmap=ResourceManager::getImage(Component::types::voltmeter);
    current=0;
}