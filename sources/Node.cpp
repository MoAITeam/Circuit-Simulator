//
// Created by Sierra on 2019-06-13.
//
#include "Node.h"
#include "Component.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <iostream>
#include <cmath>
#define nodeOnTop 200
#define solutionOnTop 400

#include <QApplication>

Node::Node(float x, float y,bool isGround):observer(nullptr),voltage(0),gnd(isGround){
    setAcceptHoverEvents(true);
    setZValue(nodeOnTop);
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setX(x);
    setY(y);
    setSelected(false);
}

Node::~Node(){
    if(observer!= nullptr)
        observer->removeNotify(this);

    std::list<Component*> toDelete=components;
    if(!toDelete.empty())
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
    float xDistance=abs(x() - n.x());
    float yDistance=abs(y() - n.y());
    return xDistance < (NodeSize) && yDistance < (NodeSize);
}

void Node::setObserver(NodeObserver *o){
    observer=o;
}

std::list<Component*> Node::getComponents() {
    return components;
}

QRectF Node::boundingRect() const {
    QPointF topLeft=QPointF(-NodeSize/2.0, -NodeSize/2.0);
    QSize rectSize=QSize(NodeSize,NodeSize);
    QRectF boundingRect= QRectF( topLeft*2,rectSize*2);
    QRectF largeBoundingRect=QRectF( topLeft*6,rectSize*6);
    return gnd ? largeBoundingRect : boundingRect;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(gnd) {
        QPixmap pic(ResourceManager::getImage(Component::types::ground));
        painter->drawPixmap(-15, 0, 30, 20, pic);
    }
    else {
        if(isSelected()) {
            painter->setPen(selectedPen);
            painter->setBrush(QBrush(Qt::gray));
        }
        else {
            painter->setPen(renderPen);
            painter->setBrush(QBrush(Qt::black));
        }
        painter->drawEllipse(-NodeSize / 2, -NodeSize / 2, NodeSize, NodeSize);
    }
    if(hovering)
        paintSolution(painter);
}

void Node::paintSolution(QPainter *painter){
    painter->resetTransform();//scene coordinates

    //QRectF solRect = QRectF(10,10,150,45);
    //QPainterPath path;
    QPointF topLeftDisplay(15,25);

    //path.addRoundedRect(solRect,10,10);

    painter->setPen(solutionPen);
    //painter->fillPath(path,solutionColor);
    //painter->drawPath(path);

    painter->drawText(topLeftDisplay, "Voltage:"+QString::number(round(voltage*100)/100));
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    for (auto component : components) {
        prepareGeometryChange();
        component->update();
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
    checkLink();
}

void Node::checkLink(){
    observer->update(this);
}

void Node::setVoltage(float value) {
        voltage=value;
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mousePressEvent(event);
    if (!(event->modifiers() & Qt::ControlModifier)) {
        for (auto &item : scene()->selectedItems())
            if (item->type() >= Component::component) {
                scene()->clearSelection();
                item->setSelected(false);
            }
    }
}

bool Node::isGround(){
    return gnd;
}

float Node::getVoltage() {
    return voltage;
}

void Node::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    setZValue(solutionOnTop);
    hovering=true;
}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    setZValue(nodeOnTop);
    hovering=false;
}

QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    if(change==ItemPositionChange && scene()){
        QPointF newPos = value.toPointF();
        if(QApplication::mouseButtons()==Qt::LeftButton){
            qreal xV = Node::toGrid(newPos).x();
            qreal yV = Node::toGrid(newPos).y();
            return QPointF(xV,yV);
        }
        else
            return newPos;
    }
    else
        return QGraphicsItem::itemChange(change,value);
}

QPointF Node::toGrid(QPointF n){
    n.setX(round(n.x()/20.0)*20);
    n.setY(round(n.y()/20.0)*20);
    return n;
}
