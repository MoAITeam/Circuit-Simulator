//
// Created by Sierra on 2019-08-01.
//

#ifndef FIRSTSIMULATORTEST_ACTIVECOMPONENT_H
#define FIRSTSIMULATORTEST_ACTIVECOMPONENT_H

#include "Component.h"
#include "Node.h"
#include "QGraphicsScene"

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
        if(controller!= nullptr)
            drawLabels(painter,label+" ∝ "+controller->getLabel());
        else
            drawLabels(painter,label);
        Component::paint(painter,s,w);

        scene()->update();


    };

    void drawLabels(QPainter* painter, QString text){
        painter->save();
        painter->translate(QPointF((nodes.first->x()+nodes.second->x())/2, (nodes.first->y()+nodes.second->y())/2)-pos());
        QFont font=painter->font();
        font.setBold(true);
        painter->setFont(font);
        painter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawText(QPointF(-40,-50), text);
        font.setBold(false);
        painter->setFont(font);
        painter->drawText(QPointF(-40,-50)+QPointF(0,20),QString::number(value)+unit);
        painter->restore();
    };
protected:
    float value=0;
};


#endif //FIRSTSIMULATORTEST_ACTIVECOMPONENT_H
