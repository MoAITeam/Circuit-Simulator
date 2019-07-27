//
// Created by Sierra on 2019-06-23.
//

#include "CircuitScene.h"
#include "Node.h"
#include <iostream>
#include <QtWidgets/QInputDialog>
#include "Resistor.h"
#include "VoltageSource.h"
#include "CurrentSource.h"
#include "Wire.h"
#include "Voltmeter.h"
#include "Amperometer.h"

#define sceneSize 1100

QColor CircuitScene::gridColor = QColor(237,237,237,125);

CircuitScene::CircuitScene(Circuit* c):circuit(c){

    myMode=moveItem;

    setSceneRect(0, 0, sceneSize, sceneSize);
    circuit->setObserver(this);

    for(int x=0; x<=sceneSize; x+=nodeGridSize)
        addLine(x,0,x,1000,QPen(gridColor));

    for(int y=0; y<=sceneSize; y+=nodeGridSize)
        addLine(0,y,sceneSize,y, QPen(gridColor));

}

void CircuitScene::addNotify(QGraphicsItem *item) {
    if(item->scene()!=this) {
        addItem(item);
    }
}

void CircuitScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(myMode==insertItem)
    mousePressPoint=Node::toGrid(event->scenePos());
    if(myMode==moveItem)
    QGraphicsScene::mousePressEvent(event);
}

void CircuitScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
    QPointF mouseReleasePoint=Node::toGrid(event->scenePos());
    if (myMode==insertItem && event->button()==Qt::LeftButton) {
        //Aggiungere il nodo solo se ha senso
        //TODO manhattan
        if(sqrt(pow(mousePressPoint.x()-mouseReleasePoint.x(),2)+pow(mousePressPoint.y()-mouseReleasePoint.y(),2))<NodeSize) {
            mousePressPoint=mousePressPoint+QPoint(0,-100);
            mouseReleasePoint=mousePressPoint+QPoint(0,100);
            //default position
        }
            Component *c;
            switch(myType) {
                case Component::resistor:
                    c = new Resistor(cValue);
                    break;
                case Component::voltmeter:
                    c = new Voltmeter;
                    break;
                case Component::amperometer:
                    c=new Amperometer;
                    break;
                case Component::voltageSource:
                    c = new VoltageSource(cValue);
                    break;
                case Component::currentSource:
                    c = new CurrentSource(cValue);
                    break;
                case Component::wire:
                    c = new Wire;
                    break;
                default:
                    c = nullptr;
            }

            if(c!= nullptr) {
                auto *p = new Node(mousePressPoint);
                auto *n = new Node(mouseReleasePoint);
                circuit->add(c, p, n);
                c->update();
                setMode(CircuitScene::modes(CircuitScene::moveItem));

            }
        }
}

void CircuitScene::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key::Key_C)
        circuit->print();
    if(event->key()==Qt::Key::Key_S)
        circuit->solve();
}

void CircuitScene::setType(Component::types type) {
    myType=type;
}

void CircuitScene::setMode(CircuitScene::modes mode) {
    myMode=mode;
}

void CircuitScene::setcValue(float v) {
    cValue=v;
}

Circuit* CircuitScene::getCircuit() {

    return circuit;
}