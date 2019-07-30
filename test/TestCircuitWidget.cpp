//
// Created by Sierra on 2019-07-01.
//

#ifndef FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_CPP
#define FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_CPP

#include <QtTest/QtTest>
#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include "../sources/CircuitScene.h"
#include "../sources/ResourceManager.h"
#include "../sources/ModelException.h"
#include "../sources/MatrixException.h"

#define EPSILON 0.1

class TestCircuitWidget: public QObject {

Q_OBJECT

ResourceManager* manager=new ResourceManager();

private:
    bool isEqual(float value1, float value2) {

        if (fabs(fabs(value1) - fabs(value2)) < (EPSILON))
            return true;
        else
            return false;
    }


private slots:

    void testAddItem() {
        Circuit *circuit = new Circuit;
        CircuitScene *scene = new CircuitScene(circuit);
        auto c = new Resistor(5);
        auto p = new Node(50, 50);
        auto n = new Node(100, 100);
        circuit->add(c, p, n);
        QVERIFY(c->getNodes().first->x() == 50 && c->getNodes().first->y() == 50 && c->getNodes().second->x() == 100 &&
                c->getNodes().second->y() == 100);
        bool found = false;
        for (auto item : scene->items()) {
            if (item == c) {
                if (found == false)
                    found = true;
                else
                    found = false; //duplicated
            }
        }
        QVERIFY(found);
    };

    //FIXME double click doesn't work anymore...
    /*void removeRandomComponent() {
        QMainWindow *mainWindow = new QMainWindow();
         auto circuit = new Circuit;
         auto scene = new CircuitScene(circuit);
         auto widget = new QGraphicsView();
         widget->setScene(scene);
         auto c = new Resistor(10);
         auto p = new Node(50, 50);
         auto n = new Node(100, 100);
        mainWindow->setCentralWidget(widget);
        circuit->add(c, p, n);
         QTest::mouseDClick(widget->viewport(), Qt::LeftButton, Qt::NoModifier, widget->mapFromScene(100,100));
         QTest::mouseClick(widget->viewport(), Qt::LeftButton, Qt::NoModifier,  widget->mapFromScene(0,0));
         QTest::mouseDClick(widget->viewport(), Qt::LeftButton, Qt::NoModifier,  widget->mapFromScene(48,48));
         bool status = false;
         if (widget->scene()->items().size() == 0) //items has always one void
             status = true;
         QVERIFY(status);
    };*/


    void testSampleCircuit() {



        QMainWindow *mainWindow = new QMainWindow();
        auto circuit = new Circuit;
        auto scene = new CircuitScene(circuit);
        auto widget = new QGraphicsView();
        widget->setScene(scene);

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


try{
    circuit->add(vol, vol_p, vol_n);
    circuit->add(res1, res1_p, res1_n);
    circuit->add(res2, res2_p, res2_n);
    circuit->add(res3, res3_p, res3_n);
    }catch (ModelException e){
    //For now, exceptions are only printed and may still quit the program
    std::cout<<e.what()<<std::endl;
    }catch (MatrixException e){
    std::cout<<e.what()<<std::endl;
    }

QTest::keyPress(widget , Qt::Key::Key_S);

        float t1 = res1_p->getVoltage();
        float t2 = res2_p->getVoltage();
        float t3 = res3_p->getVoltage();
        float t4 = vol_p->getVoltage();
        QVERIFY(isEqual(t1,-20));
        QVERIFY(isEqual(t2,-10));
        QVERIFY(isEqual(t3,0));
        QVERIFY(isEqual(t4,10));

        float c1=res1->getCurrent();
        float c2=res2->getCurrent();
        float c3=res3->getCurrent();

        QVERIFY(isEqual(c1,-1));
        QVERIFY(isEqual(c2,1));
        QVERIFY(isEqual(c3,-1));

        float v1=res1->getVoltage();
        float v2=res2->getVoltage();
        float v3=res3->getVoltage();

        QVERIFY(isEqual(v1,-10));
        QVERIFY(isEqual(v2,10));
        QVERIFY(isEqual(v3,-10));


    };


    void testComplicatedCircuit() {

        QMainWindow *mainWindow = new QMainWindow();
        auto circuit = new Circuit;
        auto scene = new CircuitScene(circuit);
        auto widget = new QGraphicsView();
        widget->setScene(scene);

        auto *curr = new CurrentSource(10);
        auto *curr_p = new Node(50, 50);
        auto *curr_n = new Node(50, 100);
        circuit->add(curr, curr_p, curr_n);

        auto *res1 = new Resistor(5);
        auto *res1_p = new Node(50, 100);
        auto *res1_n = new Node(100, 100);
        circuit->add(res1, res1_p, res1_n);

        auto *res2 = new Resistor(5);
        auto *res2_p = new Node(100, 100);
        auto *res2_n = new Node(100, 50);
        circuit->add(res2, res2_p, res2_n);

        auto *res3 = new Resistor(5);
        auto *res3_p = new Node(100, 50);
        auto *res3_n = new Node(50, 50);
        circuit->add(res3, res3_p, res3_n);

        auto *wir= new Wire();
        auto *wir_p= new Node(100,100,1);
        auto *wir_n= new Node(150,100,1);
        circuit->add(wir,wir_p,wir_n);

        auto *res4= new Resistor(5);
        auto *res4_p= new Node(150,100);
        auto *res4_n=new Node(200,100);
        circuit->add(res4,res4_p,res4_n);

        auto *vol= new VoltageSource(10);
        auto *vol_p= new Node(200,100);
        auto *vol_n= new Node(200,50);
        circuit->add(vol,vol_p,vol_n);

        auto *res5 = new Resistor(5);
        auto *res5_p = new Node(200, 50);
        auto *res5_n = new Node(150, 50);
        circuit->add(res5, res5_p, res5_n);

        auto *res6 = new Resistor(5);
        auto *res6_p = new Node(150, 50);
        auto *res6_n = new Node(150, 100);
        circuit->add(res6, res6_p, res6_n);

        circuit->solve();
        float t1=curr_p->getVoltage();
        float t2= res1_p->getVoltage();
        float t3= res2_p->getVoltage();
        float t4= res3_p->getVoltage();
        float t5= wir_p->getVoltage();
        float t6= res4_n->getVoltage();
        float t7= vol_n->getVoltage();
        float t8= res5_n->getVoltage();
        float t9= res6_p->getVoltage();

        QVERIFY(isEqual(t1,-100) );
        QVERIFY(isEqual(t2,50) );
        QVERIFY(isEqual(t3,0) );
        QVERIFY(isEqual(t4,-50) );
        QVERIFY(isEqual(t5,0) );
        QVERIFY(isEqual(t6,3.3333) );
        QVERIFY(isEqual(t7,-6.6666) );
        QVERIFY(isEqual(t8,-3.3333) );
        QVERIFY(isEqual(t9,-3.3333) );




    };
};

QTEST_MAIN(TestCircuitWidget)
#include "TestCircuitWidget.moc"

#endif //FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_H CIRCUITWIDGET_H