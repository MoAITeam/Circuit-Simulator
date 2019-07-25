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



Component::Component(float a,float b,float c,types compType): behavior{a,b,c}, nodes{nullptr, nullptr} {
    setZValue(100);
    setAcceptHoverEvents(true);
    setFlag(ItemIsSelectable,true);
    switch(compType){
        case resistor:
            pixmap=ResourceManager::getImage("resistor");
            break;
        case voltageSource:
            pixmap=ResourceManager::getImage("voltageSource");
            break;
        case currentSource:
            pixmap=ResourceManager::getImage("currentSource");
            break;
        case voltmeter:
            pixmap=ResourceManager::getImage("voltmeter");
            break;
        case wire:
            break;
        default:
            break;
        
    }
}

Component::~Component() {
    if (observer!= nullptr)
    observer->removeNotify(this);
    nodes.first->disconnect(this);
    nodes.second->disconnect(this);
    QPointF length;
    length.setX(qAbs(nodes.first->x()-nodes.second->x()));
    length.setY(qAbs(nodes.first->y()-nodes.second->y()));
    QPointF m=(nodes.first->pos()+nodes.second->pos())/2;
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

void Component::redraw(){
    prepareGeometryChange();
    update();
}

QRectF Component::boundingRect() const {
    QPoint n1(nodes.first->x(),nodes.first->y());
    QPoint n2(nodes.second->x(),nodes.second->y());
    QPoint m=(n1+n2)/2;
    QPoint length;
    length.setX(qAbs(n1.x()-n2.x()));
    length.setY(qAbs(n1.y()-n2.y()));
    //return QRectF(n1,n2).normalized();
    return QRectF(QPointF(m.x()-length.x()/2-50,m.y()-length.y()/2-50),QPointF(m.x()+length.x()/2+200,m.y()+length.y()/2+100));

}

void Component::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

    QPointF center((nodes.first->x()+nodes.second->x())/2, (nodes.first->y()+nodes.second->y())/2);

    if (isSelected()) {
        painter->setPen(QPen(Qt::green, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    }
    QPoint n1(nodes.first->x(),nodes.first->y());
    QPoint n2(nodes.second->x(),nodes.second->y());
    QLineF line(n1,n2);
    bool notImage;
    if(line.length()<100)
        notImage=true;
    else
        notImage=false;

    painter->drawLine(line);


    if(!pixmap.isNull()) {
        float useful_angle = qAtan(qAbs(nodes.first->x()-nodes.second->x()) / qAbs(nodes.first->y()-nodes.second->y())) * 180 / M_PI;
        if ((nodes.second->x() > nodes.first->x() && nodes.second->y() > nodes.first->y()) ||
            (nodes.second->x() < nodes.first->x() && nodes.second->y() < nodes.first->y())) {
            painter->translate(center);
            painter->rotate(-useful_angle);
        } else {
            painter->translate(center);
            painter->rotate(useful_angle);
        }
        if(!notImage)
            painter->drawPixmap(-50, -50, 100, 100, pixmap);
        else
            painter->drawPixmap(-50,-line.length()/2,100,line.length(),pixmap);
    }
    painter->resetTransform();
    painter->translate(center);
    if(hovering) {
        if ((nodes.second->x() > nodes.first->x() && nodes.second->y() > nodes.first->y()) ||
            (nodes.second->x() < nodes.first->x() && nodes.second->y() < nodes.first->y())) {

            painter->setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            QPainterPath path;
            path.addRoundedRect(QRectF(35,-67.5,150,45),10,10);
            QPen pen(Qt::black,1);
            painter->setPen(pen);
            painter->fillPath(path,QColor(220, 245, 247));
            painter->drawPath(path);
            painter->drawText(40,-50, "Current:"+QString().number(current));
            painter->drawText(40, -30, "Voltage:"+QString().number(voltage));

        } else {
            painter->setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            QPainterPath path;
            path.addRoundedRect(QRectF(35,12.5,150,45),10,10);
            QPen pen(Qt::black,1);
            painter->setPen(pen);
            painter->fillPath(path,QColor(220, 245, 247));
            painter->drawPath(path);
            painter->drawText(40, 30, "Current:"+QString().number(current));
            painter->drawText(40, 50, "Voltage:"+QString().number(voltage));

        }

    }

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
    polygon << QPoint(nodes.first->x()-10,nodes.first->y()-10);
    polygon << QPoint(nodes.first->x()+10,nodes.first->y()+10);
    polygon << QPoint(nodes.second->x()+10, nodes.second->y()+10);
    polygon << QPoint(nodes.second->x()-10, nodes.second->y() - 10);
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