//
// Created by Sierra on 2019-06-23.
//

#include "CircuitScene.h"
#include "Node.h"
#include "Component.h"
#include <iostream>
#include "Resistor.h"


CircuitScene::CircuitScene(Circuit* c):circuit(c){

    setSceneRect(0, 0, 800, 800);
    circuit->setObserver(this);

}

void CircuitScene::addNotify(QGraphicsItem *item) {
    if(item->scene()!=this) {
        addItem(item);
    }
}

void CircuitScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    mousePressPoint = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void CircuitScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
    if (event->button() == Qt::RightButton) {
        //Aggiungere il nodo solo se ha senso
        if(sqrt(pow(mousePressPoint.x()-event->scenePos().x(),2)+pow(mousePressPoint.y()-event->scenePos().y(),2))>NodeSize) {
            auto *r= new Resistor(5);
            auto *p = new Node(mousePressPoint.x(), mousePressPoint.y());
            auto *n = new Node(event->scenePos().x(), event->scenePos().y());
            circuit->add(r, p, n);
            /*QList<QGraphicsItem*> list=QList<QGraphicsItem*>();
            list.append(r);
            list.append(p);
            list.append(n);
            auto *g = QGraphicsScene::createItemGroup(list);
            g->setFlag(QGraphicsItem::ItemIsMovable);
            addItem(g);*/
        }
    }
}

void CircuitScene::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key::Key_C)
        circuit->print();
    if(event->key()==Qt::Key::Key_S)
        circuit->solve();
}