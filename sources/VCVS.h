//
// Created by Sierra on 2019-07-28.
//

#ifndef FIRSTSIMULATORTEST_VCVS_H
#define FIRSTSIMULATORTEST_VCVS_H

#include "Component.h"

class VCVS : public Component{
public:
    VCVS(float value,Component *d);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
    void setValue(float value) override{
        behavior[0]=1/value;
        observer->update(this);
    }
};


#endif //FIRSTSIMULATORTEST_VCVS_H