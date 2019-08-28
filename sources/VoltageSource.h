//
// Created by cipher on 13/07/19.
//

#ifndef FIRSTSIMULATORTEST_VOLTAGESOURCE_H
#define FIRSTSIMULATORTEST_VOLTAGESOURCE_H


#include "ActiveComponent.h"
#include <QPixmap>

class VoltageSource : public ActiveComponent {

public:
    VoltageSource(float value);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
    void setValue(float value) override;
};

#endif //FIRSTSIMULATORTEST_VOLTAGESOURCE_H
