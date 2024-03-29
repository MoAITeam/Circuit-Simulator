//
// Created by Sierra on 2019-06-23.
//

#include "CircuitScene.h"

#define sceneSize 1100

CircuitScene::CircuitScene(Circuit* c):circuit(c){

    myMode=moveItem;
    myType=Component::types::ground;
    itemMenu=new QMenu();
    richItemMenu=new QMenu();
    selectedDependent= nullptr;
    focus= nullptr;
    cValue=0;

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
    //propagation is important, I don't want to move nodes if I'm inserting
    if(event->button()==Qt::LeftButton) {

        mousePressPoint = event->scenePos();
        mouseDragPoint=mousePressPoint;

        if(myMode==moveItem) {
            if (itemAt(mousePressPoint, QTransform()) == nullptr)
                selecting = true;
            QGraphicsScene::mousePressEvent(event);
        }
    }else{
        QGraphicsScene::mousePressEvent(event);
    }
}

void CircuitScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button()==Qt::LeftButton) {
        if (myMode == moveItem) {
            mouseDragPoint = event->scenePos();
            //used in draw foreground
        }
        if (selecting) {
            update(QRectF(mousePressPoint, mouseDragPoint).normalized());
        }
    }
    else { //hovering to show solutions
        QGraphicsItem* item=itemAt(event->scenePos(),QTransform());
        if(item!=nullptr)
            item->update();
            //won't show solution otherwise, because this is called first, and the rectangle is not yet drawn
        update(QRectF(display,QSize(200,100)));
    }

    this->update();
    QGraphicsScene::mouseMoveEvent(event);

}

void CircuitScene::drawForeground(QPainter *painter, const QRectF &rect) {
    if (selecting) {
        painter->setPen(QPen(Qt::black, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawRect(QRectF(mousePressPoint, mouseDragPoint));
    }
    QGraphicsScene::drawForeground(painter,rect);
}


void CircuitScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button()==Qt::LeftButton) {

        mouseDragPoint = event->scenePos();            //different behavior due to myMode after release
        QGraphicsItem *clicked;

        if (event->button() == Qt::LeftButton) {
            switch (myMode) {
                case insertItem:
                    if ((mousePressPoint - mouseDragPoint).manhattanLength() < NodeSize*2) {
                        QPoint defaultPos = QPoint(0, 50);
                        createComponent(mousePressPoint-defaultPos,mousePressPoint+defaultPos);
                    } else{
                        createComponent(mousePressPoint,mouseDragPoint);
                    }
                    emit insertedComponent();
                    break;
                case selectDependent:
                    clicked = itemAt(mouseDragPoint, QTransform());
                        if (clicked != nullptr)
                            if (clicked->type() >= Component::component) {
                                selectedDependent = (Component *) clicked;
                                selectedDependent->update();
                                selectedDependent->addDependent();
                                myMode = insertItem;
                            }
                        break;
                case moveItem:
                        if (selecting) {
                            QPainterPath path;
                            QRectF selectionRect=QRectF(mousePressPoint, mouseDragPoint);
                            path.addRect(selectionRect);
                            setSelectionArea(path);
                            update(selectionRect);//rect remains drawn otherwise
                        }
                    break;
            }
            QGraphicsScene::mouseReleaseEvent(event);
            if(!selecting) {
                linkSelectedNodes();//should stay here or you get a bug, caller event destroyed sooner
            }
            selecting = false;
            update(); //for selection area
        }
    } else{
        QGraphicsScene::mouseReleaseEvent(event);
    }
}

void CircuitScene::linkSelectedNodes() {
    for (auto &item : items()) {
        if(item->isSelected()) {
            Node* n=dynamic_cast<Node*>(item);
            if (n!= nullptr) {
                n->checkLink();
            }
        }
    }
}

void CircuitScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {    //mouserightbutton contextmenu
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

void CircuitScene::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key::Key_C)
        circuit->print();
    if(event->key()==Qt::Key_Backspace)
        for(auto &item : items())
            if(item->isSelected())
                if(item->type()>=Component::component)
                    delete item;
}

std::string CircuitScene::getCircuitData() {    //collect data about components and positions
    std::string result;
    for(auto item:items()) {
        if (item->type() == Component::component)
            result+=((Component *) item)->getData();
        if(item->type()==Component::activeComponent)
            result+=((ActiveComponent *) item)->getData();
    }
    return result;
}

