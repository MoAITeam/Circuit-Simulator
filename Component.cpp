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
    observer->removeNotify(this);
    nodes.first->disconnectComponent(this);
    nodes.second->disconnectComponent(this);
}

void Component::setObserver(ComponentObserver* o){
    observer=o;
}

void Component::connect(std::shared_ptr<Node> p, std::shared_ptr<Node> n){
    if(p!= nullptr && n!=nullptr) { //Exactly disconnecting but keeping in the view and in the component vector in circuit
        if (nodes.first != nullptr)
            nodes.first->disconnectComponent(this);
        if (nodes.second != nullptr)
            nodes.second->disconnectComponent(this);
        nodes.first = p;
        nodes.second = n;
        p->connectComponent(this);
        n->connectComponent(this);
    }
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

void Component::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) {
    delete this;
}

void Component::redraw(){
    prepareGeometryChange();
    update();
}

nodePair Component::getNodes() {
    return nodes;
}