//
// Created by Sierra on 2019-06-13.
//

#ifndef FIRSTSIMULATORTEST_CIRCUIT_H
#define FIRSTSIMULATORTEST_CIRCUIT_H

//TODO: components and nodes should be abstract not graphical entities [VERY HARD]!
#include "Component.h"
#include "Node.h"
#include "IMatrix.h"
#include <vector>
#include "Observer.h"

class Circuit{
public:
    Circuit(Observer* o=nullptr);
    ~Circuit();
    void setObserver(Observer* graphics);
    void add(Component *c, Node *p, Node *n); //aggiunge in tutti i modi
    void deleteComponent(Component* c);
    void removeComponent(Component* c);
    void print();
    void link(Node* n);

private:
    template <class T> int find(T *e,std::vector<T*> v);
    template <class T> int getIndex(T *e,std::vector<T*> v);
    void connect(Component *c, Node *p, Node *n); //aggiunge solo se esistono già i nodi
    void AddNode(Node* n);
    void removeNode(Node* n);
    std::vector<Component*> components;
    std::vector<Node*> nodes;
    Observer* observer;
    IMatrix I;
};


#endif //FIRSTSIMULATORTEST_CIRCUIT_H
