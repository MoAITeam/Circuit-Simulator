#include <iostream>
#include "Circuit.h"
#include "CircuitScene.h"
#include <QApplication>
#include <QMainWindow>
#include "CurrentSource.h"
#include "VoltageSource.h"
#include "Wire.h"
#include "MainWindow.h"
#include "ResourceManager.h"


int main(int argc, char **argv) {

    QApplication app(argc,argv);
    Q_INIT_RESOURCE(components);

    ResourceManager resourceManager;
    CircuitScene* graph;
    Circuit c;
    graph=new CircuitScene(&c);
    MainWindow mainWindow(graph);
    c.setObserver(graph);
    mainWindow.setGeometry(100, 100, 800, 500);
    mainWindow.show();

    auto *wire = new Wire();
    auto  *wire_p = new Node(150,300,true);
    auto  *wire_n = new Node(250,300);
    c.add(wire,wire_p,wire_n);


    app.exec();

    return 0;
}