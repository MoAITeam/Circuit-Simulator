//
// Created by Sierra on 2019-06-13.
//

#ifndef FIRSTSIMULATORTEST_CIRCUIT_H
#define FIRSTSIMULATORTEST_CIRCUIT_H

//TODO: components and nodes should be abstract not graphical entities [VERY HARD]!
#include "Component.h"
#include "Node.h"
#include <vector>
#include "CircuitObserver.h"

class Circuit: public ComponentObserver, public NodeObserver{
public:
    Circuit(CircuitObserver* o=nullptr);
    ~Circuit();

    void add(Component *c, float x1, float y1, float x2, float y2) override;
    void remove(Component *c) override;

    void setObserver(CircuitObserver* graphics);
    void link(Node& drag) override;

private:
    int find(Component* c);
    CircuitObserver* observer;
    std::vector<Component*> components;

};


#endif //FIRSTSIMULATORTEST_CIRCUIT_H
