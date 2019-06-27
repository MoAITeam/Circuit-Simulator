//
// Created by Sierra on 2019-06-24.
//

#ifndef FIRSTSIMULATORTEST_OBSERVER_H
#define FIRSTSIMULATORTEST_OBSERVER_H

#include "Node.h"
#include "Component.h"

class Observer{
public:
    //FIXME due versioni per due signal diversi...
    virtual void addItem(Node* item) = 0;
    virtual void addItem(Component* item) = 0;
    virtual void removeItem(QGraphicsItem* item) = 0;
    virtual ~Observer() {};
};

#endif //FIRSTSIMULATORTEST_OBSERVER_H
