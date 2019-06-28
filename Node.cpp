//
// Created by Sierra on 2019-06-13.
//
#include "Node.h"
#include "Component.h"
#include <QPainter>

Node::Node(float x, float y){
    setFlag(ItemIsMovable);
    this->setX(x);
    this->setY(y);
}

Node::Node(QPointF point):Node(point.x(),point.y()) {

}

bool Node::operator==(Node& n) {
    if (qAbs(this->x()-n.x())<(NodeSize)&&qAbs(this->y()-n.y())<(NodeSize))
        return true;
    else {
        return false;
    }
}

QRectF Node::boundingRect() const {
    return QRectF( -NodeSize/2, -NodeSize/2, NodeSize, NodeSize);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawEllipse(-NodeSize/2, -NodeSize/2, NodeSize, NodeSize);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
    emit positionChanged(this);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    for (auto component : components) {
        component->update();
    }
    QGraphicsItem::mouseMoveEvent(event);
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