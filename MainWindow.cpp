//
// Created by cipher on 18/07/19.
//

#include <QtWidgets/QGridLayout>
#include "MainWindow.h"

MainWindow::MainWindow(CircuitWidget *view) {

    addToolBar(tr("edit"));

    QGridLayout *toolboxLayout= new QGridLayout;
    toolboxLayout->setRowStretch(3,10);
    toolboxLayout->setColumnStretch(2,10);

    auto widget1= new QWidget;
    widget1->setLayout(toolboxLayout);

    auto *toolbox=new QToolBox;
    toolbox->setMinimumWidth(100);
    toolbox->addItem(widget1,tr("resistenza"));

    auto *layout= new QHBoxLayout;
    layout->addWidget(toolbox);
    layout->addWidget(view);

    QWidget *widget=new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);

    setWindowTitle(tr("Circuit Simulator"));
    setUnifiedTitleAndToolBarOnMac(true);






}

