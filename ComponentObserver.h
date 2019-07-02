//
// Created by Sierra on 2019-07-02.
//

#ifndef FIRSTSIMULATORTEST_COMPONENTOBSERVER_H
#define FIRSTSIMULATORTEST_COMPONENTOBSERVER_H

#include "Component.h"

class ComponentObserver{
public:
    virtual void removeComponent(Component* )=0;
};

#endif //FIRSTSIMULATORTEST_COMPONENTOBSERVER_H
