//
// Created by Sierra on 2019-06-13.
//

#include "Component.h"
#include "Node.h"
#include <QPainter>
#include <QGraphicsScene>

Component::Component(float v): value(v), nodes{nullptr, nullptr} {

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
    QPoint n1(nodes.first->x(),nodes.first->y());
    QPoint n2(nodes.second->x(),nodes.second->y());
    QLineF line(n1,n2);

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
}