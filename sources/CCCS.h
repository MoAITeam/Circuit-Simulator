//
// Created by Sierra on 2019-07-29.
//

#ifndef FIRSTSIMULATORTEST_CCCS_H
#define FIRSTSIMULATORTEST_CCCS_H


#include "Component.h"

class CCCS : public Component{
public:
    CCCS(float value,Component *d);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
};



#endif //FIRSTSIMULATORTEST_CCCS_H