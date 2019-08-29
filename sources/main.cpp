#include <iostream>
#include <QApplication>
#include <QMainWindow>
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

    app.exec();

    return 0;
}

