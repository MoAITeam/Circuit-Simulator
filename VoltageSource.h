//
// Created by cipher on 13/07/19.
//

#ifndef FIRSTSIMULATORTEST_VOLTAGESOURCE_H
#define FIRSTSIMULATORTEST_VOLTAGESOURCE_H


#include "Component.h"
#include <QPixmap>

class VoltageSource : public Component {

public:
    VoltageSource(float value):Component(1,0,value,new QPixmap(":/images/voltagesource.png")){
        voltage=value;
    };

    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
};


#endif //FIRSTSIMULATORTEST_VOLTAGESOURCE_H
