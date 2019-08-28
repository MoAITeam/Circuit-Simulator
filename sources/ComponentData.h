//
// Created by Sierra on 2019-08-28.
//

#ifndef FIRSTSIMULATORTEST_COMPONENTDATA_H
#define FIRSTSIMULATORTEST_COMPONENTDATA_H

#include "Component.h"

struct ComponentData{
    Component::types type;
    std::string label;
    float value;
    float pX;
    float pY;
    float nX;
    float nY;
    std::string dependent;
};

#endif //FIRSTSIMULATORTEST_COMPONENTDATA_H
