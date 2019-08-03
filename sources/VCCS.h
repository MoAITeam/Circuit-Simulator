//
// Created by Sierra on 2019-07-29.
//

#ifndef FIRSTSIMULATORTEST_VCCS_H
#define FIRSTSIMULATORTEST_VCCS_H

#include "ActiveComponent.h"

class VCCS : public ActiveComponent{
public:
    VCCS(float value,Component *d= nullptr);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
    void setValue(float value) override{
        behavior[1]=1/value;
    }
    void setSource(Component* c){
        dependent=c;
    };
};



#endif //FIRSTSIMULATORTEST_VCCS_H