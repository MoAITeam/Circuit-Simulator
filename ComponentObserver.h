//
// Created by Sierra on 2019-07-02.
//

#ifndef FIRSTSIMULATORTEST_COMPONENTOBSERVER_H
#define FIRSTSIMULATORTEST_COMPONENTOBSERVER_H

class Component;

class ComponentObserver{
public:
    virtual void add(Component* item, float x1, float y1, float x2, float y2) = 0;
    virtual void remove(Component* )=0;
};

#endif //FIRSTSIMULATORTEST_COMPONENTOBSERVER_H
