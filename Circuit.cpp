//
// Created by Sierra on 2019-06-13.
//

#include "Circuit.h"
#include <iostream>
//TODO: Node should be abstract, concrete GraphicalNode

Circuit::Circuit(Observer *o):observer(o) {

}

Circuit::~Circuit() {
    //TODO: KILL ALL OF THEM :D
}

void Circuit::setObserver(Observer *o) {
    observer=o;
}

void Circuit::AddNode(Node *n) {

    if(observer!=nullptr)
        observer->addItem(n); //FIXME two overloaded addItems should be one...

    nodes.push_back(n);
    I.addRow();
}

//FIXME should I be allowed to create Nodes outside of the Circuit class?
void Circuit::add(Component *c, Node*& p, Node*& n) {
    //FIXME Are the original nodes from the calling function updated?

    //Check if the nodes I'm trying to add already exist
    //If so, replace original pointers with the existing ones
    int indexP=find(p,nodes);
    if (indexP==nodes.size()){
        AddNode(p);
    }
    else{
        delete p;
        p=nodes[indexP];
    }

    int indexN=find(n,nodes);
    if (indexN==nodes.size()){
        AddNode(n);
    }else{
        delete n;
        n=nodes[indexN];
    }

    //FIXME: very expensive, it searches twice... but it's clear
    connect(c,p,n);

    /*if(observer!=nullptr)
        observer->addItem(c);

    c->connect(p,n);

    I.addCol();
    I(indexP, I.end())=1;
    I(indexN, I.end())=-1;

    components.push_back(c);*/
}

void Circuit::connect(Component *c, Node *p, Node *n) {
    //TODO: not found exception

    int indexP=getIndex(p,nodes);
    int indexN=getIndex(n,nodes);

    if (indexP!=nodes.size()&&indexN!=nodes.size()) {

        if (observer != nullptr)
            observer->addItem(c); //FIXME two overloaded addItems should be one...

        c->connect(p, n);

        I.addCol();
        I(indexP, I.end()) = 1;
        I(indexN, I.end()) = -1;

        components.push_back(c);
    }
}

void Circuit::removeNode(Node *n) {
    //TODO: not found exception

    int index=getIndex(n,nodes);

    if(index!=nodes.size()) {
        nodes.erase(nodes.begin() + index);
        for (auto &component : n->getComponents())
            removeComponent(component);
        I.removeRow(index);

        if(observer!=nullptr)
            observer->removeItem(n); //FIXME two overloaded addItems should be one...

        delete n;
    }
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
        I.removeColumn(index);
    }
}

void Circuit::deleteComponent(Component *c) {
    removeComponent(c);
    delete c;
}

template <class T> int Circuit::find(T *e,std::vector<T*> v){
    //TODO: should throw duplicated exception?
    int index=v.size(); int f=0;
    for (int i=0; i<v.size();i++)
    {
        if(*v[i]==*e){
            index=i;
            f++;
        }
    }
    if (f>1)
        std::cout<<f<<"duplicated nodes"<<std::endl;
    return index;
}

template <class T> int Circuit::getIndex(T *e,std::vector<T*> v){
    int index=v.size();
    for(int i=0;i<v.size();i++)
        if(v[i]==e)
            index=i;
    return index;
}

void Circuit::link(Node *n) {
    //TODO: should throw duplicated exception?
    //FIXME: should Node call this method directly, instead of asking the View?
    Node *newNode = nullptr;

    //The heart of link method: finds the one that is "identical for Node standards" but not the same node
    for(int j=0;j<nodes.size();j++)
        if( *(nodes[j]) == *n && nodes[j]!=n )
            newNode=nodes[j];

    if (newNode != nullptr) {
        std::vector<Component *> componentsToUpdate = n->getComponents();

        for (auto &component : componentsToUpdate) {
            Node *other;
            other = component->getNodes()[(component->getNodes()[0] == n ? 1 : 0)];
            if (*other == *n) {
                //If I'm linking it to itself
                deleteComponent(component);
            } else {
                removeComponent(component);
                connect(component, newNode, other);
            }
        }
        //TODO: with shared pointers?
        removeNode(n);
    }
}

void Circuit::print(){
    std::cout<<"components->          ";
    for (int i=0; i<components.size(); i++)
        std::cout<<components[i]<<"        ";
    std::cout<<std::endl;
    for (int j=0; j< I.bottom()+1; j++) {
        std::cout<<nodes[j]<<"("<<nodes[j]->x()<<","<<nodes[j]->y()<<")"<<"   ";
        for (int i = 0; i < I.end()+1; i++)
            std::cout << I(j,i) << "                     ";
        std::cout << std::endl;
    }
}