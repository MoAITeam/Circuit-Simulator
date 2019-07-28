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
};


#endif //FIRSTSIMULATORTEST_VCVS_H
