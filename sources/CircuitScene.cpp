//
// Created by Sierra on 2019-06-23.
//

#include <fstream>
#include "CircuitScene.h"

#define sceneSize 1100

CircuitScene::CircuitScene(Circuit* c):circuit(c){

    myMode=moveItem;
    myType=Component::types::ground;
    itemMenu=new QMenu();
    richItemMenu=new QMenu();
    selectedDependent= nullptr;//TODO forse posso usarne uno solo?
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
    //FIXME problema con spostamento che torna a 0,0
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

        mouseDragPoint = event->scenePos();
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

void CircuitScene::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key::Key_C)
        circuit->print();
    if(event->key()==Qt::Key::Key_S){
        saveCircuit();
    }
    if(event->key()==Qt::Key::Key_L) {
        loadCircuit();
    }
    if(event->key()==Qt::Key_Backspace)
        for(auto &item : items())
            if(item->isSelected())
                if(item->type()>=Component::component)
                    delete item;
}

void CircuitScene::saveCircuit() {
    std::ofstream out("save.txt");
    for(auto item:items()) {
        if (item->type() == Component::component)
            out << ((Component *) item)->getData() << std::endl;
        if(item->type()==Component::activeComponent)
            out<<((ActiveComponent*)item)->getData()<<std::endl;
    }
}

void CircuitScene::loadCircuit() {
    circuit->clear();
    std::ifstream in("save.txt");
    std::string currentString;
    std::vector<std::string> v;
    std::vector<Component*> toAdd;
    std::vector<nodePair> nodesToAdd;
    std::vector<QString> dependentLabels;
    std::vector<ActiveComponent*> dependentSources;

    while (std::getline(in, currentString)) {
        v.clear();
        std::stringstream ss(currentString);
        while (ss.good()) {
            std::string substr;
            getline(ss, substr, '/');
            v.push_back(substr);
        }

        auto type=Component::types(std::stoi(v[0]));
        QString label=QString::fromStdString(v[1]);
        float value=stof(v[2]);
        float pX=std::stof(v[3]);
        float pY=std::stof(v[4]);
        float nX=std::stof(v[5]);
        float nY=std::stof(v[6]);

        Component *c=initComponent(type);
        c->setlabel(label);

        if(c->type()==Component::activeComponent)
            ((ActiveComponent*)c)->setValue(value);

        if(c->myType>=Component::vcvs) {
            dependentSources.push_back((ActiveComponent *) c);
            dependentLabels.push_back(QString::fromStdString(v[7]));
        }

        auto *p = new Node(Node::toGrid(QPointF(pX, pY)));
        Node* n;
        if(type==Component::ground)
            n = new Node(Node::toGrid(QPointF(nX,nY)),true);
        else
            n = new Node(Node::toGrid(QPointF(nX, nY)));
        toAdd.push_back(c);
        nodePair pair;
        pair.first=p;
        pair.second=n;
        nodesToAdd.push_back(pair);
    }

    int i=0;
    for(auto &c:dependentSources) {
        for(auto &comp:toAdd){
                if(comp->getLabel()==dependentLabels[i]) {
                    c->controller = comp;
                    comp->addDependent();
                }
        }
        i++;
    }
    for(int i=0; i<toAdd.size();i++)
        if(toAdd[i]->myType<Component::vcvs)
            circuit->add(toAdd[i], nodesToAdd[i].first, nodesToAdd[i].second);
    for(int i=0; i<toAdd.size();i++)
        if(toAdd[i]->myType>=Component::vcvs)
            circuit->add(toAdd[i], nodesToAdd[i].first, nodesToAdd[i].second);

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

void CircuitScene::setcName(QString s) {
    cName=s;
}

Circuit* CircuitScene::getCircuit() {
    return circuit;
}

void CircuitScene::deleteItem() {
        delete focus;
}

void CircuitScene::changeValue() {
    if (focus->type()==Component::activeComponent) {
        emit insertValue((ActiveComponent*)focus);
        circuit->update((ActiveComponent*)focus,cValue);
        focus->update();
    }
}

void CircuitScene::changeName() {
    if (focus->type()==Component::activeComponent) {
        emit insertName((ActiveComponent*)focus);
        ((ActiveComponent*)focus)->setlabel(cName);
        focus->update();
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

Component* CircuitScene::initComponent(Component::types type, Component* source) {
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