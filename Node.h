//
// Created by Sierra on 2019-06-13.
//

#ifndef FIRSTSIMULATORTEST_NODE_H
#define FIRSTSIMULATORTEST_NODE_H

#include <QGraphicsItem>
#include <QMouseEvent>
#include <vector>
#define NodeSize 10

class Component;

class Node: public QObject, public QGraphicsItem{
Q_OBJECT
public:
    Node(float x, float y);
    Node(QPointF point);
    bool operator==(Node& a);
    void connectComponent(Component* c);
    void disconnectComponent(Component* c);

    QRectF boundingRect() const override;
    void paint(QPainter* painter,const QStyleOptionGraphicsItem*,QWidget* ) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    std::vector<Component*> getComponents();

signals:
    void positionChanged(Node *);

private:
    float voltage;
    std::vector<Component*> components;
};


#endif //FIRSTSIMULATORTEST_NODE_H
