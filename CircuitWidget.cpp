//
// Created by Sierra on 2019-06-23.
//

#include "CircuitWidget.h"
#include "Node.h"
#include "Component.h"
#include <iostream>

CircuitWidget::CircuitWidget(Circuit* c):circuit(c){
    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 400, 400);
    circuit->setObserver(this);
    setScene(scene);
}

void CircuitWidget::addNotify(QGraphicsItem *item) {
    if(item->scene()!=this->scene()) {
        scene()->addItem(item);
    }
}

void CircuitWidget::mousePressEvent(QMouseEvent *event) {
    mousePressPoint = event->pos();
    QGraphicsView::mousePressEvent(event);
}

void CircuitWidget::mouseReleaseEvent(QMouseEvent *event) {
    QGraphicsView::mouseReleaseEvent(event);
    if (event->button() == Qt::RightButton) {
        //Aggiungere il nodo solo se ha senso
        if(sqrt(pow(mousePressPoint.x()-event->x(),2)+pow(mousePressPoint.y()-event->y(),2))>NodeSize) {
            auto *c = new Component(0,0,0);
            auto *p = new Node(mousePressPoint.x(), mousePressPoint.y());
            auto *n = new Node(event->x(), event->y());
            circuit->add(c, p, n);
        }
    }
}

void CircuitWidget::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key::Key_C)
        circuit->print();
}