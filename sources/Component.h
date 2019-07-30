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

class Component: public  QGraphicsItem{
public:

    enum types {resistor, currentSource, voltageSource, wire, voltmeter ,amperometer, ground, vcvs, vccs, cccs, ccvs};

    Component(float a,float b, float c, types compType, Component* d=nullptr);
    ~Component();

    void connect(Node* p, Node* n);

    QRectF boundingRect() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void setImage(types compType);
    void redraw();
    QPainterPath shape() const override;

    void setObserver(ComponentObserver *o);
    nodePair getNodes();

    virtual void setCurrent(float value);
    void setVoltage(float value);
    void setControlled();
    void removeControlled();

    float getCurrent();
    float getVoltage();

    float behavior[3];
    Component *dependent;
    int s=0;
protected:
    float current;
    float voltage;
    nodePair nodes;
    QPixmap pixmap;

private:
    bool hovering=false;
    int controlled=0;
    QPointF mousePress;
    ComponentObserver* observer;

    QPointF press;
    QPointF pressfirst;
    QPointF pressecond;
};
#endif //FIRSTSIMULATORTEST_COMPONENT_H