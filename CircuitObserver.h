//
// Created by Sierra on 2019-06-24.
//

#ifndef FIRSTSIMULATORTEST_CIRCUITOBSERVER_H
#define FIRSTSIMULATORTEST_CIRCUITOBSERVER_H

#include "Node.h"
#include "Component.h"

class CircuitObserver{
public:
    virtual void addNotify(QGraphicsItem *item, QGraphicsItem* item1,QGraphicsItem* item2) = 0;
    virtual ~CircuitObserver() {};
};

#endif //FIRSTSIMULATORTEST_CIRCUITOBSERVER_H
