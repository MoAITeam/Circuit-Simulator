//
// Created by Sierra on 2019-07-29.
//

#ifndef FIRSTSIMULATORTEST_CCVS_H
#define FIRSTSIMULATORTEST_CCVS_H


#include "Component.h"

class CCVS : public Component{
public:
    CCVS(float value,Component *d);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
};



#endif //FIRSTSIMULATORTEST_CCVS_H