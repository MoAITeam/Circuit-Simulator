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
#include "CircuitScene.h"

#define FLT_EPSILON 0.001
#define solutionOnTop 300
#define selectedNodesOnTop 400
#define underNode 100
#define nodeOnTop 200



Component::Component(float a,float b,float c, Component* d): behavior{a,b,c}, dependent(d), nodes{nullptr, nullptr} {
    setZValue(underNode);
    setAcceptHoverEvents(true);
    setFlag(ItemIsSelectable,true);
    setFlag(ItemIsMovable,true);
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
    update(); //FIXME maybe not here if I only disconnect model
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
    QPoint n1(nodes.first->x()-x(),nodes.first->y()-y());
    QPoint n2(nodes.second->x()-x(),nodes.second->y()-y());
    QPoint m=(n1+n2)/2;
    QPoint length(qAbs(n1.x()-n2.x()),qAbs(n1.y()-n2.y()));
    return QRectF(QPointF(m.x()-length.x()/2-50,m.y()-length.y()/2-50),QPointF(m.x()+length.x()/2+200,m.y()+length.y()/2+100));
}

void Component::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

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
    //FIXME duplicated but fixes bug of showing wrong rect first
    float angle = qAtan(qAbs(nodes.first->x()-nodes.second->x()) / qAbs(nodes.first->y()-nodes.second->y())) * 180 / M_PI;
    if ((nodes.second->x() > nodes.first->x() && nodes.second->y() > nodes.first->y())) {
        angle=-angle;
    }
    if((nodes.second->x() < nodes.first->x() && nodes.second->y() < nodes.first->y())){
        angle=180-angle;
    }
    if ((nodes.second->x() > nodes.first->x() && nodes.second->y() < nodes.first->y())) {
        angle=180+angle;
    }
    angle=this->angle/360*2*M_PI;
    polygon << QPoint(nodes.first->x()-20*cos(angle)-x(),nodes.first->y()-20*sin(angle)-y());
    polygon << QPoint(nodes.first->x()+20*cos(angle)-x(),nodes.first->y()+20*sin(angle)-y());
    polygon << QPoint(nodes.second->x()+20*cos(angle)-x(), nodes.second->y()+20*sin(angle)-y());
    polygon << QPoint(nodes.second->x()-20*cos(angle)-x(), nodes.second->y()-20*sin(angle)-y());
    path.addPolygon(polygon);
    return path;
}

void Component::hoverEnterEvent(QGraphicsSceneHoverEvent*){
    hovering=true;
    setZValue(solutionOnTop);
    nodes.first->setZValue(selectedNodesOnTop);
    nodes.second->setZValue(selectedNodesOnTop);
    update();
}

void Component::hoverLeaveEvent(QGraphicsSceneHoverEvent*){
    hovering=false;
    setZValue(underNode);
    nodes.first->setZValue(nodeOnTop);
    nodes.second->setZValue(nodeOnTop);
    update();
}

void Component::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mousePressEvent(event);
    prepareGeometryChange();
    update();
}

void Component::mouseMoveEvent(QGraphicsSceneMouseEvent* event){

    QGraphicsItem::mouseMoveEvent(event);
    prepareGeometryChange();
    update();
}

void Component::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
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
    QPoint n1(nodes.first->x()-x(),nodes.first->y()-y());
    QPoint n2(nodes.second->x()-x(),nodes.second->y()-y());
    QLineF line(n1,n2);

    painter->drawLine(line);
    painter->translate(center-pos());

    if(!pixmap.isNull()) {
        if (type()==activeComponent){//TODO make a function
            QFont font=painter->font();
            font.setBold(true);
            painter->setFont(font);
            painter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter->drawText(rectLocation, label);
            font.setBold(false);
            painter->setFont(font);
            painter->drawText(rectLocation+QPointF(0,20),QString::number(((ActiveComponent*)this)->value)+unit);//FIXME brutto forte
        }
        painter->rotate(angle);
        if (line.length() > 100)
            painter->drawPixmap(-50, -50, 100, 100, pixmap);  //image as it is
        else
            painter->drawPixmap(-50, -line.length() / 2, 100, line.length(), pixmap); //reduced
        painter->resetTransform(); //reset rotation
        painter->translate(center-pos());
    }
}

void Component::drawSolution(QPainter* painter) {
    painter->resetTransform();
    if(hovering){
        QPainterPath path;
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        //path.addRoundedRect(QRectF(rectLocation.x()-5,rectLocation.y()-17.5,150,45),10,10);
        path.addRoundedRect(QRectF(10,10,150,45),10,10);
        painter->fillPath(path,QColor(220, 245, 247));
        painter->drawPath(path);
        painter->drawText(QPointF(15,25), "Current:"+QString().number(round(current)));
        painter->drawText(QPointF(15,25)+QPointF(0,20), "Voltage:"+QString().number(round(voltage)));
    }
}

void Component::setOrientation() {
    angle = qAtan(qAbs(nodes.first->x()-nodes.second->x()) / qAbs(nodes.first->y()-nodes.second->y())) * 180 / M_PI;
    rectLocation=QPointF(-60, -60);//sennò primo stampa sopra componente
    if ((nodes.second->x() > nodes.first->x() && nodes.second->y() > nodes.first->y())) {
        //quarto
        angle=-angle;
        rectLocation=QPointF(-60, -60);
    }
        if((nodes.second->x() < nodes.first->x() && nodes.second->y() < nodes.first->y())){
            //secondo
            angle=180-angle;
            rectLocation=QPointF(-60, -60);
        }
    if ((nodes.second->x() < nodes.first->x() && nodes.second->y() > nodes.first->y())) {
        //primo
        rectLocation=QPointF(-60, -60);
    }
    if ((nodes.second->x() > nodes.first->x() && nodes.second->y() < nodes.first->y())) {
        //terzo
        angle=180+angle;
        rectLocation=QPointF(-60, -60);
    }
}

