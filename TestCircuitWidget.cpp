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

class TestCircuitWidget: public QObject {
Q_OBJECT
private slots:
    void testAddItem(){
        Circuit* circuit= new Circuit;
        CircuitWidget* widget=new CircuitWidget(circuit);
        auto c = new Component(5);
        auto p = new Node(50,50);
        auto n = new Node(100,100);
        circuit->add(c, p, n);
        QVERIFY(c->getNodes().first->x()==50 && c->getNodes().first->y()==50 && c->getNodes().second->x()==100 && c->getNodes().second->y()==100);
        bool found=false;
        for (auto item : widget->scene()->items()){
            if (item==c) {
                if (found==false)
                    found=true;
                else
                    found=false; //duplicated
            }
        }
        QVERIFY(found);
};
    void removeRandomComponent(){
        QMainWindow* mainWindow=new QMainWindow();
        auto circuit=new Circuit;
        auto widget= new CircuitWidget(circuit);
        auto c= new Component(10);
        auto p = new Node(50,50);
        auto n = new Node(100,100);
        circuit->add(c,p,n);
        mainWindow->setCentralWidget(widget);
        QTest::mouseDClick(widget->viewport(),Qt::LeftButton,Qt::NoModifier,widget->mapFromScene(100,100));
        QTest::mouseClick(widget->viewport(),Qt::LeftButton,Qt::NoModifier,widget->mapFromScene(0,0));
        QTest::mouseDClick(widget->viewport(),Qt::LeftButton,Qt::NoModifier,widget->mapFromScene(48,48));
        bool status =false;
        if(widget->scene()->items().size()==0) //items has always one void
            status=true;
        QVERIFY(status==true);
    };
};

    void testSampleCircuit(){
        QMainWindow* mainWindow=new QMainWindow();
        auto circuit=new Circuit;
        auto widget= new CircuitWidget(circuit);
        auto curr=new currentSource(10);
        auto pCurr = new Node(50,50);
        auto nCurr = new Node(100,100);

        auto curr=new currentSource(10);
        auto pCurr = new Node(50,50);
        auto nCurr = new Node(100,100);


    }

QTEST_MAIN(TestCircuitWidget)
#include "TestCircuitWidget.moc"

#endif //FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_H CIRCUITWIDGET_H