//
// Created by cipher on 13/07/19.
//

#ifndef FIRSTSIMULATORTEST_CURRENTSOURCE_H
#define FIRSTSIMULATORTEST_CURRENTSOURCE_H


#include "ActiveComponent.h"

class CurrentSource : public ActiveComponent{

public:
    CurrentSource(float value);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override  final;
    void setValue(float value) override{
        behavior[2]=value;
        current=value;
        this->value=value;
    }
};


#endif //FIRSTSIMULATORTEST_CURRENTSOURCE_H