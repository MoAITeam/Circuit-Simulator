//
// Created by Sierra on 2019-07-01.
//

#ifndef FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_CPP
#define FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_CPP

#include <QtTest/QtTest>
#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QtWidgets>

#include "../sources/CircuitScene.h"
#include "../sources/ResourceManager.h"
#include "../sources/ModelException.h"
#include "../sources/MatrixException.h"
#include "../sources/MainWindow.h"

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


    void removeRandomComponent() {
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
        circuit->clear();
         bool status = false;
         if (widget->scene()->items().size() == 0) //items has always one void
             status = true;
         QVERIFY(status);
    };


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

        circuit->solve();

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


  void testMatrix(){

        auto circuit = new Circuit;
        auto scene = new CircuitScene(circuit);
        auto widget = new QGraphicsView();
        widget->setScene(scene);

        auto *vol = new VoltageSource(10);
        auto *vol_p = new Node(100,50);
        auto *vol_n = new Node(200,75);         //FIXME ERRORE STRANO
        circuit->add(vol,vol_p,vol_n);

        auto *res1 = new Resistor(100);
        auto* res_n=new Node(100,100);
        circuit->add(res1,res_n,vol_p);

        auto* res2=new Resistor(100);
        circuit->add(res2,res_n,vol_n);

        int check= circuit->getMatrix()(2,3);
        QVERIFY(circuit->getMatrix()(0,0)==1);
        QVERIFY(circuit->getMatrix()(0,1)==0);
        QVERIFY(circuit->getMatrix()(0,2)==0);
        QVERIFY(circuit->getMatrix()(0,3)==0);
        QVERIFY(circuit->getMatrix()(0,4)==0);
        QVERIFY(circuit->getMatrix()(0,5)==0);
        QVERIFY(circuit->getMatrix()(0,6)==0);
        QVERIFY(circuit->getMatrix()(0,7)==-1);
        QVERIFY(circuit->getMatrix()(0,8)==1);

       QVERIFY(circuit->getMatrix()(1,0)==0);
       QVERIFY(circuit->getMatrix()(1,1)==1);
       QVERIFY(circuit->getMatrix()(1,2)==0);
       QVERIFY(circuit->getMatrix()(1,3)==0);
       QVERIFY(circuit->getMatrix()(1,4)==0);
       QVERIFY(circuit->getMatrix()(1,5)==0);
       QVERIFY(circuit->getMatrix()(1,6)==-1);
       QVERIFY(circuit->getMatrix()(1,7)==0);
       QVERIFY(circuit->getMatrix()(1,8)==1);

       QVERIFY(circuit->getMatrix()(2,0)==0);
       QVERIFY(circuit->getMatrix()(2,1)==0);
       QVERIFY(circuit->getMatrix()(2,2)==1);
       QVERIFY(circuit->getMatrix()(2,3)==0);
       QVERIFY(circuit->getMatrix()(2,4)==0);
       QVERIFY(circuit->getMatrix()(2,5)==-1);
       QVERIFY(circuit->getMatrix()(2,6)==1);
       QVERIFY(circuit->getMatrix()(2,7)==0);
       QVERIFY(circuit->getMatrix()(2,8)==0);

       QVERIFY(circuit->getMatrix()(3,0)==1);
       QVERIFY(circuit->getMatrix()(3,1)==0);
       QVERIFY(circuit->getMatrix()(3,2)==0);
       QVERIFY(circuit->getMatrix()(3,3)==-100);
       QVERIFY(circuit->getMatrix()(3,4)==0);
       QVERIFY(circuit->getMatrix()(3,5)==0);
       QVERIFY(circuit->getMatrix()(3,6)==0);
       QVERIFY(circuit->getMatrix()(3,7)==0);
       QVERIFY(circuit->getMatrix()(3,8)==0);

       QVERIFY(circuit->getMatrix()(4,0)==0);
       QVERIFY(circuit->getMatrix()(4,1)==1);
       QVERIFY(circuit->getMatrix()(4,2)==0);
       QVERIFY(circuit->getMatrix()(4,3)==0);
       QVERIFY(circuit->getMatrix()(4,4)==-100);
       QVERIFY(circuit->getMatrix()(4,5)==0);
       QVERIFY(circuit->getMatrix()(4,6)==0);
       QVERIFY(circuit->getMatrix()(4,7)==0);
       QVERIFY(circuit->getMatrix()(4,8)==0);

       QVERIFY(circuit->getMatrix()(5,0)==0);
       QVERIFY(circuit->getMatrix()(5,1)==0);
       QVERIFY(circuit->getMatrix()(5,2)==1);
       QVERIFY(circuit->getMatrix()(5,3)==0);
       QVERIFY(circuit->getMatrix()(5,4)==0);
       QVERIFY(circuit->getMatrix()(5,5)==0);
       QVERIFY(circuit->getMatrix()(5,6)==0);
       QVERIFY(circuit->getMatrix()(5,7)==0);
       QVERIFY(circuit->getMatrix()(5,8)==10);

       QVERIFY(circuit->getMatrix()(6,0)==0);
       QVERIFY(circuit->getMatrix()(6,1)==0);
       QVERIFY(circuit->getMatrix()(6,2)==0);
       QVERIFY(circuit->getMatrix()(6,3)==0);
       QVERIFY(circuit->getMatrix()(6,4)==1);
       QVERIFY(circuit->getMatrix()(6,5)==1);
       QVERIFY(circuit->getMatrix()(6,6)==0);
       QVERIFY(circuit->getMatrix()(6,7)==0);
       QVERIFY(circuit->getMatrix()(6,8)==0);

       QVERIFY(circuit->getMatrix()(7,0)==0);
       QVERIFY(circuit->getMatrix()(7,1)==0);
       QVERIFY(circuit->getMatrix()(7,2)==0);
       QVERIFY(circuit->getMatrix()(7,3)==1);
       QVERIFY(circuit->getMatrix()(7,4)==0);
       QVERIFY(circuit->getMatrix()(7,5)==-1);
       QVERIFY(circuit->getMatrix()(7,6)==0);
       QVERIFY(circuit->getMatrix()(7,7)==0);
       QVERIFY(circuit->getMatrix()(7,8)==0);

       QVERIFY(circuit->getMatrix()(8,0)==0);
       QVERIFY(circuit->getMatrix()(8,1)==0);
       QVERIFY(circuit->getMatrix()(8,2)==0);
       QVERIFY(circuit->getMatrix()(8,3)==-1);
       QVERIFY(circuit->getMatrix()(8,4)==-1);
       QVERIFY(circuit->getMatrix()(8,5)==0);
       QVERIFY(circuit->getMatrix()(8,6)==0);
       QVERIFY(circuit->getMatrix()(8,7)==0);
       QVERIFY(circuit->getMatrix()(8,8)==0);


   }

   void checkButtons(){

       auto circuit = new Circuit;
       auto scene = new CircuitScene(circuit);
       auto widget = new QGraphicsView();
       widget->setScene(scene);
       auto mw=new MainWindow(scene);

       auto *vol = new VoltageSource(10);
       auto *vol_p = new Node(100,50);
       auto *vol_n = new Node(200,75);
       circuit->add(vol,vol_p,vol_n);

       auto *res1 = new Resistor(100);
       auto* res_n=new Node(100,100);
       circuit->add(res1,res_n,vol_p);

       auto* res2=new Resistor(100);
       circuit->add(res2,res_n,vol_n);

       res2->setSelected(true);
       int check=widget->scene()->items().size();
       mw->getDeleteAction()->triggered(true);
        QVERIFY(widget->scene()->items().size()==5);

       mw->getSelectAllAction()->triggered(true);
       mw->getDeleteAction()->triggered(true);
       QVERIFY(widget->scene()->items().size()==0);


        auto res=new Resistor(10);
        auto n1=new Node(300,100);
        auto n2=new Node(300,50);
        circuit->add(res,n1,n2);

        mw->getClearAction()->triggered(true);
        QVERIFY(widget->scene()->items().size()==0);

   }
};

QTEST_MAIN(TestCircuitWidget)
#include "TestCircuitWidget.moc"

#endif //FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_H CIRCUITWIDGET_H