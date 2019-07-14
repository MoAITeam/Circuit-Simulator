//
// Created by Sierra on 2019-07-01.
//

#ifndef FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_CPP
#define FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_CPP

#include <QtTest/QtTest>
#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include "TestCircuitWidget.cpp"
#include "CircuitWidget.h"
#include "Component.h"
#include "Resistor.h"
#include "VoltageSource.h"

class TestCircuitWidget: public QObject {
Q_OBJECT
private slots:

    void testAddItem() {
        Circuit *circuit = new Circuit;
        CircuitWidget *widget = new CircuitWidget(circuit);
        auto c = new Resistor(5);
        auto p = new Node(50, 50);
        auto n = new Node(100, 100);
        circuit->add(c, p, n);
        QVERIFY(c->getNodes().first->x() == 50 && c->getNodes().first->y() == 50 && c->getNodes().second->x() == 100 &&
                c->getNodes().second->y() == 100);
        bool found = false;
        for (auto item : widget->scene()->items()) {
            if (item == c) {
                if (found == false)
                    found = true;
                else
                    found = false; //duplicated
            }
        }
        QVERIFY(found);
    };

    void removeRandomComponent() {
        QMainWindow *mainWindow = new QMainWindow();
        auto circuit = new Circuit;
        auto widget = new CircuitWidget(circuit);
        auto c = new Resistor(10);
        auto p = new Node(50, 50);
        auto n = new Node(100, 100);
        circuit->add(c, p, n);
        mainWindow->setCentralWidget(widget);
        QTest::mouseDClick(widget->viewport(), Qt::LeftButton, Qt::NoModifier, widget->mapFromScene(100, 100));
        QTest::mouseClick(widget->viewport(), Qt::LeftButton, Qt::NoModifier, widget->mapFromScene(0, 0));
        QTest::mouseDClick(widget->viewport(), Qt::LeftButton, Qt::NoModifier, widget->mapFromScene(48, 48));
        bool status = false;
        if (widget->scene()->items().size() == 0) //items has always one void
            status = true;
        QVERIFY(status == true);
    };


    void testSampleCircuit() {

        QMainWindow *mainWindow = new QMainWindow();
        auto circuit = new Circuit;
        auto widget = new CircuitWidget(circuit);

        auto *vol = new VoltageSource(30);
        auto *vol_p = new Node(50, 50);
        auto *vol_n = new Node(50, 100);
        circuit->add(vol, vol_p, vol_n);

        auto *res1 = new Resistor(10);
        auto *res1_p = new Node(50, 100);
        auto *res1_n = new Node(100, 100);
        circuit->add(res1, res1_p, res1_n);

        auto *res2 = new Resistor(10);
        auto *res2_p = new Node(100, 100);
        auto *res2_n = new Node(100, 50, 1); //se lo dichiari dopo di terra non fa
        circuit->add(res2, res2_p, res2_n);

        auto *res3 = new Resistor(10);
        auto *res3_p = new Node(100, 50);
        auto *res3_n = new Node(50, 50);
        circuit->add(res3, res3_p, res3_n);

        //mainWindow->setCentralWidget(widget);
        //QTest::keyPress(widget , Qt::Key::Key_S);
        circuit->print();
        circuit->solve();
        float t1 = res1_p->getVoltage();
        float t2 = res1_n->getVoltage();
        float t3 = res2_n->getVoltage();
        float t4 = vol_p->getVoltage();
        QVERIFY(t1 == -20);
        QVERIFY(t2 == -10);
        QVERIFY(t3 == 0);
        QVERIFY(t4 == 10);  //FIXME
        //TODO e link? modifica il puntatore originale??

    };

};

QTEST_MAIN(TestCircuitWidget)
#include "TestCircuitWidget.moc"

#endif //FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_H CIRCUITWIDGET_H