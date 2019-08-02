//
// Created by Sierra on 2019-07-29.
//

#ifndef FIRSTSIMULATORTEST_CCCS_H
#define FIRSTSIMULATORTEST_CCCS_H


#include "ActiveComponent.h"

class CCCS : public ActiveComponent{
public:
    CCCS(float value,Component *d);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
    void setValue(float value) override{
        behavior[1]=1/value;
    }
};



#endif //FIRSTSIMULATORTEST_CCCS_H