void CircuitScene::loadCircuitData(const std::vector<ComponentData> circuitData) {

    circuit->clear();

    std::vector<QString> dependentLabels;
    std::vector<ActiveComponent*> dependentSources;
    std::vector<nodePair> dependentSourcesNodes;

    for(auto const &data:circuitData){

        Component::types type=data.type;                   //analyses a vector of ComponentData,for each one create new components and add them to the circuit

        Component *c=initComponent(type);

        auto *p = new Node(Node::toGrid(QPointF(data.pX, data.pY)));
        Node* n;
        if(type==Component::ground)
            n = new Node(Node::toGrid(QPointF(data.nX,data.nY)),true);
        else
            n = new Node(Node::toGrid(QPointF(data.nX, data.nY)));

        c->setlabel(QString::fromStdString(data.label));

        if(c->type()==Component::activeComponent)
            ((ActiveComponent*)c)->setValue(data.value);

        if(c->getType()>=Component::vcvs) {
            dependentSources.push_back((ActiveComponent *) c);
            dependentLabels.push_back(QString::fromStdString(data.dependent));
            dependentSourcesNodes.emplace_back(nodePair(p,n));
        } else{
            circuit->add(c,p,n);
        }
    }

    int i=0;
    for(auto &c:dependentSources) {               //load dependencies
        for(auto &comp:circuit->getComponents()){
            if(comp->getLabel()==dependentLabels[i]) {
                c->setController(comp);
                comp->addDependent();
            }
        }
            circuit->add(c, dependentSourcesNodes[i].first, dependentSourcesNodes[i].second);
        i++;
    }

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

void CircuitScene::setcName(QString *s) {
    cName=s;
}

Circuit* CircuitScene::getCircuit() {
    return circuit;
}

void CircuitScene::deleteItem() {
        delete focus;
}

void CircuitScene::changeValue() {    //change value of component
    if (focus->type()==Component::activeComponent) {
        emit insertValue((ActiveComponent*)focus);
        circuit->update((ActiveComponent*)focus,cValue);
        focus->update();
    }
}

void CircuitScene::changeName() {   //change name of component
    if (focus->type()==Component::activeComponent) {
        emit insertName((ActiveComponent*)focus);
        ((ActiveComponent*)focus)->setlabel(*cName);
        focus->update();
    }
}


void CircuitScene::disconnectModel() {        //disconnect function: disconnect comp from others
    if (focus->type()>=Component::component) {
        Component* disconnecting=((Component*)focus);
        nodePair pair=disconnecting->getNodes();
        Node* a_saved=new Node(pair.first->x()+20,pair.first->y()+20);
        Node* b_saved=new Node(pair.second->x()+20,pair.second->y()+20);

        disconnecting->disconnect();
        circuit->add(disconnecting,a_saved,b_saved, false);
        update();
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


void CircuitScene::createComponent(QPointF P, QPointF N) {
    Component *c=initComponent(myType,selectedDependent);
    c->setlabel(c->getLabel()+QString::number(labelCount++));
    auto *p = new Node(Node::toGrid(P));
    Node* n;
    if(myType==Component::ground)
        n = new Node(Node::toGrid(N),true);
    else
        n = new Node(Node::toGrid(N));
    circuit->add(c, p, n);
    clearSelection();
    focus=c;
    c->setSelected(true);
    p->setSelected(true);
    n->setSelected(true);
    c->update();
    setMode(CircuitScene::modes(CircuitScene::moveItem));
}

void CircuitScene::createItemMenus(){
    auto* deleteAction=new QAction(tr("&Delete"),this);
    connect(deleteAction, &QAction::triggered, this, &CircuitScene::deleteItem);
    richItemMenu->addAction(deleteAction);
    itemMenu->addAction(deleteAction);

    auto* changeValueAction=new QAction(tr("&Change Value"),this);
    connect(changeValueAction, &QAction::triggered, this, &CircuitScene::changeValue);
    richItemMenu->addAction(changeValueAction);

    auto changeNameAction=new QAction(tr("&Change Name"),this);
    connect(changeNameAction,&QAction::triggered, this, &CircuitScene::changeName);
    richItemMenu->addAction(changeNameAction);

    auto* selectAllAction=new QAction(tr("&Select All"),this);
    connect(selectAllAction, &QAction::triggered, this, &CircuitScene::selectAll);
    sceneMenu->addAction(selectAllAction);

    auto* disconnectModel=new QAction(tr("&Disconnect"),this);
    connect(disconnectModel, &QAction::triggered, this, &CircuitScene::disconnectModel);
    itemMenu->addAction(disconnectModel);
    richItemMenu->addAction(disconnectModel);

}

void CircuitScene::resetExSel() {
    focus= nullptr;
}

Component* CircuitScene::initComponent(Component::types type, Component* source) {    //initializes new component
    Component* c;
    switch(type) {
        case Component::resistor:
            c = new Resistor(100);
            break;
        case Component::voltmeter:
            c = new Voltmeter;
            break;
        case Component::amperometer:
            c=new Amperometer;
            break;
        case Component::voltageSource:
            c = new VoltageSource(10);
            break;
        case Component::currentSource:
            c = new CurrentSource(10);
            break;
        case Component::wire:
            c = new Wire;
            break;
        case Component::vcvs:
            c = new VCVS(1,source);
            break;
        case Component::vccs:
            c = new VCCS(1,source);
            break;
        case Component::ccvs:
            c = new CCVS(1,source);
            break;
        case Component::cccs:
            c = new CCCS(1,source);
            break;
        case Component::ground:
            c = new Wire(true);
            break;
        default:
            c = nullptr;
    }

    return c;
}