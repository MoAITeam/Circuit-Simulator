//
// Created by cipher on 18/07/19.
//

#include "MainWindow.h"

#include <QtWidgets>


MainWindow::MainWindow(CircuitScene *scene) {


    createToolBox();
    createActions();
    createMenus();
    createToolbars();


    auto *layout= new QHBoxLayout;
    auto view= new QGraphicsView(scene);
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
    buttonGroup->setExclusive(true);

    auto *toolboxLayout= new QGridLayout;
    toolboxLayout->addWidget(createCellWidget(tr("Resistor"),":/images/resistance.png"),0,0);
    toolboxLayout->addWidget(createCellWidget(tr("Voltage Source"),":/images/voltagesource.png"),0,1);
    toolboxLayout->addWidget(createCellWidget(tr("Current Source"),":/images/currentsource.png"),1,0);
    toolboxLayout->setRowStretch(3,10);
    toolboxLayout->setColumnStretch(3,10);

    auto itemWidget= new QWidget;
    itemWidget->setLayout(toolboxLayout);

    toolBox=new QToolBox;
    toolBox->setMinimumWidth(100);
    toolBox->addItem(itemWidget,tr("Electric Components"));


}

void MainWindow::createActions() {

    QIcon icon= QIcon(":/images/delete.png");
    deleteAction=new QAction(icon,tr("&Delete"),this);


}

void MainWindow::createToolbars() {

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);



}


QWidget* MainWindow::createCellWidget(const QString &text, const QString &image ) {

    QToolButton *button= new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50,50));
    button->setCheckable(true);
    buttonGroup->addButton(button,Qt::NoModifier);

    auto *layout= new QGridLayout;
    layout->addWidget(button,0,0,Qt::AlignCenter);
    layout->addWidget(new QLabel(text),1,0,Qt::AlignCenter);

    auto *widget = new QWidget;
    widget->setLayout(layout);

    return widget;


}

void MainWindow::createMenus() {
    fileMenu=menuBar()->addMenu(tr("&File"));
    //fileMenu->addAction(exitAction);

    itemMenu= menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
}

