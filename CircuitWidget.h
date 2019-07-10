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

class CircuitWidget: public QGraphicsView, public CircuitObserver{
Q_OBJECT
public:
    CircuitWidget(Circuit* c);
    void addNotify(QGraphicsItem *c) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent *event);

private:
    Circuit* circuit;
    QPointF mousePressPoint;
};


#endif //FIRSTSIMULATORTEST_CIRCUITWIDGET_H
