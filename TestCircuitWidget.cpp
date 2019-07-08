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
        mainWindow->update();
        QTest::mouseDClick(widget->viewport(),Qt::LeftButton,Qt::NoModifier,widget->mapFromScene(50,50)); //FIXME FUCK.
        //delete c;
        //delete p;
        //delete n;
        bool status =false;
        if(widget->scene()->items().size()==1) //items has always one void
            status=true;
        QVERIFY(status==true);
    };
};

QTEST_MAIN(TestCircuitWidget)
#include "TestCircuitWidget.moc"

#endif //FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_H CIRCUITWIDGET_H