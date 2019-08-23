//
// Created by Sierra on 2019-06-13.
//

#ifndef FIRSTSIMULATORTEST_CIRCUIT_H
#define FIRSTSIMULATORTEST_CIRCUIT_H

#include "ActiveComponent.h"
#include "Node.h"
#include <vector>
#include "CircuitObserver.h"
#include "SparseMatrix.h"


class Circuit: public ComponentObserver, public NodeObserver{
public:
    Circuit(CircuitObserver* o=nullptr);
    ~Circuit();
    void clear();

    void add(Component *c, Node*& p, Node*& n);
    void removeNotify(Component *c) override;
    void removeNotify(Node *n) override;
    void checkLink(Node *n);
    void update(ActiveComponent* component,float value);
    template <typename T> int getIndex(T*x,std::vector<T*> v);

    void setObserver(CircuitObserver* graphics);
    void update(Node *drag) override;
    std::vector<Node*> nonGround();
    void print();
    void solve();

private:
    CircuitObserver* observer;
    std::vector<Component*> components;
    std::vector<Node*> nodes;
    SparseMatrix matrix;
};


#endif //FIRSTSIMULATORTEST_CIRCUIT_H
