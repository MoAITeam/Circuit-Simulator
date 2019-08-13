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
    //FIXME brutto (node in component)
    enum itemType {node = QGraphicsItem::UserType+1, component = QGraphicsItem::UserType+2, activeComponent = QGraphicsItem::UserType+3};

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
    void drawLabels(QPainter *painter);
    void drawSolution(QPainter *painter);
    void setOrientation();
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    //void mouseClick(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;

    //setters
    virtual void setCurrent(float value);
    void setVoltage(float value);

    void setObserver(ComponentObserver *o);

    void setControlled();
    void removeControlled();
    void setlabel(QString label){
        this->label=label;
    };

    //getters
    QString getUnit(){
        return unit;
    };
    QString getLabel(){
        return label;
    };
    float getCurrent();
    float getVoltage();
    int getSourceType();
    nodePair getNodes();

    float behavior[3];
    Component *dependent;

protected:
    int sourceType=0;
    float current=0;
    float voltage=0;
    nodePair nodes;
    QPixmap pixmap;
    QString unit="Us";
    QString label="";
    ComponentObserver* observer;
    QPointF rectLocation;

private:
    bool connected=false;
    bool hovering=false;
    int controlled=0;
    QPointF mousePress;
    float angle;

    QPointF press;
    QPointF pressfirst;
    QPointF pressecond;
};
#endif //FIRSTSIMULATORTEST_COMPONENT_H