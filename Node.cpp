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

Node::Node(QPointF point):Node(point.x(),point.y()) {

}

Node::~Node(){
    disconnect(); //for signals
    //if it ever had to get destroyed not regularly
}

void Node::destroy(){
    std::vector<Component*> comps=components;
    for(auto &component : comps) {
        disconnectComponent(component);
        delete component;
    }
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
    for (auto component : components) {
        component->redraw();
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    for (auto component : components) {
        component->redraw();
    }
    QGraphicsItem::mouseReleaseEvent(event);
        observer->link(*this);
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    destroy();
}

void Node::connectComponent(Component *c) {
    components.push_back(c);
}

void Node::disconnectComponent(Component *c){
    for(int i=0; i<components.size(); i++)
        if(components[i]==c)
            components.erase(components.begin()+i);
}

std::vector<Component*> Node::getComponents() {
    return components;
}
