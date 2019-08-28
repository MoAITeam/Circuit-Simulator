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

#define solutionOnTop 300
#define selectedNodesOnTop 400
#define underNode 100
#define nodeOnTop 200



Component::Component(float a,float b,float c, Component* d): behavior{a,b,c}, controller(d) {
    nodes={nullptr, nullptr};
    circuit= nullptr;
    angle=0;
    setZValue(underNode);
    setAcceptHoverEvents(true);
    setFlag(ItemIsSelectable,true);
    setFlag(ItemIsMovable,true);
}

Component::~Component() {
    disconnect();

    if(controller!= nullptr) {
        controller->removeDependent();
        controller->update();
    }
}

void Component::disconnect() { //remove both component and nodes from circuit
    nodes.first->disconnect(this);
    nodes.second->disconnect(this);

    if(nodes.first->getComponents().empty())
        delete nodes.first;
    if(nodes.second->getComponents().empty())
        delete nodes.second;

    nodes.first= nullptr;
    nodes.second= nullptr;

    if (circuit != nullptr) {
        circuit->removeNotify(this);
        circuit = nullptr;
    }
}

void Component::connect(Node* p, Node* n){   //check dependencies then connect the nodes
    if(p!= nullptr && n!=nullptr) {
        Node* save_a= nullptr;
        Node* save_b= nullptr;
        if(nodes.first!= nullptr) {
            save_a=nodes.first;
            nodes.first->disconnect(this);
        }
        if(nodes.second!= nullptr) {
            save_b=nodes.second;
            nodes.second->disconnect(this);
        }
        nodes.first = p;
        nodes.second = n;
        p->connect(this);
        n->connect(this);
        if(save_a!= nullptr)
            if(save_a->getComponents().empty())
                delete save_a;
        if(save_b!= nullptr)
            if(save_b->getComponents().empty())
                delete save_b;
    }
}

void Component::setObserver(ComponentObserver* o){
    circuit=o;
}

nodePair Component::getNodes() {
    return nodes;
}

QRectF Component::boundingRect() const {    //geometric container for component
    QPointF n1(nodes.first->x() - x(), nodes.first->y() - y());
    QPointF n2(nodes.second->x() - x(), nodes.second->y() - y());
    QPointF m = (n1 + n2) / 2;
    QPointF length(qAbs(n1.x() - n2.x()), qAbs(n1.y() - n2.y()));
    QPointF topLeft(m.x() - length.x() / 2 - 50, m.y() - length.y() / 2 - 50);
    QPointF bottomRight(m.x() + length.x() / 2 + 200, m.y() + length.y() / 2 + 100);
    QRectF boundingRect(topLeft, bottomRight);
    return boundingRect;
}

void Component::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

    if (isSelected())
        painter->strokePath(shape().simplified(),selectedPen);

    if (dependentSources>0)
        painter->setPen(controllingPen);
    else
        painter->setPen(componentPen);

    setOrientation();
    drawComponent(painter);
    if(hovering)
        drawSolution(painter);
}

void Component::drawComponent(QPainter* painter){

    painter->save();

    QPointF center=QPointF((nodes.first->x()+nodes.second->x())/2, (nodes.first->y()+nodes.second->y())/2)-pos();
    QPointF n1(nodes.first->x()-x(),nodes.first->y()-y());
    QPointF n2(nodes.second->x()-x(),nodes.second->y()-y());
    QLineF line(n1,n2);

    painter->drawLine(line);
    painter->translate(center);

    if(!pixmap.isNull()) {
        painter->rotate(angle);        //coordinate pixmap with line direction and position
        if (line.length() > 100) {
            painter->drawPixmap(-50, -50, 100, 100, pixmap);  //image as it is
        }
        else {
            painter->drawPixmap(-50,(int) -line.length() / 2, 100,(int) line.length(), pixmap); //scaled
        }
    }

    painter->restore();

}

