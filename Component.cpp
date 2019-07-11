//
// Created by Sierra on 2019-06-13.
//

#include "Component.h"
#include "Node.h"
#include <QPainter>
#include <QGraphicsScene>
#include <iostream>
#include <cmath>
#include <QGraphicsSceneMouseEvent>

Component::Component(float a,float b,float c): behavior{a,b,c}, nodes{nullptr, nullptr} {

}

Component::~Component() {
    if (observer!= nullptr)
    observer->removeNotify(this);
    nodes.first->disconnect(this);
    nodes.second->disconnect(this);
}

void Component::setObserver(ComponentObserver* o){
    observer=o;
}

void Component::connect(Node* p, Node* n){
    if(p!= nullptr && n!=nullptr) {
        if (nodes.first!= nullptr)
        nodes.first->disconnect(this);
        if (nodes.second!= nullptr)
        nodes.second->disconnect(this);
        nodes.first = p;
        nodes.second = n;
        p->connect(this);
        n->connect(this);
    }
}

nodePair Component::getNodes() {
    return nodes;
}

void Component::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) {
    delete this;
}

void Component::redraw(){
    prepareGeometryChange();
    update();
}

QRectF Component::boundingRect() const {
    QPoint n1(nodes.first->x(),nodes.first->y());
    QPoint n2(nodes.second->x(),nodes.second->y());
    return QRectF(n1,n2).normalized();
}

void Component::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    QString value="";
    QPoint n1(nodes.first->x(),nodes.first->y());
    QPoint n2(nodes.second->x(),nodes.second->y());
    QLineF line(n1,n2);

    if (behavior[1]==0) {
        painter->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        value.setNum(behavior[2]);
    }
    else {
        painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        value.setNum(-behavior[1]);
    }
    if (behavior[0]==0) {
        painter->setPen(QPen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        value.setNum(behavior[2]);
    }
    if (behavior[0]==1&&behavior[2]==0&&behavior[1]==0) {
        painter->setPen(QPen(Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        value.setNum(behavior[2]);
    }
    painter->drawLine(line);
    //painter->drawText(this->boundingRect().center(),value);
}

void Component::setCurrent(float value) {
    current=value;
}

void Component::setVoltage(float value) {
    voltage=value;
}

void Component::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    int d1=sqrt(pow(event->pos().x()-nodes.first->x(),2)+pow((event->pos().y()-nodes.first->y()),2));
    int d2=sqrt(pow(event->pos().x()-nodes.second->x(),2)+pow((event->pos().y()-nodes.second->y()),2));
    int length=sqrt(pow(nodes.second->x()-nodes.first->x(),2)+pow((nodes.second->y()-nodes.first->y()),2));
    if(d1+d2<length+5) {
        std::cout << "Current Value:" << current << std::endl;
        std::cout << "Voltage Value:" << voltage << std::endl;
    }
    QGraphicsItem::mousePressEvent(event);

}