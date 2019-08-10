//
// Created by Sierra on 2019-07-29.
//

#ifndef FIRSTSIMULATORTEST_CCCS_H
#define FIRSTSIMULATORTEST_CCCS_H


#include "ActiveComponent.h"

class CCCS : public ActiveComponent{
public:
    CCCS(float value,Component *d= nullptr);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
    void setValue(float value) override{
        behavior[1]=1/value;
        this->value=value;
    }
    void setSource(Component* c){
        dependent=c;
    };
};



#endif //FIRSTSIMULATORTEST_CCCS_H