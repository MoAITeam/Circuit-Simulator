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
        if(observer!= nullptr) {
            observer->removeItem(component->getNode(1).get());
            observer->removeItem(component->getNode(0).get());
        }
        removeComponent(component);
    }
}

void Circuit::setObserver(Observer *o) {
    observer=o;
}

void Circuit::add(Component *c, float x1, float y1, float x2, float y2) {

    //Check if the nodes I'm trying to add already exist
    //If so, replace original pointers with the existing ones

    auto *p =new Node(x1,y1);
    auto *n=new Node(x2,y2);

    std::shared_ptr<Node> ps(p);
    std::shared_ptr<Node> ns(n);

    observer->addItem(ps.get());
    observer->addItem(ns.get());

    if (observer != nullptr)
        observer->addItem(c); //FIXME two overloaded addItems should be one...

    c->connect(ps, ns);

    components.push_back(c);

    link(p);
    link(n);
}

void Circuit::removeComponent(Component *c) {
    //TODO: not found exception
    //TODO: handle empty nodes
    int index= find(c,components);
    if(index!=components.size()) {
        components.erase(components.begin() + index);

        if(observer!=nullptr)
            observer->removeItem(c); //FIXME two overloaded addItems should be one...

        c->disconnect();
        delete c;
    }
}

template <class T> int Circuit::find(T *e,std::vector<T*> v){
    //TODO: should throw duplicated exception?
    int index=v.size();
    for (int i=0; i<v.size();i++)
        if(*v[i]==*e)
            index=i;
    return index;
}

void Circuit::link(Node* &drag) {
    //TODO: should throw duplicated exception?
    std::shared_ptr<Node> existing;

    //The heart of link method: finds the one that is "identical for Node standards" but not the same node
    //Alternativa: costruire un'area attorno al nodo che si attiva versione hover, e controlla se sto pigiando...seee
    for (auto &component : components) {
        if (*(component->getNode(0))==*drag && component->getNode(0).get()!=drag)
            existing= component->getNode(0);
        if (*(component->getNode(1))==*drag && component->getNode(1).get()!=drag)
            existing= component->getNode(1);
    }

    if (existing != nullptr) {

        std::vector<Component *> componentsToUpdate = drag->getComponents();

        for (auto &component : componentsToUpdate) {
            std::shared_ptr<Node> keep;
            keep = component->getNode((component->getNode(0).get() == drag ? 1 : 0));
            if (*keep == *drag) {
                removeComponent(component);
            } else {
                component->connect(existing,keep);
            }
        }
        drag=existing.get();
    }
}