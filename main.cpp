#include <iostream>
#include "Circuit.h"
#include "CircuitWidget.h"
#include <QApplication>
#include <QMainWindow>
#include "CurrentSource.h"
#include "VoltageSource.h"
#include "Wire.h"
#include "MainWindow.h"

int main(int argc, char **argv) {

    QApplication app(argc,argv);
    Q_INIT_RESOURCE(components);

    CircuitWidget* graph;
    Circuit c;
    graph=new CircuitWidget(&c);
    MainWindow mainWindow(graph);
    c.setObserver(graph);
    mainWindow.setGeometry(100, 100, 800, 500);
    mainWindow.show();

    auto *curr = new CurrentSource(10);
    auto *curr_p = new Node(50, 50);
    auto *curr_n = new Node(50, 100);
    c.add(curr, curr_p, curr_n);

    auto *volt = new VoltageSource(10);
    auto  *volt_p = new Node(350,50);
    auto  *volt_n = new Node(350,100);
    c.add(volt,volt_p,volt_n);

    auto *wire = new Wire();
    auto  *wire_p = new Node(150,300,true);
    auto  *wire_n = new Node(250,300);
    c.add(wire,wire_p,wire_n);


    app.exec();

    return 0;
}