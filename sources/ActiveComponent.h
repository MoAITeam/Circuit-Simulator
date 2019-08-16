//
// Created by Sierra on 2019-08-01.
//

#ifndef FIRSTSIMULATORTEST_ACTIVECOMPONENT_H
#define FIRSTSIMULATORTEST_ACTIVECOMPONENT_H

#include "Component.h"
#include "Node.h"

class ActiveComponent: public Component {
public:
    virtual void setValue(float value)=0;
    ActiveComponent(float a,float b, float c,Component* d=nullptr):Component(a,b,c,d){};
    int type() const override{
        return itemType::activeComponent;
    };
    float getValue(){
        return value;
    };
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *s, QWidget *w) override{
        painter->save();
        QString originalLabel=label;


        Component::paint(painter,s,w);

        painter->restore();
        if(dependent!= nullptr)
            drawLabels(painter,label+" ∝ "+dependent->getLabel());
        else
            drawLabels(painter,label);

    };

    void drawLabels(QPainter* painter, QString text){
        painter->translate(QPointF((nodes.first->x()+nodes.second->x())/2, (nodes.first->y()+nodes.second->y())/2)-pos());
        QFont font=painter->font();
        font.setBold(true);
        painter->setFont(font);
        painter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawText(QPointF(-40,-50), text);
        font.setBold(false);
        painter->setFont(font);
        painter->drawText(QPointF(-40,-50)+QPointF(0,20),QString::number(value)+unit);
    };
protected:
    float value=0;
};


#endif //FIRSTSIMULATORTEST_ACTIVECOMPONENT_H
