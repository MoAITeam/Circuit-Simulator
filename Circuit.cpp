//
// Created by Sierra on 2019-06-13.
//

#include "Circuit.h"
//TODO: node should be abstract non inheriting from QGraphicsItem

Circuit::Circuit(Observer *o):observer(o) {

}

Circuit::~Circuit() {
    std::vector<Component*> toUpdate=components;
    for (auto &component : toUpdate) {
        delete component;
    }
}

void Circuit::setObserver(Observer *o) {
    observer=o;
}

void Circuit::add(Component *c, float x1, float y1, float x2, float y2) {

    //Check if the nodes I'm trying to add already exist
    //If so, replace original pointers with the existing ones

    int index=find(c);
    if (index!=components.size())
        throw "Already added to circuit";

    std::shared_ptr<Node> ps(new Node(x1,y1));
    std::shared_ptr<Node> ns(new Node(x2,y2));

    observer->addItem(ps.get());
    observer->addItem(ns.get());

    c->setObserver(this);

    if (observer != nullptr)
        observer->addItem(c); //FIXME two overloaded addItems should be one...

    c->connect(ps, ns);

    components.push_back(c);

    link(*ps);
    link(*ns);
}

int Circuit::find(Component* c){
    //TODO: should throw duplicated exception?
    int index=components.size();
    for (int i=0; i<components.size();i++)
        if(components[i]==c)
            index=i;
    return index;
}

void Circuit::link(Node& drag) {
    //TODO: should throw duplicated exception?
    std::shared_ptr<Node> existing;

    //The heart of link method: finds the one that is "identical for Node standards" but not the same node
    //Alternativa: costruire un'area attorno al nodo che si attiva versione hover, e controlla se sto pigiando...seee
    for (auto &component : components) {
        if (*(component->getNode(0))==drag && component->getNode(0).get()!=&drag)
            existing= component->getNode(0);
        if (*(component->getNode(1))==drag && component->getNode(1).get()!=&drag)
            existing= component->getNode(1);
    }

    if (existing != nullptr) {

        std::vector<Component *> componentsToUpdate = drag.getComponents();

        for (auto &component : componentsToUpdate) {
            std::shared_ptr<Node> keep;
            keep = component->getNode((component->getNode(0).get() == &drag ? 1 : 0));
            if (*keep == drag) {
                delete component;
            } else {
                component->connect(existing,keep);
            }
        }
    }
}

void Circuit::removeComponent(Component *c) {
    int index= find(c);
    if(index!=components.size())
        components.erase(components.begin() + index);
}