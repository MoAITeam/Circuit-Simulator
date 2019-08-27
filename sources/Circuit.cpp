//
// Created by Sierra on 2019-06-13.
//

#include <QtWidgets/QMessageBox>
#include "Circuit.h"
#include "ModelException.h"

Circuit::Circuit(CircuitObserver *o):observer(o) {

}

Circuit::~Circuit() {
    clear();
}

void Circuit::clear(){
    std::vector<Component*> toDestroy=components;
    for (auto &c : toDestroy) {
        delete c;
    }
}

void Circuit::setObserver(CircuitObserver *o) {
    observer=o;
    for (const auto &component : components) {
        observer->addNotify(component);
        observer->addNotify(component->getNodes().first);
        observer->addNotify(component->getNodes().second);
    }
}

bool Circuit::overlaps(Node* p, Node* n){
    bool result=false;
    for(auto component : components){
        if ((*(p) == *(component->getNodes().first) && *(n)==*(component->getNodes().second))
            ||(*(n) == *(component->getNodes().first) && *(p)==*(component->getNodes().second))) {
            result=true;
        }
    }
    return result;
}

Node* Circuit::getNode(Node* n){
    bool found=false;
    for (auto &node : nodes) {
        if (*n == *node && n != node) {
            delete n;
            n = node;
            found = true;
        }
        if(n==node)
            found=true;
    }
    if (!found){
        if(!n->isGround()) {
            matrix.add();
            notGrounds.push_back(n);
        }

        nodes.push_back(n);
        n->setObserver(this);

        if(observer!=nullptr) {
            observer->addNotify(n);
        }
    }
    return n;
}

void Circuit::add(Component *c, Node*& p, Node*& n) {

    if(p==n)
        throw ModelException("Nodes point to the same memory location, component won't be connected...");

    for (auto &component : components)
        if (c == component)
            throw ModelException("duplicated component won't add it...");

    while(overlaps(p,n)){
        p->setX(p->x() + 30);
        n->setX(n->x() + 30);
    }

    p=getNode(p);
    n=getNode(n);

    components.push_back(c);
    c->setObserver(this);
    if(observer!= nullptr)
        observer->addNotify(c);

    int a=getIndex(p, notGrounds);   //find the indexes of comp'sourceType nodes in the list
    int b=getIndex(n, notGrounds);

    c->connect(p, n);
    if(c->controller==nullptr)
        matrix.add(c->behavior,a,b);
    else
        matrix.add(c->behavior,getIndex(c->controller,components),c->getSourceType(),a,b);

}

void Circuit::checkLink(Node *n) {

    Node *existing = nullptr;
    int instances = 0;

    //The heart of link method: finds the one that is "identical for Node standards" but not the same node
    for (auto &node : nodes) {
        if (*node == *n && node != n) {
            existing = node;
            instances++;
        }
    }

    if (instances <= 1){
        //throw ModelException("found more than one node to connect to, unexpected behavior");

        //bool destroy=false;
        if (existing != nullptr) {
            std::list<Component *> componentsToUpdate = n->getComponents();
            for (auto &component : componentsToUpdate) {
                nodePair pair = component->getNodes();
                Node *keep;
                keep = pair.first == n ? pair.second : pair.first;

                if (!(*keep == *n)) {
                    component->connect(existing, keep);
                    int componentIndex = getIndex(component, components);
                    matrix.update(componentIndex, getIndex(existing, notGrounds), getIndex(keep, notGrounds));
                }
            }
        }
}
    }

template <class T> int Circuit::getIndex(T *x,std::vector<T*> v){
    int result=notFound, count=0, instances=0;
    for (auto &e : v){
        if (e==x) {
            result=count;
            instances++;
        }
        count++;
    }
    if (instances<=1)
        return result;
    else
        throw ModelException("getIndex found duplicated, unexpected behavior");
}

void Circuit::removeNotify(Component *c) {
    matrix.removeComponent(getIndex(c,components));

    for(auto &component : components)
        if(component->controller==c)
            component->controller=nullptr;

    //Implementation of the erase-remove idiom

    auto removeTail=std::remove(components.begin(),components.end(),c); //moves to the end
    if(components.end()-removeTail>1)
        throw ModelException("found more than one component to remove when expected one, undefined behavoir");
    components.erase(removeTail,components.end()); //destroys
}

void Circuit::removeNotify(Node *n) {
    if (!n->isGround())
        matrix.removeNode(getIndex(n, notGrounds));
    auto removeTail = std::remove(nodes.begin(), nodes.end(), n);
    if(nodes.end()-removeTail>1)
        throw ModelException("found more than one node to remove when expected one, undefined behavoir");
    nodes.erase(removeTail,nodes.end());

    removeTail = std::remove(notGrounds.begin(), notGrounds.end(), n);
    notGrounds.erase(removeTail,notGrounds.end());
}
void Circuit::update(Node *drag) {
    checkLink(drag);
}

void Circuit::print(){
    matrix.print();
}

void Circuit::solve(){
    bool atLeastOneGround=false;
    for (auto &n : nodes) {
        if (n->isGround())
            atLeastOneGround = true;
    }

    if(!atLeastOneGround){
        QMessageBox noGnd;
        noGnd.setText("No ground inserted");
        noGnd.exec();
        return;
    }

    std::vector<float> solution=matrix.solve();
    auto comp=components.begin();
    while(comp!=components.end()){
        (*comp)->setVoltage(solution[components.size()-1-(comp-components.begin())]);
        (*comp)->setCurrent(solution[2*components.size()-1-(comp-components.begin())]);
        comp++;
    }
    auto node=notGrounds.begin();
    while(node!=notGrounds.end()){
        (*node)->setVoltage(solution[2*components.size()+(node-notGrounds.begin())]);
        node++;
    }
}

void Circuit::update(ActiveComponent *component,float value) {
    component->setValue(value);
    matrix.update(getIndex((Component*)component,components),component->behavior);
}

SparseMatrix* Circuit::getMatrix() {
    return &matrix;
}
