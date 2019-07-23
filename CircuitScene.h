//
// Created by Sierra on 2019-06-23.
//

#ifndef FIRSTSIMULATORTEST_CIRCUITSCENE_H
#define FIRSTSIMULATORTEST_CIRCUITSCENE_H

#pragma once
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include "Circuit.h"

class CircuitScene: public QGraphicsScene, public CircuitObserver{
Q_OBJECT
public:
    CircuitScene(Circuit* c);
    void addNotify(QGraphicsItem *c) override;

    enum modes{insertItem,MoveItem};

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override ;

    void setType(Component::types type);
    void setMode(CircuitScene::modes mode);

private:
    static QColor gridColor;
    Component::types  myType;
    CircuitScene::modes myMode;
    Circuit* circuit;
    QPointF mousePressPoint;
};


#endif //FIRSTSIMULATORTEST_CIRCUITSCENE_H
