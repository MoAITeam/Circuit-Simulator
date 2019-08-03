//
// Created by Sierra on 2019-07-28.
//

#ifndef FIRSTSIMULATORTEST_VCVS_H
#define FIRSTSIMULATORTEST_VCVS_H

#include "ActiveComponent.h"

class VCVS : public ActiveComponent{
public:
    VCVS(float value,Component *d= nullptr);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
    void setValue(float value) override{
        behavior[0]=1/value;
    }
    void setSource(Component* c){
        dependent=c;
    };
};


#endif //FIRSTSIMULATORTEST_VCVS_H