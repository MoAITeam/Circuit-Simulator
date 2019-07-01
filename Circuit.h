//
// Created by Sierra on 2019-06-13.
//

#ifndef FIRSTSIMULATORTEST_CIRCUIT_H
#define FIRSTSIMULATORTEST_CIRCUIT_H

//TODO: components and nodes should be abstract not graphical entities [VERY HARD]!
#include "Component.h"
#include "Node.h"
#include <vector>
#include "Observer.h"
#include "IMatrix.h"

class Circuit{
public:
    Circuit(Observer* o=nullptr);
    ~Circuit();
    void setObserver(Observer* graphics);
    void add(Component *c, float x1, float y1, float x2, float y2); //aggiunge in tutti i modi, doppio puntatore per modificare quello passato
    void removeComponent(Component *c);
    void link(Node* &drag);
    void print();

private:
    template <class T> int find(T *e,std::vector<T*> v);
    std::vector<Component*> components;
    std::vector<Node*> nodes;
    Observer* observer;
    IMatrix I;
};


#endif //FIRSTSIMULATORTEST_CIRCUIT_H
