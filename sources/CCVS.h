//
// Created by Sierra on 2019-07-29.
//

#ifndef FIRSTSIMULATORTEST_CCVS_H
#define FIRSTSIMULATORTEST_CCVS_H


#include "ActiveComponent.h"

class CCVS : public ActiveComponent{
public:
    CCVS(float value,Component *d= nullptr);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
    void setValue(float value) override{
        behavior[0]=1/value;
        this->value=value;
    }
    void setSource(Component* c){
        controller=c;
    };
};



#endif //FIRSTSIMULATORTEST_CCVS_H