void Component::drawSolution(QPainter* painter) {      //solution pop-up
    painter->resetTransform();//scene coordinates

    QRectF solRect = QRectF(10,10,150,45);
    QPointF topLeftDisplay=QPointF(15,25);
    QPainterPath path;

    path.addRect(solRect);

    painter->setPen(solutionPen);
    painter->fillPath(path,solutionColor);
    painter->drawPath(path);

    painter->drawText(topLeftDisplay, "Current:"+ QString::number(round(current*100)/100));
    painter->drawText(topLeftDisplay+QPointF(0,20), "Voltage:"+QString::number(round(voltage*100)/100));
}

void Component::setCurrent(float value) {
    current=value;
}

void Component::setVoltage(float value) {
    voltage=value;
}

float Component::getCurrent() {
    return current;
}

float Component::getVoltage() {
    return voltage;
}

QPainterPath Component::shape() const     //define effective interaction area for component -->PATH
{
    QPainterPath path;
    QPolygon polygon;
    QPointF vector=nodes.second->pos()-nodes.first->pos();
    QPointF pVector=QPointF(-vector.y(),vector.x())/sqrt(pow(vector.x(),2)+pow(vector.y(),2))*20;

    polygon << QPoint((nodes.first->pos()-pVector-pos()).toPoint());
    polygon << QPoint((nodes.first->pos()+pVector-pos()).toPoint());
    polygon << QPoint((nodes.second->pos()+pVector-pos()).toPoint());
    polygon << QPoint((nodes.second->pos()-pVector-pos()).toPoint());

    path.addPolygon(polygon);
    return path;
}

void Component::hoverEnterEvent(QGraphicsSceneHoverEvent*){    //These methods define hovering interaction on component
    hovering=true;
    setZValue(solutionOnTop);
    nodes.first->setZValue(selectedNodesOnTop);
    nodes.second->setZValue(selectedNodesOnTop);
}

void Component::hoverLeaveEvent(QGraphicsSceneHoverEvent*){
    hovering=false;
    setZValue(underNode);
    nodes.first->setZValue(nodeOnTop);
    nodes.second->setZValue(nodeOnTop);
}

void Component::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mousePressEvent(event);
    setNodesSelection(true);
    prepareGeometryChange();
}

void Component::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    QGraphicsItem::mouseMoveEvent(event);
    prepareGeometryChange();
}

void Component::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseReleaseEvent(event);
    setNodesSelection(true);
    prepareGeometryChange();
}

void Component::addDependent() {
    dependentSources++;
}

int Component::getSourceType() {
    return sourceType;
}

void Component::removeDependent() {
    dependentSources--;
}


void Component::setOrientation() {   //geometry coordination for component

    Node* p=nodes.first;
    Node* n=nodes.second;

    angle = qAtan(qAbs(p->x()-n->x()) / qAbs(p->y()-n->y())) * 180 / M_PI;
    if ((p->x() < n->x() && p->y() < n->y())||(p->x() > n->x() && p->y() > n->y()))
        angle=-angle;
    if(p->y() > n->y())
        angle=180+angle;
}

void Component::setNodesSelection(bool value){
    nodes.first->setSelected(value);
    nodes.second->setSelected(value);
}

QVariant Component::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    if (change == ItemSelectedHasChanged && scene()) {
        nodes.first->setSelected(this->isSelected());
        nodes.second->setSelected(this->isSelected());
    }
    return QGraphicsItem::itemChange(change, value);
}

const QPixmap &Component::getPixmap() const {
    return pixmap;
}

std::string Component::getData(){
    return std::to_string(myType)+"/"+label.toStdString()+"/0.000/"+std::to_string(nodes.first->x())+"/"+std::to_string(nodes.first->y())+"/"+std::to_string(nodes.second->x())+"/"+std::to_string(nodes.second->y())+"//";
}

QString Component::getLabel(){
    return label;
};

QString Component::getUnit(){
    return unit;
}

void Component::setlabel(QString label){
    this->label=label;
}

float* Component::getBehavior(){
    return behavior;
}