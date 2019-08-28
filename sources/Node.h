//
// Created by Sierra on 2019-06-13.
//

#ifndef FIRSTSIMULATORTEST_NODE_H
#define FIRSTSIMULATORTEST_NODE_H

#include <QMouseEvent>
#include <vector>
#include <QGraphicsItem>
#include "NodeObserver.h"
#include "ResourceManager.h"
#define NodeSize 4
#define nodeGridSize 20

class Component;

class NodeObserver;

class Node: public QGraphicsItem{
public:
    Node(float x, float y,bool isGround=false);
    Node(QPointF point,bool isGround=false):Node(point.x(),point.y(),isGround){};
    ~Node();
    void connect(Component *c);
    void disconnect(Component *c);

    void setObserver(NodeObserver *o);
    void setVoltage(float value);
    float getVoltage();

    void checkLink();

    std::list<Component*> getComponents();
    bool isGround();

    bool operator==(Node& a);
    static QPointF toGrid(QPointF n);

private:

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* ) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* ) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* ) override;
    void paint(QPainter* painter,const QStyleOptionGraphicsItem*,QWidget* ) override;
    void paintSolution(QPainter* painter);
    QRectF boundingRect() const override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    float voltage;
    std::list<Component*> components;
    NodeObserver* observer;
    bool gnd;
    bool hovering=false;
    QPen selectedPen=QPen(Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen renderPen=QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen solutionPen=QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QColor solutionColor=QColor(220, 220, 220);
};


#endif //FIRSTSIMULATORTEST_NODE_H
