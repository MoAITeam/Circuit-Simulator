//
// Created by Sierra on 2019-06-13.
//

#ifndef FIRSTSIMULATORTEST_COMPONENT_H
#define FIRSTSIMULATORTEST_COMPONENT_H

#include <QGraphicsItem>
#include <vector>

class Node;

class Component: public QGraphicsItem {
public:
    Component(float v);
    ~Component();
    bool operator==(Component& c);
    void connect(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2);
    void disconnect();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void prepare(); //FIXME ugly name hiding

    std::shared_ptr<Node> getNode(int i);

private:
    float value;
    float current;
    float voltage;
    std::vector<std::shared_ptr<Node>> nodes{nullptr, nullptr};
    bool connected=false;

};


#endif //FIRSTSIMULATORTEST_COMPONENT_H
