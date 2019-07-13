//
// Created by Sierra on 2019-06-13.
//

#ifndef FIRSTSIMULATORTEST_CIRCUIT_H
#define FIRSTSIMULATORTEST_CIRCUIT_H

#include "Component.h"
#include "Node.h"
#include <vector>
#include "CircuitObserver.h"
#include "SparseMatrix.h"


class Circuit: public ComponentObserver, public NodeObserver{
public:
    Circuit(CircuitObserver* o=nullptr);
    ~Circuit();

    void add(Component *c, Node* p, Node* n);
    void removeNotify(Component *c) override;
    void removeNotify(Node *n) override;
    void checkLink(Node &n);
    template <typename T> int getIndex(T*x,std::list<T*> v);

    void setObserver(CircuitObserver* graphics);
    void moveNotify(Node &drag) override;
    std::list<Node*> nonGround();
    void print();
    void solve();

private:
    CircuitObserver* observer;
    std::list<Component*> components;
    std::list<Node*> nodes;
    SparseMatrix* matrix; //Muore insieme, non puntatore
};


#endif //FIRSTSIMULATORTEST_CIRCUIT_H
