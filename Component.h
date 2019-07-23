//
// Created by Sierra on 2019-06-13.
//

#ifndef FIRSTSIMULATORTEST_COMPONENT_H
#define FIRSTSIMULATORTEST_COMPONENT_H

#include <vector>
#include <memory>
#include <QGraphicsItem>
#include "ComponentObserver.h"
#include <QPainter>

class Node;
typedef std::pair<Node*,Node*> nodePair;

//FIXME resource manager?
class Component: public  QGraphicsItem{
public:

    Component(float a,float b, float c);
    ~Component();

    enum types {Resistor, CurrentSource, VoltageSource, Wire};

    void connect(Node* p, Node* n);

    QRectF boundingRect() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void redraw();
    QPainterPath shape() const override;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* ) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* ) override;

        void setObserver(ComponentObserver *o);
    nodePair getNodes();

    void setCurrent(float value);
    void setVoltage(float value);

    float getCurrent();
    float getVoltage();

    float behavior[3];
protected:
    float current;
    float voltage;
    nodePair nodes;
    QPixmap pixmap;

private:
    QPointF mousePress;
    ComponentObserver* observer;
};
#endif //FIRSTSIMULATORTEST_COMPONENT_H