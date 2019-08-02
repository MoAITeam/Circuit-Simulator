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
    enum sourceTypes {none, volts, ampere};
    enum types {resistor, currentSource, voltageSource, wire, voltmeter ,amperometer, ground, vcvs, vccs, cccs, ccvs};
    enum itemType {component = QGraphicsItem::UserType+1, activeComponent = QGraphicsItem::UserType+2};

    Component(float a,float b, float c,Component* d=nullptr);
    virtual ~Component() override;

    void connect(Node* p, Node* n);
    void disconnect();

    //QGraphicsItem
    int type() const override {return component;};
    QRectF boundingRect() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    QPainterPath shape() const override;
    void drawComponent(QPainter *painter);
    void drawSolution(QPainter *painter);
    void setOrientation();
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;

    //setters
    virtual void setCurrent(float value);
    void setVoltage(float value);

    void setObserver(ComponentObserver *o);
    void setMenu(QMenu* m);

    void setControlled();
    void removeControlled();

    //getters
    float getCurrent();
    float getVoltage();
    int getSourceType();
    nodePair getNodes();

    float behavior[3];
    Component *dependent;
    QMenu* contextMenu;

protected:
    int sourceType=0;
    float current;
    float voltage;
    nodePair nodes;
    QPixmap pixmap;
    ComponentObserver* observer;

private:
    bool hovering=false;
    int controlled=0;
    QPointF mousePress;
    QPointF rectLocation;
    float angle;

    QPointF press;
    QPointF pressfirst;
    QPointF pressecond;
};
#endif //FIRSTSIMULATORTEST_COMPONENT_H