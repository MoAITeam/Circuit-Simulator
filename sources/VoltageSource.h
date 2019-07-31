//
// Created by cipher on 13/07/19.
//

#ifndef FIRSTSIMULATORTEST_VOLTAGESOURCE_H
#define FIRSTSIMULATORTEST_VOLTAGESOURCE_H


#include "Component.h"
#include <QPixmap>

class VoltageSource : public Component {

public:
    VoltageSource(float value);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
    void setValue(float value) override{
        behavior[2]=value;
        voltage=value;
        observer->update(this);
    };
};

#endif //FIRSTSIMULATORTEST_VOLTAGESOURCE_H
