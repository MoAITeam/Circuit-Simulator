//
// Created by Sierra on 2019-06-13.
//

#include "Component.h"
#include "Node.h"
#include <QPainter>

Component::Component(float v): value(v) {

}

bool Component::operator==(Component &c) {
    if (this==&c)
        return true;
    return false;
}

void Component::connect(Node *n1, Node *n2) {
    nodes[0]=n1;
    nodes[1]=n2;
    n1->connectComponent(this);
    n2->connectComponent(this);
}

void Component::disconnect() {
    this->nodes[0]->disconnectComponent(this);
    this->nodes[1]->disconnectComponent(this);
    nodes[0]= nullptr;
    nodes[1]= nullptr;
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

void Component::update(const QRectF &rect) {
    prepareGeometryChange();
    QGraphicsItem::update(rect);
}

std::vector<Node*> Component::getNodes() {
    return nodes;
}