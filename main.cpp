#include <iostream>
#include "Component.h"
#include "Circuit.h"
#include "CircuitWidget.h"
#include <QApplication>
#include <QMainWindow>
#include "CurrentSource.h"
#include "VoltageSource.h"
#include "Wire.h"
#include "ModelException.h"

int main(int argc, char **argv) {

    QApplication app(argc,argv);
    QMainWindow mainWindow;
    CircuitWidget* graph;
    Circuit c;
    graph=new CircuitWidget(&c);
    c.setObserver(graph);
    mainWindow.setCentralWidget(graph);
    mainWindow.show();

    //FIXME bring in a test maybe?
    try {
        auto *curr = new CurrentSource(10);
        auto *curr_p = new Node(50, 50);
        auto *curr_n = new Node(50, 100);
        c.add(curr, curr_p, curr_n);
        c.add(curr,curr_n,curr_p);
    }catch (ModelException *e){
        std::cout<<e->what()<<std::endl;
    }

    auto *volt = new VoltageSource(10);
    auto  *volt_p = new Node(350,50);
    auto  *volt_n = new Node(350,100);
    c.add(volt,volt_p,volt_n);

    auto *wire = new Wire();
    auto  *wire_p = new Node(150,300,true);
    auto  *wire_n = new Node(250,300,true);
    c.add(wire,wire_p,wire_n);

    app.exec();

    return 0;
}