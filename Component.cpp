//
// Created by Sierra on 2019-06-13.
//

#include "Component.h"
#include "Node.h"
#include <QPainter>
#include <QGraphicsScene>

Component::Component(float v): value(v) {

}

Component::~Component() {
    //FIXME something that actually works
    //scene()->removeItem(this);
}

bool Component::operator==(Component &c) {
    if (this==&c)
        return true;
    return false;
}

void Component::connect(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2){
    if (connected)
            disconnect();
        nodes[0] = n1;
        nodes[1] = n2;
        n1->connectComponent(this);
        n2->connectComponent(this);
        connected=true;
}

void Component::disconnect() {
    this->nodes[0]->disconnectComponent(this);
    this->nodes[1]->disconnectComponent(this);
    nodes[0]= nullptr;
    nodes[1]= nullptr;
    connected= false;

}

QRectF Component::boundingRect() const {
    QPoint n1(nodes[0]->x(),nodes[0]->y());
    QPoint n2(nodes[1]->x(),nodes[1]->y());
    return QRectF(n1,n2).normalized();
}

void Component::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPoint n1(nodes[0]->x(),nodes[0]->y());
    QPoint n2(nodes[1]->x(),nodes[1]->y());
    QLineF line(n1,n2);

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
}

void Component::prepare(){
    prepareGeometryChange();
}

std::shared_ptr<Node> Component::getNode(int i) {
    return nodes[i];
}