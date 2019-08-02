//
// Created by Sierra on 2019-08-01.
//

#ifndef FIRSTSIMULATORTEST_ACTIVECOMPONENT_H
#define FIRSTSIMULATORTEST_ACTIVECOMPONENT_H

#include "Component.h"

class ActiveComponent: public Component {
public:
    virtual void setValue(float value)=0;
    ActiveComponent(float a,float b, float c,Component* d=nullptr):Component(a,b,c,d){};
    int type() const override{
        return itemType::activeComponent;
    };
};


#endif //FIRSTSIMULATORTEST_ACTIVECOMPONENT_H
