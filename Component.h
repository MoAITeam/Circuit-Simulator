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

class Component: public QGraphicsItem {
public:
    Component(float v);
    ~Component();
    void setObserver(ComponentObserver *o);
    void connect(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2);
    void disconnect();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void redraw();

    std::pair<std::shared_ptr<Node>,std::shared_ptr<Node>> getNodes();

private:
    float value;
    float current;
    float voltage;
    ComponentObserver* observer;
    std::pair<std::shared_ptr<Node>,std::shared_ptr<Node>> nodes{nullptr, nullptr};
    //std::vector<std::shared_ptr<Node>> nodes{nullptr, nullptr}; //FIXME pair

    bool connected=false;

};

#endif //FIRSTSIMULATORTEST_COMPONENT_H