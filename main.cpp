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
    Circuit c;
    auto graph=new CircuitWidget(&c);
    c.setObserver(graph);
    mainWindow.setCentralWidget(graph);
    mainWindow.show();

    app.exec();

    return 0;
}