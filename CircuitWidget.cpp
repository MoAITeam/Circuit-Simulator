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
    //TODO maybe redefine QGraphicsScene?
}

void CircuitWidget::addItem(QGraphicsItem *item) {
    if(item->scene()!=this->scene()) {
        scene()->addItem(item);
    }
}

void CircuitWidget::mousePressEvent(QMouseEvent *event) {
    mousePressPoint = event->pos();
    QGraphicsView::mousePressEvent(event);
}

void CircuitWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        QGraphicsView::mouseReleaseEvent(event);

        auto *c = new Component(5);
        circuit->add(c, mousePressPoint.x(), mousePressPoint.y(), event->pos().x(), event->pos().y());
    }
    else
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void CircuitWidget::keyPressEvent(QKeyEvent *event){

}