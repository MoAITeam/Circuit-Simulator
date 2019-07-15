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
#include "ModelException.h"
#include "MatrixException.h"

#define EPSILON 0.0001

class TestCircuitWidget: public QObject {

private:

    bool isEqual(double a, double b)
    {
        float fa=fabs(a);
        float fb=fabs(b);
        float absd=fabs(fa-fb);
        return (absd < (EPSILON));
    }

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

        auto *res1 = new Resistor(10);
        auto *res1_p = new Node(50, 100);
        auto *res1_n = new Node(100, 100);

        auto *res2 = new Resistor(10);
        auto *res2_p = new Node(100, 100);
        auto *res2_n = new Node(100, 50, 1); //se lo dichiari dopo di terra non fa

        auto *res3 = new Resistor(10);
        auto *res3_p = new Node(100, 50);
        auto *res3_n = new Node(50, 50);

        try {
            circuit->add(vol, vol_p, vol_n);
            circuit->add(res1, res1_p, res1_n);
            circuit->add(res2, res2_p, res2_n);
            circuit->add(res3, res3_p, res3_n);
        }
        catch (ModelException e){
            //For now, exceptions are only printed and may still quit the program
            std::cerr<<e.what()<<std::endl;
        }catch (MatrixException e){
            //Should be caught by model
            std::cerr<<e.what()<<std::endl;
        }

        QTest::keyPress(widget , Qt::Key::Key_S);

        float c1 = res1->getCurrent();
        float c2 = res2->getCurrent();
        float c3 = res3->getCurrent();
        float c4 = vol->getCurrent();
        QVERIFY(isEqual(c1,1));
        QVERIFY(isEqual(c2,1));
        QVERIFY(isEqual(c3,1));
        QVERIFY(isEqual(c4,1));

    };

};

QTEST_MAIN(TestCircuitWidget)
#include "TestCircuitWidget.moc"

#endif //FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_H CIRCUITWIDGET_H