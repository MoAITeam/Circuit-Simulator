//
// Created by Sierra on 2019-08-22.
//

#include "MainWindow.h"

//TODO these have no label

void MainWindow::drawCircuits(QString text) {

    if(text=="Parallel Circuit"){

        scene->getCircuit()->clear();

        auto res=new Resistor(10);
        auto n1=new Node(400,160,1);
        auto n2=new Node(400,60);
        scene->getCircuit()->add(res,n1,n2);

        auto w1= new Wire;
        auto n3=new Node(300,60);
        scene->getCircuit()->add(w1,n2,n3);

        auto w2= new Wire;
        auto n4=new Node(300,160);
        scene->getCircuit()->add(w2,n1,n4);

        auto w3=new Wire;
        scene->getCircuit()->add(w3,n4,n3);

        auto w4=new Wire;
        auto n5=new Node(200,160);
        scene->getCircuit()->add(w4,n4,n5);

        auto w5= new Wire;
        auto n6=new Node(200,60);
        scene->getCircuit()->add(w5,n3,n6);

        auto vol= new VoltageSource(10);
        scene->getCircuit()->add(vol,n5,n6);
        //n3->setGnd(true);


    }
    else if(text==tr("Voltage Divider")){

        scene->getCircuit()->clear();

        auto res1=new Resistor(10);
        auto n1=new Node(400,160,1);
        auto n2=new Node(400,60);
        scene->getCircuit()->add(res1,n1,n2);

        auto res2= new Resistor(10);
        auto n3=new Node(300,60);
        scene->getCircuit()->add(res2,n2,n3);

        auto res3= new Resistor(10);
        auto n4=new Node(300,160);
        scene->getCircuit()->add(res3,n1,n4);

        auto res4=new Resistor(10);
        auto n5=new Node(200,160);
        scene->getCircuit()->add(res4,n4,n5);

        auto res5= new Resistor(10);
        auto n6=new Node(200,60);
        scene->getCircuit()->add(res5,n3,n6);

        auto vol= new VoltageSource(10);
        scene->getCircuit()->add(vol,n5,n6);


    }

    else if(text=="Current Divider"){

        scene->getCircuit()->clear();

        auto res1=new Resistor(10);
        auto n1=new Node(400,160,1);
        auto n2=new Node(400,60);
        scene->getCircuit()->add(res1,n1,n2);

        auto w1= new Wire;
        auto n3=new Node(300,60);
        scene->getCircuit()->add(w1,n2,n3);

        auto w2= new Wire;
        auto n4=new Node(300,160);
        scene->getCircuit()->add(w2,n1,n4);

        auto res2=new Resistor(10);
        scene->getCircuit()->add(res2,n4,n3);

        auto w4=new Wire;
        auto n5=new Node(200,160);
        scene->getCircuit()->add(w4,n4,n5);

        auto w5= new Wire;
        auto n6=new Node(200,60);
        scene->getCircuit()->add(w5,n3,n6);

        auto curr= new CurrentSource(10);
        scene->getCircuit()->add(curr,n5,n6);


    }

    else if(text=="Strange One"){

        scene->getCircuit()->clear();

        auto vol1=new VoltageSource(10);
        auto n1=new Node(400,200,1);
        auto n2=new Node(400,50);
        scene->getCircuit()->add(vol1,n1,n2);

        auto res1= new Resistor(10);
        auto n3=new Node(250,50);
        scene->getCircuit()->add(res1,n2,n3);

        auto res2= new Resistor(10);
        auto n4=new Node(250,200);
        scene->getCircuit()->add(res2,n1,n4);

        auto vol2=new VoltageSource(10);
        scene->getCircuit()->add(vol2,n4,n3);

        auto res3= new Resistor(10);
        scene->getCircuit()->add(res3,n2,n4);


    }

    else if(text=="Controlled One"){

        scene->getCircuit()->clear();

        auto res1=new Resistor(10);
        auto n2= new Node(300,160);
        auto n7=new Node(300,60);
        scene->getCircuit()->add(res1,n2,n7);

        auto wir1=new Wire;
        auto n1=new Node(400,160,1);
        scene->getCircuit()->add(wir1,n2,n1);

        auto vcvs=new VCVS(10,res1);
        auto n8=new Node(400,60);
        scene->getCircuit()->add(vcvs,n1,n8);

        auto wir2=new Wire;
        scene->getCircuit()->add(wir2,n8,n7);

        auto wir4=new Wire;
        auto n5=new Node(100,60);
        scene->getCircuit()->add(wir4,n7,n5);

        auto wir5=new Wire;
        auto n4=new Node(100,160);
        scene->getCircuit()->add(wir5,n2,n4);

        auto curr=new CurrentSource(10);
        scene->getCircuit()->add(curr,n4,n5);

    }

    else if(text=="Trasformatore"){

        //rapporto di 2
        scene->getCircuit()->clear();

        auto vol=new VoltageSource(10);
        auto n1=new Node(500,200,1);
        auto n2=new Node(500,100);
        scene->getCircuit()->add(vol,n1,n2);

        auto res1=new Resistor(10);
        auto n3=new Node(400,200);
        scene->getCircuit()->add(res1,n1,n3);

        auto w1=new Wire;
        auto n4=new Node(400,100);
        scene->getCircuit()->add(w1,n2,n4);

        auto w2=new Wire;
        auto n6= new Node(300,100);
        scene->getCircuit()->add(w2,n4,n6);

        auto n9=new Node(200,200);
        auto n10=new Node(200,100);

        auto n5=new Node(300,200);
        auto w3=new Wire;
        scene->getCircuit()->add(w3,n5,n9);

        auto w4=new Wire;
        scene->getCircuit()->add(w4,n6,n10);

        auto cccs=new CCCS(2,w3);
        w3->addDependent();
        scene->getCircuit()->add(cccs,n3,n4);

        auto vcvs= new VCVS(2,cccs);
        cccs->addDependent();
        scene->getCircuit()->add(vcvs,n6,n5);

        auto curr=new CurrentSource(10);
        scene->getCircuit()->add(curr,n9,n10);

    }

}