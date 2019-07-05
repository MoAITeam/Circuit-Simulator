//
// Created by Sierra on 2019-06-13.
//

#ifndef FIRSTSIMULATORTEST_COMPONENT_H
#define FIRSTSIMULATORTEST_COMPONENT_H

#include <QGraphicsItem>
#include <vector>
#include <memory>
#include "ComponentObserver.h"

class Node;
typedef std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> nodePair;

class Component: public QGraphicsItem {
public:
    Component(float v);
    ~Component();
    void connect(std::shared_ptr<Node> p, std::shared_ptr<Node> n);


    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void redraw();

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*) override;
    //just really deletes the pointer


    void setObserver(ComponentObserver *o);
    nodePair getNodes();

private:
    float value;
    float current;
    float voltage;
    ComponentObserver* observer;
    nodePair nodes;

};

#endif //FIRSTSIMULATORTEST_COMPONENT_H