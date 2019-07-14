#include <iostream>
#include "Component.h"
#include "Circuit.h"
#include "CircuitWidget.h"
#include <QApplication>
#include <QMainWindow>
#include "CurrentSource.h"
#include "VoltageSource.h"
#include "Wire.h"
#include "Resistor.h"

int main(int argc, char **argv) {

    QApplication app(argc,argv);
    QMainWindow mainWindow;
    CircuitWidget* graph;
    Circuit c;
    graph=new CircuitWidget(&c);
    c.setObserver(graph);
    mainWindow.setCentralWidget(graph);
    mainWindow.show();

   /* auto *curr = new CurrentSource(10);
    auto  *curr_p = new Node(50,50);
    auto  *curr_n = new Node(50,100);
    c.add(curr,curr_p,curr_n);

    auto *volt = new VoltageSource(10);
    auto  *volt_p = new Node(350,50);
    auto  *volt_n = new Node(350,100);
    c.add(volt,volt_p,volt_n);

    auto *wire = new Wire();
    auto  *wire_p = new Node(150,300,true);
    auto  *wire_n = new Node(250,300,true);
    c.add(wire,wire_p,wire_n);*/



    auto *vol = new VoltageSource(30);
    auto  *vol_p = new Node(50,50);
    auto  *vol_n = new Node(50,100);
    c.add(vol,vol_p,vol_n);

    auto *res1 = new Resistor(10);
    auto  *res1_p = new Node(50,100);
    auto  *res1_n = new Node(100,100);
    c.add(res1,res1_p,res1_n);

    auto *res2 = new Resistor(10);
    auto  *res2_p = new Node(100,100);
    auto  *res2_n = new Node(100,50);
    c.add(res2,res2_p,res2_n);

    auto *res3 = new Resistor(10);
    auto  *res3_p = new Node(100,50);
    auto  *res3_n = new Node(50,50);
    c.add(res3,res3_p,res3_n);

    app.exec();

    return 0;
}