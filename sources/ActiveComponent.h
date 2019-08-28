//
// Created by Sierra on 2019-08-01.
//

#ifndef FIRSTSIMULATORTEST_ACTIVECOMPONENT_H
#define FIRSTSIMULATORTEST_ACTIVECOMPONENT_H

#include "Component.h"
#include "Node.h"
#include "QGraphicsScene"

//Component like controlled sources

class ActiveComponent: public Component {
public:
    virtual void setValue(float value)=0;
    ActiveComponent(float a,float b, float c,Component* d=nullptr):Component(a,b,c,d){};
    int type() const override;
    float getValue();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *s, QWidget *w) override;
    void drawLabels(QPainter* painter, QString text);
    std::string getData() override;

protected:
    float value=0;
};


#endif //FIRSTSIMULATORTEST_ACTIVECOMPONENT_H
