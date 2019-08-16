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

    const QBrush brush(QImage(":/images/Rect.png"));
    setBackgroundBrush(brush);

    sceneMenu=new QMenu();
    createItemMenus();

}

void CircuitScene::addNotify(QGraphicsItem *item) {
    if(item->scene()!=this) {
        addItem(item);
    }
}

void CircuitScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button()==Qt::LeftButton) {
        mousePressPoint = event->scenePos();
        mouseReleasePoint=mousePressPoint;
        QGraphicsItem *clicked = itemAt(mousePressPoint, QTransform());
            if (clicked== nullptr) {
                selecting = true;
                QGraphicsScene::mousePressEvent(event);
            }
        if (myMode == moveItem) {
            QGraphicsScene::mousePressEvent(event);
            if (clicked != nullptr) {
                if (clicked->type() >= Component::component) {
                    ((Component *) clicked)->getNodes().first->setSelected(true);
                    ((Component *) clicked)->getNodes().second->setSelected(true);
                }
            }
        }
    } else
    {
        QGraphicsScene::mousePressEvent(event);
    }
}

void CircuitScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    mousePressPoint=event->scenePos();
    focus= itemAt(mousePressPoint,QTransform());
    if(focus!= nullptr) {
        switch (focus->type()){
            case Component::component:
                itemMenu->exec(event->screenPos());
                break;
            case Component::activeComponent:
                richItemMenu->exec(event->screenPos());
                break;
        }
    }
        else
            sceneMenu->exec(event->screenPos());

}

void CircuitScene::drawForeground(QPainter *painter, const QRectF &rect) {
    if (selecting) {
        painter->setPen(QPen(Qt::black, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawRect(QRectF(mousePressPoint, mouseReleasePoint));
    }
    QGraphicsScene::drawForeground(painter,rect);
}

void CircuitScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button()==Qt::LeftButton) {
        QGraphicsScene::mouseReleaseEvent(event);
        mouseReleasePoint = event->scenePos();
        if (event->button() == Qt::LeftButton) {
            if (myMode == insertItem) {
                if ((mousePressPoint - mouseReleasePoint).manhattanLength() < NodeSize) {
                    QPoint defaultPos = QPoint(0, 100);
                    mousePressPoint = mousePressPoint - defaultPos;
                    mouseReleasePoint = mousePressPoint + defaultPos;
                }
                createComponent();
            }
            if (myMode == selectDependent) {
                QGraphicsItem *clicked = itemAt(event->scenePos(), QTransform());
                if (clicked != nullptr)
                    if (clicked->type() >= Component::component) {
                        selectedDependent = (Component *) clicked;
                        selectedDependent->update();
                        selectedDependent->setControlled();
                        myMode = insertItem;
                    }
            }
            if (myMode == moveItem) {
                for (auto &item : items()) {
                    if(item->isSelected()==true) {
                        if (item->type() >= Component::component) {
                            //bug fixing
                            if (!((Component *) item)->getNodes().first->isSelected() &&
                                !((Component *) item)->getNodes().second->isSelected()) {
                                ((Component *) item)->getNodes().first->setSelected(true);
                                ((Component *) item)->getNodes().second->setSelected(true);
                            }
                            ((Component *) item)->getNodes().first->checkLink();
                            ((Component *) item)->getNodes().second->checkLink();
                            item->update();
                            selecting = false;
                        }
                    }
                }
                if (selecting) {
                    QPainterPath path;
                    path.addRect(QRectF(mousePressPoint, mouseReleasePoint));
                    setSelectionArea(path);
                    update();
                    selecting = false;
                }
            }
        }
    } else{
        QGraphicsScene::mouseReleaseEvent(event);
    }
}


void CircuitScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button()==Qt::LeftButton) {
        if (myMode == moveItem) {
            mouseReleasePoint = event->scenePos();
        }
    }
    if(selecting)
        update(QRectF(mousePressPoint,mouseReleasePoint).normalized());
    else {
        QGraphicsItem* item=itemAt(event->scenePos(),QTransform());
        if(item!= nullptr)
            item->update();
        update(QRectF(display,QSize(200,100)));
        //update();
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void CircuitScene::keyPressEvent(QKeyEvent *event) {
    //FIXME doesn't work
    /*if(event->key()==Qt::Key::Key_C)
        circuit->print();
    if(event->key()==Qt::Key_Backspace)
        for(auto &item : items())
            if(item->isSelected())
                if(item->type()>=Component::component)
                    delete item;*/
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
    if(focus!=nullptr)
        delete focus;
}

void CircuitScene::changeValue() {
    if (focus->type()==Component::activeComponent) {
        emit insertValue((ActiveComponent*)focus);
        circuit->update((ActiveComponent*)focus,cValue);
    }
}

void CircuitScene::disconnectModel() {
    if (focus->type()>=Component::component) {
        Component* disconnecting=((Component*)focus);
        nodePair pair=disconnecting->getNodes();
        Node* a_saved=new Node(pair.first->x()+20,pair.first->y()+20);
        Node* b_saved=new Node(pair.second->x()+20,pair.second->y()+20);
        disconnecting->disconnect();
        circuit->add(disconnecting,a_saved,b_saved);
        disconnecting->update();
        clearSelection();
        disconnecting->setSelected(true);
    }
}

void CircuitScene::selectAll() {
    for(auto &item : items())
        if (item->type()>=Component::component)
            item->setSelected(true);
}


void CircuitScene::createComponent() {
    Component *c;
    focus=c;
    bool gnd=false;
    switch(myType) {
        case Component::resistor:
            c = new Resistor(100);
            c->setlabel("R "+QString::number(labelCount++));
            break;
        case Component::voltmeter:
            c = new Voltmeter;
            c->setlabel("VM "+QString::number(labelCount++));
            break;
        case Component::amperometer:
            c=new Amperometer;
            c->setlabel("AM "+QString::number(labelCount++));
            break;
        case Component::voltageSource:
            c = new VoltageSource(10);
            c->setlabel("VS "+QString::number(labelCount++));
            break;
        case Component::currentSource:
            c = new CurrentSource(10);
            c->setlabel("CS "+QString::number(labelCount++));
            break;
        case Component::wire:
            c = new Wire;
            break;
        case Component::vcvs:
            c = new VCVS(1,selectedDependent);
            c->setlabel("VCVS "+QString::number(labelCount++));
            break;
        case Component::vccs:
            c = new VCCS(1,selectedDependent);
            c->setlabel("VCCS "+QString::number(labelCount++));
            break;
        case Component::ccvs:
            c = new CCVS(1,selectedDependent);
            c->setlabel("CCVS "+QString::number(labelCount++));
            break;
        case Component::cccs:
            c = new CCCS(1,selectedDependent);
            c->setlabel("CCCS "+QString::number(labelCount++));
            break;
        case Component::ground:
            c = new Wire;
            c->setlabel("wire");
            gnd=true;
            break;
        default:
            c = nullptr;
    }

    if(c!= nullptr) {
        auto *p = new Node(Node::toGrid(mousePressPoint));
        auto *n = new Node(Node::toGrid(mouseReleasePoint),gnd);
        circuit->add(c, p, n);
        clearSelection();
        c->setSelected(true);
        p->setSelected(true);
        n->setSelected(true);
        c->update();
        setMode(CircuitScene::modes(CircuitScene::moveItem));}
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

    QAction* selectAllAction=new QAction(tr("&Select All"),this);
    connect(selectAllAction, &QAction::triggered, this, &CircuitScene::selectAll);
    sceneMenu->addAction(selectAllAction);

    QAction* disconnectModel=new QAction(tr("&Disconnect"),this);
    connect(disconnectModel, &QAction::triggered, this, &CircuitScene::disconnectModel);
    itemMenu->addAction(disconnectModel);
    richItemMenu->addAction(disconnectModel);
}

void CircuitScene::resetExSel() {
    focus= nullptr;
}