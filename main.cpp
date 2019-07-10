#include <iostream>
#include "Component.h"
#include "Circuit.h"
#include "CircuitWidget.h"
#include <QApplication>
#include <QMainWindow>

//TODO: What the heck is argv i only need it to create the application for Qt
int main(int argc, char **argv) {

    QApplication app(argc,argv);
    QMainWindow mainWindow;
    CircuitWidget* graph;
    Circuit c;
    graph=new CircuitWidget(&c);
    c.setObserver(graph);
    mainWindow.setCentralWidget(graph);
    mainWindow.show();

    auto *gen = new Component(1,0,10);
    auto  *pgen = new Node(50,50);
    auto  *ngen = new Node(50,100);
    c.add(gen,pgen,ngen);

    app.exec();

    return 0;
}