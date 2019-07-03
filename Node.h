//
// Created by Sierra on 2019-06-13.
//

#ifndef FIRSTSIMULATORTEST_NODE_H
#define FIRSTSIMULATORTEST_NODE_H

#include <QGraphicsItem>
#include <QMouseEvent>
#include <vector>
#include "NodeObserver.h"
#define NodeSize 10

class Component;

class NodeObserver;

class Node: public QObject, public QGraphicsItem{
Q_OBJECT
public:
    Node(float x, float y);
    Node(QPointF point);
    ~Node();
    bool operator==(Node& a);
    void connectComponent(Component* c);
    void disconnectComponent(Component* c);
    void destroy();
    void setObserver(NodeObserver *o);

    QRectF boundingRect() const override;
    void paint(QPainter* painter,const QStyleOptionGraphicsItem*,QWidget* ) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* ) override;
    std::vector<Component*> getComponents();

private:
    float voltage;
    std::vector<Component*> components;
    NodeObserver* observer;
};


#endif //FIRSTSIMULATORTEST_NODE_H
