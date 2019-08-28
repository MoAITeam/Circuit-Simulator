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

    int type() const override {return component;};
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;

    //setters
    virtual void setCurrent(float value);
    void setVoltage(float value);
    void setNodesSelection(bool value);
    void setObserver(ComponentObserver *o);
    void setlabel(QString label);
    void setController(Component*);

    void addDependent();
    void removeDependent();

    //getters
    QString getUnit();
    const QPixmap &getPixmap() const;
    QString getLabel();
    float getCurrent();
    float getVoltage();
    virtual std::string getData();
    int getSourceType();
    nodePair getNodes();
    float* getBehavior();
    types getType();
    Component* getController();

protected:
    Component *controller;
    types componentType=wire;
    float behavior[3];
    int sourceType=0;
    float current=0;
    float voltage=0;
    nodePair nodes;
    QPixmap pixmap;
    QString unit="Us";
    QString label="";
private:

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void drawComponent(QPainter *painter);
    void drawSolution(QPainter *painter);
    void setOrientation();
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;

    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

    ComponentObserver* circuit;
    int dependentSources=0;
    bool hovering=false;
    float angle;
    QColor solutionColor=QColor(220, 220, 220);
    QPen controllingPen=QPen(Qt::darkGreen, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen componentPen=QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen selectedPen=QPen(Qt::green, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    QPen solutionPen=QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
};
#endif //FIRSTSIMULATORTEST_COMPONENT_H