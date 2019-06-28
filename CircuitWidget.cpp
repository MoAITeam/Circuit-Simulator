//
// Created by Sierra on 2019-06-23.
//

#include "CircuitWidget.h"
#include "Node.h"
#include "Component.h"
#include <iostream>

CircuitWidget::CircuitWidget(Circuit* c):circuit(c){
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 400, 400);
    circuit->setObserver(this);
    setScene(scene);
}

CircuitWidget::~CircuitWidget() {
    delete scene;
}

void CircuitWidget::addItem(Component *c) {
    scene->addItem(c);
}

void CircuitWidget::removeItem(Component *c){
    scene->removeItem(c);
}

void CircuitWidget::addItem(Node *node) {
    QObject::connect(node,SIGNAL(positionChanged(Node*)),this,SLOT(linkNode(Node*)));
    scene->addItem(node);
}

void CircuitWidget::removeItem(Node *node){
    this->disconnect(node);
    scene->removeItem(node);
}

void CircuitWidget::mousePressEvent(QMouseEvent *event) {
    mousePressPoint = event->pos();
    QGraphicsView::mousePressEvent(event);
}

void CircuitWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {

        Component *c = new Component(5);
        Node* p=new Node(mousePressPoint.x(), mousePressPoint.y());
        Node* n=new Node(event->pos().x(), event->pos().y());

        circuit->add(c, p, n);
        circuit->print();
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void CircuitWidget::linkNode(Node* n){
    circuit->link(n);
    circuit->print();
}

void CircuitWidget::keyPressEvent(QKeyEvent *event)
{
    std::cout<<"Evento Debug"<<std::endl;
}