//
// Created by Sierra on 2019-06-23.
//

#include "CircuitScene.h"
#include "Node.h"
#include <iostream>
#include "Resistor.h"
#include "VoltageSource.h"
#include "CurrentSource.h"
#include "Wire.h"
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
        if(sqrt(pow(mousePressPoint.x()-mouseReleasePoint.x(),2)+pow(mousePressPoint.y()-mouseReleasePoint.y(),2))>NodeSize) {
            Component *c;
            switch(myType){
                case Component::Resistor:
                    c=new Resistor(10);
                    break;
                case Component::VoltageSource:
                    c=new VoltageSource(10);
                    break;
                case Component::CurrentSource:
                    c=new CurrentSource(10);
                    break;
                case Component::Wire:
                    c= new Wire;
                    break;
                default:
                    c=nullptr;

            }
            if(c!= nullptr) {
                auto *p = new Node(mousePressPoint);
                auto *n = new Node(mouseReleasePoint);

                circuit->add(c, p, n);
                c->update();
            }
        }
    }
}

void CircuitScene::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key::Key_C)
        circuit->print();
    if(event->key()==Qt::Key::Key_S)
        circuit->solve();
    if(event->key()==Qt::Key::Key_M) {
        myMode = moveItem;
    }
}

void CircuitScene::setType(Component::types type) {
    myType=type;
}

void CircuitScene::setMode(CircuitScene::modes mode) {
    myMode=mode;
}