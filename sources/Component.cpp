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



Component::Component(float a,float b,float c,types compType, Component* d): behavior{a,b,c}, dependent(d), nodes{nullptr, nullptr} {
    setZValue(100);
    setAcceptHoverEvents(true);
    setFlag(ItemIsSelectable,true);
    setImage(compType);
    contextMenu=new QMenu();
}

void Component::copy(Component *c) {
    /*//non copio i nodi
    for (int i=0; i<3; i++)
    behavior[i]=c->behavior[i];
    //dependent=c->dependent;
    if(dependent!= nullptr)
        dependent->setControlled();
    current=c->current;
    voltage=c->voltage;
    //QPixmap pic=c->pixmap;
    //pixmap=pic;
    //observer=c->observer;
    //TODO menu su costruttore?
    //controlled=c->controlled;
    s=c->s;*/
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

void Component::redraw(){
    prepareGeometryChange();
    update();
}

QRectF Component::boundingRect() const {
    QPoint n1(nodes.first->x(),nodes.first->y());
    QPoint n2(nodes.second->x(),nodes.second->y());
    QPoint m=(n1+n2)/2;
    QPoint length(qAbs(n1.x()-n2.x()),qAbs(n1.y()-n2.y()));
    return QRectF(QPointF(m.x()-length.x()/2-50,m.y()-length.y()/2-50),QPointF(m.x()+length.x()/2+200,m.y()+length.y()/2+100));
}

void Component::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

    QPointF center((nodes.first->x()+nodes.second->x())/2, (nodes.first->y()+nodes.second->y())/2);
    QPainterPath path;
    QPointF text;

    //draw selected
    if (isSelected()) {
        painter->setPen(QPen(Qt::green, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
        painter->strokePath(shape().simplified(),painter->pen());
    }
    if (controlled>0)
        painter->setPen(QPen(Qt::darkGreen, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    //draw line
    QPoint n1(nodes.first->x(),nodes.first->y());
    QPoint n2(nodes.second->x(),nodes.second->y());
    QLineF line(n1,n2);

    painter->drawLine(line);
    painter->translate(center);

    //Context
        float angle = qAtan(qAbs(nodes.first->x()-nodes.second->x()) / qAbs(nodes.first->y()-nodes.second->y())) * 180 / M_PI;
        if ((nodes.second->x() > nodes.first->x() && nodes.second->y() > nodes.first->y()) ||
            (nodes.second->x() < nodes.first->x() && nodes.second->y() < nodes.first->y())) {
            angle=-angle;
            if(hovering) {
                path.addRoundedRect(QRectF(25, -67.5, 150, 45), 10, 10);
                text = QPointF(30, -50);
            }
        } else {
            if(hovering){
                path.addRoundedRect(QRectF(25,12.5,150,45),10,10);
                text=QPointF(30,30);
            }
        }

        //draw picture
    if(!pixmap.isNull()) {
        painter->rotate(angle);
        if (line.length() > 100)
            painter->drawPixmap(-50, -50, 100, 100, pixmap);  //image as it is
        else
            painter->drawPixmap(-50, -line.length() / 2, 100, line.length(), pixmap); //reduced
        painter->resetTransform(); //reset rotation
        painter->translate(center);
    }

    //draw solution
    if(hovering){
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->fillPath(path,QColor(220, 245, 247));
        painter->drawPath(path);
        painter->drawText(text, "Current:"+QString().number(current));
        painter->drawText(text+QPointF(0,20), "Voltage:"+QString().number(voltage));
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
    redraw();
}

void Component::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    nodes.first->setPos(pressfirst+event->pos()-press);
    nodes.second->setPos(pressecond+event->pos()-press);
    QGraphicsItem::mouseMoveEvent(event);
    redraw();
}

void Component::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    //gridify
    nodes.first->setPos(Node::toGrid(nodes.first->pos()));
    nodes.second->setPos(Node::toGrid(nodes.second->pos()));

    //connect
    nodes.first->checkLink();
    nodes.second->checkLink();
    QGraphicsItem::mouseReleaseEvent(event);
    redraw();
}

void Component::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    scene()->clearSelection();
    setSelected(true);
    contextMenu->exec(event->screenPos());
}

void Component::setImage(types compType){
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
        case ground:
            break;
        case wire:
            break;
        case vcvs:
            pixmap=ResourceManager::getImage("vcvs");
            break;
        case vccs:
            pixmap=ResourceManager::getImage("vccs");
            break;
        case ccvs:
            pixmap=ResourceManager::getImage("ccvs");
            break;
        case cccs:
            pixmap=ResourceManager::getImage("cccs");
            break;
        default:
            break;

    }
}

void Component::setControlled() {
    controlled++;
}

void Component::removeControlled() {
    controlled--;
}

void Component::setMenu(QMenu *m) {
    contextMenu=m;
}