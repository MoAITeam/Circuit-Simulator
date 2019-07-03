//
// Created by Sierra on 2019-06-13.
//

#include "Circuit.h"
#define NOT_FOUND -1
//TODO: node should be abstract non inheriting from QGraphicsItem

Circuit::Circuit(CircuitObserver *o):observer(o) {

}

Circuit::~Circuit() {
    std::vector<Component*> toUpdate=components;
    for (auto &component : toUpdate) {
        delete component;
    }
}

void Circuit::setObserver(CircuitObserver *o) {
    observer=o;
    for (auto &component : components) {
        observer->addItem(component);
        observer->addItem(component->getNodes().first.get());
        observer->addItem(component->getNodes().second.get());
    }
}

void Circuit::add(Component *c, float x1, float y1, float x2, float y2) {

    int index=find(c);
    if (index!=NOT_FOUND)
        throw "Already added to circuit";

    std::shared_ptr<Node> ps(new Node(x1,y1));
    std::shared_ptr<Node> ns(new Node(x2,y2));

    components.push_back(c);

    c->setObserver(this);
    ps->setObserver(this);
    ns->setObserver(this);

    if (observer != nullptr){

        observer->addItem(ps.get());
        observer->addItem(ns.get());
        observer->addItem(c);

    }

    c->connect(ps, ns);
    link(*ps);
    link(*ns);
}

void Circuit::remove(Component *c) {
    int index= find(c);
    if(index!=NOT_FOUND)
        components.erase(components.begin() + index);
}

int Circuit::find(Component* c){
    //TODO: should throw duplicated exception?
    int index=NOT_FOUND;
    for (int i=0; i<components.size();i++)
        if(components[i]==c)
            index=i;
    return index;
}

void Circuit::link(Node& drag) {
    //TODO: should throw duplicated exception?
    std::shared_ptr<Node> existing;

    //The heart of link method: finds the one that is "identical for Node standards" but not the same node
    for (auto &component : components) {
        if (*(component->getNodes().first)==drag && component->getNodes().first.get()!=&drag)
            existing= component->getNodes().first;
        if (*(component->getNodes().second)==drag && component->getNodes().second.get()!=&drag)
            existing= component->getNodes().second;
    }

    if (existing != nullptr) {

        std::vector<Component *> componentsToUpdate = drag.getComponents();

        for (auto &component : componentsToUpdate) {
            std::shared_ptr<Node> keep;
            if (component->getNodes().first.get() == &drag)
                keep = component->getNodes().second;
            if (component->getNodes().second.get() == &drag)
                keep = component->getNodes().first;
            if (*keep == drag) {
                delete component;
            } else {
                component->connect(existing,keep);
            }
        }
    }
}