//
// Created by cipher on 13/07/19.
//

#ifndef FIRSTSIMULATORTEST_CURRENTSOURCE_H
#define FIRSTSIMULATORTEST_CURRENTSOURCE_H


#include "Component.h"

class CurrentSource : public Component{

public:
    CurrentSource(float value):Component(0,1,value,new QPixmap(":/images/currentsource.png")){
        current=value;
    };

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override  final;

};


#endif //FIRSTSIMULATORTEST_CURRENTSOURCE_H
