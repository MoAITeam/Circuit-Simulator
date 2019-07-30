//
// Created by Sierra on 2019-06-23.
//

#include "CircuitScene.h"

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
            bool gnd=false;
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
                case Component::vcvs:
                    c = new VCVS(cValue,prev);
                    break;
                case Component::vccs:
                    c = new VCCS(cValue,prev);
                    break;
                case Component::ccvs:
                    c = new CCVS(cValue,prev);
                    break;
                case Component::cccs:
                    c = new CCCS(cValue,prev);
                    break;
                case Component::ground:
                    c = new Wire;
                    gnd=true;
                    break;
                default:
                    c = nullptr;
            }

            if(c!= nullptr) {
                auto *p = new Node(mousePressPoint);
                auto *n = new Node(mouseReleasePoint,gnd);
                circuit->add(c, p, n);
                c->update();
                setMode(CircuitScene::modes(CircuitScene::moveItem));
            }
        }
    if (myMode==selectDependent && event->button()==Qt::LeftButton){
        if(dynamic_cast<Component*>(itemAt(event->scenePos(),QTransform()))!= nullptr) {
            prev = dynamic_cast<Component *>(itemAt(event->scenePos(), QTransform()));
            prev->setControlled();
            prev->update();
            myMode = insertItem;
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