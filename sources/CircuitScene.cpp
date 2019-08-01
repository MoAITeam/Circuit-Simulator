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

   createItemMenus();

}

void CircuitScene::addNotify(QGraphicsItem *item) {
    if(item->scene()!=this) {
        addItem(item);
    }
}

void CircuitScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    mousePressPoint=Node::toGrid(event->scenePos());
    if(myMode==moveItem)
    QGraphicsScene::mousePressEvent(event);
}

void CircuitScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    mousePressPoint=Node::toGrid(event->scenePos());
    exSel=toComponent(itemAt(mousePressPoint,QTransform()));
    if (exSel!= nullptr)
        exSel->contextMenu->exec(event->screenPos());
}

void CircuitScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
    mouseReleasePoint=Node::toGrid(event->scenePos());
    if(event->button()==Qt::LeftButton) {
        if (myMode == insertItem) {
            if ((mousePressPoint - mouseReleasePoint).manhattanLength() < NodeSize) {
                QPoint defaultPos=QPoint(0,100);
                mousePressPoint = mousePressPoint - defaultPos;
                mouseReleasePoint = mousePressPoint + defaultPos;
            }
            createComponent();
        }
        if (myMode == selectDependent) {
            Component *clicked=toComponent(itemAt(event->scenePos(),QTransform()));
            if (clicked != nullptr) {
                selectedDependent = clicked;
                selectedDependent->setControlled();
                selectedDependent->update();
                myMode = insertItem;
            }
        }
    }
}

void CircuitScene::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key::Key_C)
        circuit->print();
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

void CircuitScene::deleteItem() {
    if(exSel!=nullptr)
        delete exSel;
}

void CircuitScene::changeValue() {
    if (exSel != nullptr) {
        emit insertValue();
        exSel->setValue(cValue);
    }
}

Component* CircuitScene::toComponent(QGraphicsItem* item){
    return dynamic_cast<Component *>(item);
}

void CircuitScene::createComponent() {
    Component *c;

    bool gnd=false;
    switch(myType) {
        case Component::resistor:
            c = new Resistor(cValue);
            c->setMenu(richItemMenu);
            break;
        case Component::voltmeter:
            c = new Voltmeter;
            c->setMenu(itemMenu);
            break;
        case Component::amperometer:
            c=new Amperometer;
            c->setMenu(itemMenu);
            break;
        case Component::voltageSource:
            c = new VoltageSource(cValue);
            c->setMenu(richItemMenu);
            break;
        case Component::currentSource:
            c = new CurrentSource(cValue);
            c->setMenu(richItemMenu);
            break;
        case Component::wire:
            c = new Wire;
            c->setMenu(itemMenu);
            break;
        case Component::vcvs:
            c = new VCVS(cValue,selectedDependent);
            c->setMenu(richItemMenu);
            break;
        case Component::vccs:
            c = new VCCS(cValue,selectedDependent);
            c->setMenu(richItemMenu);
            break;
        case Component::ccvs:
            c = new CCVS(cValue,selectedDependent);
            c->setMenu(richItemMenu);
            break;
        case Component::cccs:
            c = new CCCS(cValue,selectedDependent);
            c->setMenu(richItemMenu);
            break;
        case Component::ground:
            c = new Wire;
            c->setMenu(itemMenu);
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

void CircuitScene::createItemMenus(){
    richItemMenu=new QMenu();
    itemMenu=new QMenu();
    QAction* deleteAction=new QAction(tr("&Delete"),this);
    connect(deleteAction, &QAction::triggered, this, &CircuitScene::deleteItem);
    richItemMenu->addAction(deleteAction);
    itemMenu->addAction(deleteAction);

    QAction* changeAction=new QAction(tr("&Change"),this);
    connect(changeAction, &QAction::triggered, this, &CircuitScene::changeValue);
    richItemMenu->addAction(changeAction);
}