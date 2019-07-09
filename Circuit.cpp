//
// Created by Sierra on 2019-06-13.
//

#include "Circuit.h"
//TODO: node should be abstract non inheriting from QGraphicsItem

Circuit::Circuit(CircuitObserver *o):observer(o) {

}

Circuit::~Circuit() {
    std::list<Component*> toUpdate=components;
    for (auto &component : toUpdate) {
        delete component;
    }
}

void Circuit::setObserver(CircuitObserver *o) {
    observer=o;
    for (auto &component : components) {
        observer->addNotify(component);
        observer->addNotify(component->getNodes().first);
        observer->addNotify(component->getNodes().second);
    }
}

void Circuit::add(Component *c, Node* p, Node* n) {

    for (auto &component : components)
        if (c==component)
        throw "Already added to circuit";

    bool found=false;
    for (auto &node : nodes)
        if (*p==*node) {
            delete p;
            p = node;
            found=true;
        }
    if (found==false){
        matrix.add();
        nodes.push_back(p);
        p->setObserver(this);
        observer->addNotify(p);
    }

    found= false;
    for (auto &node : nodes)
        if (*n==*node) {
            delete n;
            n = node;
            found=true;
        }
    if (found==false){
        matrix.add();
        nodes.push_back(n);
        n->setObserver(this);
        observer->addNotify(n);
    }

    components.push_back(c);
    c->setObserver(this);
    observer->addNotify(c);

    c->connect(p, n);
    matrix.add(c,getIndex(p,nodes),getIndex(n,nodes));

}

void Circuit::checkLink(Node &n) {
    //TODO: should throw duplicated exception?
            Node* existing=nullptr;

    //The heart of link method: finds the one that is "identical for Node standards" but not the same node
    for (auto &node : nodes) {
        if (*node==n && node!=&n)
            existing=node;
    }

    if (existing != nullptr) {
        std::list<Component *> componentsToUpdate = n.getComponents();
        for (auto &component : componentsToUpdate) {
            nodePair nodes= component->getNodes();
            Node* keep;
            keep = nodes.first == &n ? nodes.second :nodes.first;
            if(*keep == n )
                delete component;
            else {
                component->connect(existing, keep);
                matrix.update(getIndex(component,components),getIndex(existing,this->nodes),getIndex(keep,this->nodes));
            }
            }
        delete &n;
    }
}

template <class T> int Circuit::getIndex(T *x,std::list<T*> v){
    int i=0;
    for (auto &e : v){
        if (e==x)
            return i;
        i++;
    }
    return 0;
}

void Circuit::removeNotify(Component *c) {
    matrix.removeComponent(getIndex(c,components));
    components.remove(c);
}

void Circuit::removeNotify(Node *n) {
    matrix.removeNode(getIndex(n,nodes));
    nodes.remove(n);
}

void Circuit::moveNotify(Node &drag) {
    checkLink(drag);
}
