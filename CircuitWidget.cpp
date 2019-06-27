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

void CircuitWidget::addItem(Node *node) {
    QObject::connect(node,SIGNAL(positionChanged(Node*)),this,SLOT(linkNode(Node*)));
    scene->addItem(node);
}

void CircuitWidget::removeItem(QGraphicsItem *i){
    scene->removeItem(i);
}

void CircuitWidget::mousePressEvent(QMouseEvent *event) {
    mousePressPoint = event->pos();
    QGraphicsView::mousePressEvent(event);
}

void CircuitWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        Node *a = new Node(mousePressPoint);
        Node *b = new Node(event->pos());
        Component *c = new Component(5);
        circuit->add(c, a, b);
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