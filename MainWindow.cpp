//
// Created by cipher on 18/07/19.
//

#include <QtWidgets/QGridLayout>
#include "MainWindow.h"
#include <QAction>
#include <QToolBar>

MainWindow::MainWindow(CircuitWidget *view) {


    createToolBox();
    createActions();
    createToolbars();

    auto *layout= new QHBoxLayout;
    layout->addWidget(toolBox);
    layout->addWidget(view);

    QWidget *widget=new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);

    setWindowTitle(tr("Circuit Simulator"));
    setUnifiedTitleAndToolBarOnMac(true);

}


void MainWindow::createToolBox() {

    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);

    QGridLayout *toolboxLayout= new QGridLayout;
    toolboxLayout->setRowStretch(3,10);
    toolboxLayout->setColumnStretch(2,10);

    auto itemWidget= new QWidget;
    itemWidget->setLayout(toolboxLayout);

    toolBox=new QToolBox;
    toolBox->setMinimumWidth(100);
    toolBox->addItem(itemWidget,tr("resistenza"));


}

void MainWindow::createActions() {

    QIcon icon= QIcon(":/images/delete.png");
    deleteAction=new QAction(icon,tr("&Delete"),this);


}

void MainWindow::createToolbars() {

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);

}