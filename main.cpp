#include <iostream>
#include "Component.h"
#include "Circuit.h"
#include "CircuitWidget.h"
#include <QApplication>
#include <QMainWindow>

//TODO: What the heck is argv i only need it to create the application for Qt
int main(int argc, char **argv) {

    /*try {
        Component *component = new Component(5);
        Node *a = new Node(0, 0);
        Node *b = new Node(20, 20);
        c.add(component, a, b);
    }
    catch (const char* e)
    {
        std::cout<<e<<std::endl;
    }*/

    QApplication app(argc,argv);
    QMainWindow mainWindow;
    CircuitWidget* graph;
    Circuit c;
    graph=new CircuitWidget(&c);
    c.setObserver(graph);
    mainWindow.setCentralWidget(graph);
    mainWindow.show();

    app.exec();
    c.print();

    return 0;
}