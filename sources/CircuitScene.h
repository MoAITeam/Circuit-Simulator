
//
// Created by Sierra on 2019-06-23.
//

#ifndef FIRSTSIMULATORTEST_CIRCUITSCENE_H
#define FIRSTSIMULATORTEST_CIRCUITSCENE_H

#pragma once

#include <QGraphicsScene>
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include "Circuit.h"
#include "Node.h"
#include <iostream>
#include <QtWidgets/QInputDialog>
#include "Resistor.h"
#include "VoltageSource.h"
#include "CurrentSource.h"
#include "Wire.h"
#include "Voltmeter.h"
#include "Amperometer.h"
#include "VCVS.h"
#include "VCCS.h"
#include "CCVS.h"
#include "CCCS.h"

class CircuitScene: public QGraphicsScene, public CircuitObserver{
Q_OBJECT
public:
    CircuitScene(Circuit* c);
    void addNotify(QGraphicsItem *c) override;
    void createComponent();
    void createItemMenus();

    enum modes{insertItem,moveItem,selectDependent};

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void drawForeground(QPainter* painter, const QRectF &rect) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override ;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    void setType(Component::types type);
    void setMode(CircuitScene::modes mode);
    void resetExSel();
    void setcValue(float v);
    ActiveComponent* getExSelectedActiveComponent();

    //actions
    void changeValue();
    void deleteItem();
    void selectAll();

    Circuit* getCircuit();

signals:
    void insertValue();

private:
    static QColor gridColor;
    Component::types  myType;
    CircuitScene::modes myMode;
    Circuit* circuit;
    QPointF mousePressPoint;
    QPointF mouseReleasePoint;
    bool selecting=false;
    float cValue;
    QMenu* richItemMenu;
    QMenu* itemMenu;
    QMenu* sceneMenu;
    Component *selectedDependent;
    QGraphicsItem *exSel;
};


#endif //FIRSTSIMULATORTEST_CIRCUITSCENE_H