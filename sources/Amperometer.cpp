//
// Created by cipher on 25/07/19.
//

#include "Amperometer.h"
#include "ResourceManager.h"
#include "Node.h"

void Amperometer::paint(QPainter* painter, const QStyleOptionGraphicsItem* qg, QWidget* qw){

    painter->save();
    Component::paint(painter,qg,qw);
    painter->restore();

    QPointF center((nodes.first->x()+nodes.second->x())/2, (nodes.first->y()+nodes.second->y())/2);
    painter->translate(center-pos());
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QFont font=painter->font();
    font.setPixelSize(12);
    painter->setFont(font);
    painter->drawText(-12,5,QString().number(round(current*100)/100)+"A");
}

Amperometer::Amperometer():Component(1,0,0){
    
    voltage=0;
    pixmap=ResourceManager::getImage(Component::types::voltmeter);
}