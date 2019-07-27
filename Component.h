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

    enum types {resistor, currentSource, voltageSource, wire, voltmeter ,amperometer, ground};

    Component(float a,float b, float c,types compType);
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
    bool hovering=false;
    QPointF mousePress;
    ComponentObserver* observer;

    QPointF press;
    QPointF pressfirst;
    QPointF pressecond;
};
#endif //FIRSTSIMULATORTEST_COMPONENT_H