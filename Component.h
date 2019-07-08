//
// Created by Sierra on 2019-06-13.
//

#ifndef FIRSTSIMULATORTEST_COMPONENT_H
#define FIRSTSIMULATORTEST_COMPONENT_H

#include <vector>
#include <memory>
#include <QGraphicsItem>
#include "ComponentObserver.h"

class Node;
typedef std::pair<Node*,Node*> nodePair;

class Component: public  QGraphicsItem{
public:
    Component(float v);
    ~Component();
    void connect(Node* p, Node* n);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void redraw();

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*) override;


    void setObserver(ComponentObserver *o);
    nodePair getNodes();

    float behavior[3];

private:
    float current;
    float voltage;
    ComponentObserver* observer;
    nodePair nodes;

};

#endif //FIRSTSIMULATORTEST_COMPONENT_H