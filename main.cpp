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

    auto gen = new Component(1,0,10);
    auto  pgen = new Node(50,50);
    auto  ngen = new Node(50,100);
    c.add(gen,pgen,ngen);

    auto r1=new Component(1,-5,0);
    auto  p1= new Node(50,50);
    auto  n1= new Node(100,50);
    c.add(r1,n1,p1);

    auto r2=new Component(1,-5,0);
    auto  p2= new Node(100,50);
    auto  n2= new Node(50,100);
    c.add(r2,n2,p2);



    app.exec();

    return 0;
}