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
    ~Node();
    void connectComponent(Component* c);
    void disconnectComponent(Component* c);


    QRectF boundingRect() const override;
    void paint(QPainter* painter,const QStyleOptionGraphicsItem*,QWidget* ) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    //Just updates the drawing like the real application I'm building

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    //notifies observer of the changed position

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* ) override;
    //It really just deletes all the components attached to it


    void setObserver(NodeObserver *o);
    std::list<Component*> getComponents();

    bool operator==(Node& a);

private:
    float voltage;
    std::list<Component*> components;
    NodeObserver* observer;
};


#endif //FIRSTSIMULATORTEST_NODE_H
