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


CircuitScene::CircuitScene(Circuit* c):circuit(c){

    setSceneRect(0, 0, 1000, 1000);
    circuit->setObserver(this);

    for(int x=0; x<=1000; x+=20)
        addLine(x,0,x,1000,QPen(Qt::lightGray));

    for(int y=0; y<=1000; y+=20)
        addLine(0,y,1000,y, QPen(Qt::lightGray));

}

void CircuitScene::addNotify(QGraphicsItem *item) {
    if(item->scene()!=this) {
        addItem(item);
    }
}

void CircuitScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    mousePressPoint.setX(((int)event->scenePos().x()/20)*20);
    mousePressPoint.setY(((int)event->scenePos().y()/20)*20);
    QGraphicsScene::mousePressEvent(event);
}

void CircuitScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
    QPointF mouseReleasePoint;
    mouseReleasePoint.setX(((int)event->scenePos().x()/20)*20);
    mouseReleasePoint.setY(((int)event->scenePos().y()/20)*20);
    QPointF length;
    length.setX(qAbs(mousePressPoint.x()-mouseReleasePoint.x()));
    length.setY(qAbs(mousePressPoint.y()-mouseReleasePoint.y()));
    if (event->button() == Qt::RightButton) {
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
                auto *p = new Node(mousePressPoint.x(), mousePressPoint.y());
                auto *n = new Node(mouseReleasePoint.x(), mouseReleasePoint.y());

                circuit->add(c, p, n);
                QPointF m=(p->pos()+n->pos())/2;
                update(QRectF(QPointF(m.x()-length.x()/2-50,m.y()-length.y()/2-50),QPointF(m.x()+length.x()/2+50,m.y()+length.y()/2+50)));

            }
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