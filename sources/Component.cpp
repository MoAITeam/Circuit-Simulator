//
// Created by Sierra on 2019-06-13.
//

#include "Component.h"
#include "Node.h"
#include <QGraphicsScene>
#include <iostream>
#include <cmath>
#include <QGraphicsSceneMouseEvent>
#include <QtGui/QtGui>
#include <QLabel>
#include "ResourceManager.h"
#define FLT_EPSILON 0.001
#define solutionOnTop 300
#define underNode 100



Component::Component(float a,float b,float c, Component* d): behavior{a,b,c}, dependent(d), nodes{nullptr, nullptr} {
    setZValue(underNode);
    setAcceptHoverEvents(true);
    setFlag(ItemIsSelectable,true);
    contextMenu=new QMenu();
}

Component::~Component() {
    disconnect();
    if(dependent!= nullptr) {
        dependent->removeControlled();
        dependent->update();
    }
}

void Component::disconnect() {
    if (observer!= nullptr)
        observer->removeNotify(this);
    nodes.first->disconnect(this);
    nodes.second->disconnect(this);
    if (nodes.first->getComponents().size()==0)
        delete nodes.first;
    if (nodes.second->getComponents().size()==0)
        delete nodes.second;
    update();
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

QRectF Component::boundingRect() const {
    QPoint n1(nodes.first->x(),nodes.first->y());
    QPoint n2(nodes.second->x(),nodes.second->y());
    QPoint m=(n1+n2)/2;
    QPoint length(qAbs(n1.x()-n2.x()),qAbs(n1.y()-n2.y()));
    return QRectF(QPointF(m.x()-length.x()/2-50,m.y()-length.y()/2-50),QPointF(m.x()+length.x()/2+200,m.y()+length.y()/2+100));
}

void Component::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

    //Draw box on top
    if(hovering)
        setZValue(solutionOnTop);
    else
        setZValue(underNode);

    //draw selected
    if (isSelected()) {
        painter->setPen(QPen(Qt::green, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
        painter->strokePath(shape().simplified(),painter->pen());
    }
    if (controlled>0)
        painter->setPen(QPen(Qt::darkGreen, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    setOrientation();
    drawComponent(painter);
    drawSolution(painter);

}

void Component::setCurrent(float value) {
    if(abs(value)<FLT_EPSILON)
        current=0;
    else
        current=value;
}

void Component::setVoltage(float value) {
    if(abs(value)<FLT_EPSILON)
        voltage=0;
    else
        voltage=value;
}

float Component::getCurrent() {
    return current;
}

float Component::getVoltage() {
    return voltage;
}

QPainterPath Component::shape() const
{
    QPainterPath path;
    QPolygon polygon;
    polygon << QPoint(nodes.first->x()-20,nodes.first->y());
    polygon << QPoint(nodes.first->x()+20,nodes.first->y());
    polygon << QPoint(nodes.second->x()+20, nodes.second->y());
    polygon << QPoint(nodes.second->x()-20, nodes.second->y());
    path.addPolygon(polygon);
    return path;
}

void Component::hoverEnterEvent(QGraphicsSceneHoverEvent*){
    hovering=true;
    update();
}

void Component::hoverLeaveEvent(QGraphicsSceneHoverEvent*){
    hovering=false;
    update();
}

void Component::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //save initial position
    press=event->pos();
    pressfirst=nodes.first->pos();
    pressecond=nodes.second->pos();
    QGraphicsItem::mousePressEvent(event);
    prepareGeometryChange();
    update();
}

void Component::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    nodes.first->setPos(pressfirst+event->pos()-press);
    nodes.second->setPos(pressecond+event->pos()-press);
    for (auto c : nodes.first->getComponents())
        c->update();
    for (auto c : nodes.second->getComponents())
        c->update();
    QGraphicsItem::mouseMoveEvent(event);
    prepareGeometryChange();
    update();
}

void Component::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    //gridify
    nodes.first->setPos(Node::toGrid(nodes.first->pos()));
    nodes.second->setPos(Node::toGrid(nodes.second->pos()));

    //connect
    nodes.first->checkLink();
    nodes.second->checkLink();
    QGraphicsItem::mouseReleaseEvent(event);
    prepareGeometryChange();
    update();
}

void Component::setControlled() {
    controlled++;
}

int Component::getSourceType() {
    return sourceType;
}

void Component::removeControlled() {
    controlled--;
}

void Component::setMenu(QMenu *m) {
    contextMenu=m;
}

void Component::drawComponent(QPainter* painter){
    QPointF center((nodes.first->x()+nodes.second->x())/2, (nodes.first->y()+nodes.second->y())/2);
    QPoint n1(nodes.first->x(),nodes.first->y());
    QPoint n2(nodes.second->x(),nodes.second->y());
    QLineF line(n1,n2);

    painter->drawLine(line);
    painter->translate(center);

    if(!pixmap.isNull()) {
        painter->rotate(angle);
        if (line.length() > 100)
            painter->drawPixmap(-50, -50, 100, 100, pixmap);  //image as it is
        else
            painter->drawPixmap(-50, -line.length() / 2, 100, line.length(), pixmap); //reduced
        painter->resetTransform(); //reset rotation
        painter->translate(center);
    }
}

void Component::drawSolution(QPainter* painter) {
    if(hovering){
        QPainterPath path;
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        path.addRoundedRect(QRectF(rectLocation.x()-5,rectLocation.y()-17.5,150,45),10,10);
        painter->fillPath(path,QColor(220, 245, 247));
        painter->drawPath(path);
        painter->drawText(rectLocation, "Current:"+QString().number(current));
        painter->drawText(rectLocation+QPointF(0,20), "Voltage:"+QString().number(voltage));
    }
}

void Component::setOrientation() {
    angle = qAtan(qAbs(nodes.first->x()-nodes.second->x()) / qAbs(nodes.first->y()-nodes.second->y())) * 180 / M_PI;
    if ((nodes.second->x() > nodes.first->x() && nodes.second->y() > nodes.first->y())) {
        //quarto
        angle=-angle;
        rectLocation=QPointF(30, -50);
    }
        if((nodes.second->x() < nodes.first->x() && nodes.second->y() < nodes.first->y())){
            //secondo
            angle=180-angle;
            rectLocation=QPointF(30, -50);
        }
    if ((nodes.second->x() < nodes.first->x() && nodes.second->y() > nodes.first->y())) {
        //primo
        angle=angle;
        rectLocation=QPointF(30, 30);
    }
    if ((nodes.second->x() > nodes.first->x() && nodes.second->y() < nodes.first->y())) {
        //terzo
        angle=180+angle;
        rectLocation=QPointF(30, 30);
    }
}