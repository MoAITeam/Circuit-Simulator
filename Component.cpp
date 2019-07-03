//
// Created by Sierra on 2019-06-13.
//

#include "Component.h"
#include "Node.h"
#include <QPainter>
#include <QGraphicsScene>
#include "Circuit.h"

Component::Component(float v): value(v) {

}

Component::~Component() {
    observer->remove(this);
    disconnect();
}

void Component::setObserver(ComponentObserver* o){
    observer=o;
}

void Component::connect(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2){
    if (connected)
            disconnect();
        nodes.first = n1;
        nodes.second = n2;
        n1->connectComponent(this);
        n2->connectComponent(this);
        connected=true;

}

void Component::disconnect() {
    this->nodes.first->disconnectComponent(this);
    this->nodes.second->disconnectComponent(this);
    nodes.first= nullptr;
    nodes.second= nullptr;
    connected= false;
}

QRectF Component::boundingRect() const {
    QPoint n1(nodes.first->x(),nodes.first->y());
    QPoint n2(nodes.second->x(),nodes.second->y());
    return QRectF(n1,n2).normalized();
}

void Component::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPoint n1(nodes.first->x(),nodes.first->y());
    QPoint n2(nodes.second->x(),nodes.second->y());
    QLineF line(n1,n2);

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
}

void Component::redraw(){
    prepareGeometryChange();
    update();
}

std::pair<std::shared_ptr<Node>,std::shared_ptr<Node>> Component::getNodes() {
    return nodes;
}