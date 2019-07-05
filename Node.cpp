//
// Created by Sierra on 2019-06-13.
//
#include "Node.h"
#include "Component.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

Node::Node(float x, float y){
    setFlag(ItemIsMovable);
    this->setX(x);
    this->setY(y);
}

Node::~Node(){
    disconnect(); //for signals
    observer->removeNotify(this);
}

void Node::setObserver(NodeObserver *o){
    observer=o;
}

bool Node::operator==(Node& n) {
    return qAbs(x() - n.x()) < (NodeSize) && qAbs(y() - n.y()) < (NodeSize);
}

QRectF Node::boundingRect() const {
    return QRectF( -NodeSize/2, -NodeSize/2, NodeSize, NodeSize);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawEllipse(-NodeSize/2, -NodeSize/2, NodeSize, NodeSize);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button()==Qt::LeftButton) {
        for (auto component : components) {
            component->redraw();
        }
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
    //updateComponents(); to get better drawings, but it's not the point of the demo...
    observer->notify(*this);
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) {
    std::list<Component*> comps=components;
    for(auto &component : comps) {
        disconnectComponent(component);
        delete component;
    }
}

void Node::connectComponent(Component *c) {
    components.push_back(c);
}

void Node::disconnectComponent(Component *c){
    components.remove(c);
}

std::list<Component*> Node::getComponents() {
    return components;
}
