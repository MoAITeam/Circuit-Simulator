//
// Created by Sierra on 2019-06-13.
//
#include "Node.h"
#include "Component.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <iostream>

Node::Node(float x, float y,bool isGround):observer(nullptr),voltage(0),gnd(isGround){
    setFlag(ItemIsMovable);
    this->setX(x);
    this->setY(y);
}

Node::~Node(){
    if(observer!= nullptr)
        observer->removeNotify(this);

    std::list<Component*> toDelete=components;
    for(auto &component : toDelete) {
        delete component;
    }
}

void Node::connect(Component *c) {
    components.push_back(c);
}

void Node::disconnect(Component *c){
    components.remove(c);
}

bool Node::operator==(Node& n) {
    return qAbs(x() - n.x()) < (NodeSize) && qAbs(y() - n.y()) < (NodeSize);
}

void Node::setObserver(NodeObserver *o){
    observer=o;
}

std::list<Component*> Node::getComponents() {
    return components;
}

QRectF Node::boundingRect() const {
    return QRectF( -NodeSize/2, -NodeSize/2, NodeSize, NodeSize);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(gnd)
    painter->setPen(QPen(Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    else
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawEllipse(-NodeSize/2, -NodeSize/2, NodeSize, NodeSize);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    //if(event->button()==Qt::LeftButton) {
        for (auto component : components) {
            component->redraw();
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
    for (auto component : components) {
        component->redraw();
    }
    observer->moveNotify(*this);
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) {
    //if(!gnd)
    delete this;
}

void Node::setVoltage(float value) {
    voltage=value;
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    std::cout<<"Node Voltage:"<<voltage<<std::endl;
    QGraphicsItem::mousePressEvent(event);
}

bool Node::isGround(){
    return gnd;
}