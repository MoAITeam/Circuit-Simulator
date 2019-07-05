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
        observer->addNotify(component,component->getNodes().first.get(),component->getNodes().second.get());
       // observer->addNotify(component->getNodes().first.get());
       // observer->addNotify(component->getNodes().second.get());
    }
}

void Circuit::add(Component *c, float x1, float y1, float x2, float y2) {

    for (auto &component : components)
        if (c==component)
        throw "Already added to circuit";

    std::shared_ptr<Node> ps(new Node(x1,y1));
    std::shared_ptr<Node> ns(new Node(x2,y2));

    components.push_back(c);

    c->setObserver(this);
    ps->setObserver(this);
    ns->setObserver(this);

    if (observer != nullptr){

        observer->addNotify(c,ps.get(),ns.get());
       // observer->addNotify(ns.get());
       // observer->addNotify(c);

    }

    c->connect(ps, ns);
    notify(*ps);
    notify(*ns);
}

void Circuit::removeNotify(Component *c) {
    components.remove(c);
}

void Circuit::notify(Node &drag) {
    //TODO: should throw duplicated exception?
    std::shared_ptr<Node> existing;
    nodePair nodes;

    //The heart of link method: finds the one that is "identical for Node standards" but not the same node
    for (auto &component : components) {
        nodes=component->getNodes();
        if (*(nodes.first)==drag && nodes.first.get()!=&drag)
            existing= nodes.first;
        if (*(nodes.second)==drag && nodes.second.get()!=&drag)
            existing= nodes.second;
    }

    if (existing != nullptr) {

        std::list<Component *> componentsToUpdate = drag.getComponents();
        for (auto &component : componentsToUpdate) {
            nodes=component->getNodes();
            std::shared_ptr<Node> keep;
            keep = nodes.first.get() == &drag ? nodes.second :nodes.first;
            *keep == drag ? delete component : component->connect(existing,keep);
        }
    }
}