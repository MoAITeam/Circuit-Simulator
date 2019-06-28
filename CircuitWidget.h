//
// Created by Sierra on 2019-06-23.
//

#ifndef FIRSTSIMULATORTEST_CIRCUITWIDGET_H
#define FIRSTSIMULATORTEST_CIRCUITWIDGET_H

#pragma once
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMouseEvent>
#include "Circuit.h"

class CircuitWidget: public QGraphicsView, public Observer{
Q_OBJECT
public:
    CircuitWidget(Circuit* c);
    ~CircuitWidget();
    void addItem(Component* c) override;
    void addItem(Node* node) override;
    void removeItem(Component *c) override;
    void removeItem(Node *n) override;

    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    public slots:
    void linkNode(Node* n);

private:
    QGraphicsScene *scene;
    Circuit* circuit;
    QPointF mousePressPoint;
};


#endif //FIRSTSIMULATORTEST_CIRCUITWIDGET_H
