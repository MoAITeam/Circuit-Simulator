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
    enum types {resistor, currentSource, voltageSource, wire, voltmeter ,amperometer, ground, vcvs, vccs, cccs, ccvs}; //keep controlled as last
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
    void drawLabels(QPainter *painter);
    void drawSolution(QPainter *painter);
    void setOrientation();
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    //void mouseClick(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;

    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

        //setters
    virtual void setCurrent(float value);
    void setVoltage(float value);
    void setNodesSelection(bool value);
    void setObserver(ComponentObserver *o);
    void setlabel(QString label){
        this->label=label;
    };

    void addDependent();
    void removeDependent();

    //getters
    QString getUnit(){
        return unit;
    }

    const QPixmap &getPixmap() const;

    QString getLabel(){
        return label;
    };

    float getCurrent();
    float getVoltage();
    virtual std::string getData();
    int getSourceType();
    nodePair getNodes();

    float behavior[3];
    Component *controller;
    types myType=wire;

protected:
    int sourceType=0;
    float current=0;
    float voltage=0;
    nodePair nodes;
    QPixmap pixmap;
    QString unit="Us";
    QString label="";
    ComponentObserver* circuit;
    int dependentSources=0;
private:
    bool hovering=false;
    QPointF mousePress;
    float angle;
    QColor solutionColor=QColor(220, 220, 220);
    QPen controllingPen=QPen(Qt::darkGreen, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen componentPen=QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen selectedPen=QPen(Qt::green, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    QPen solutionPen=QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPointF press;
    QPointF pressfirst;
    QPointF pressecond;
};
#endif //FIRSTSIMULATORTEST_COMPONENT_H