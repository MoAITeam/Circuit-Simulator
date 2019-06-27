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
    bool operator==(Component& c);
    void connect(Node* n1, Node* n2);
    void disconnect();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;

    std::vector<Node*> getNodes();


private:
    float value;
    float current;
    float voltage;
    std::vector<Node*> nodes{nullptr, nullptr};

};


#endif //FIRSTSIMULATORTEST_COMPONENT_H
