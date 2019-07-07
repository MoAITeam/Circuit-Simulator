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

//TODO observer for matrix

class Circuit: public ComponentObserver, public NodeObserver{
public:
    Circuit(CircuitObserver* o=nullptr);
    ~Circuit();

    void add(Component *c, float x1, float y1, float x2, float y2);
    void removeNotify(Component *c) override;
    void removeNotify(Node *n) override;
    void checkLink(Node &n);

    void setObserver(CircuitObserver* graphics);
    void moveNotify(Node &drag) override;

private:
    CircuitObserver* observer;
    std::list<Component*> components;
    std::list<Node*> nodes;
    SparseMatrix m;
};


#endif //FIRSTSIMULATORTEST_CIRCUIT_H
