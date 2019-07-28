//
// Created by cipher on 18/07/19.
//

#include "MainWindow.h"
#include "CurrentSource.h"
#include "VoltageSource.h"
#include "Resistor.h"
#include "Component.h"
#include "CircuitScene.h"
#include "ResourceManager.h"
#include "Voltmeter.h"

#include <QtWidgets>
#include <iostream>


MainWindow::MainWindow(CircuitScene *scene) {

    createToolBox();
    createActions();
    menuBar()->setNativeMenuBar(false);
    createMenus();
    createToolbars();

    auto *layout= new QHBoxLayout;
    this->scene=scene;
    view= new QGraphicsView(scene);
    view->centerOn(0,0);

    layout->addWidget(toolBox,1);
    layout->addWidget(view,5);

    QWidget *w=new QWidget;
    w->setLayout(layout);

    setCentralWidget(w);

    setWindowTitle(tr("Circuit Simulator"));
    setUnifiedTitleAndToolBarOnMac(true);

}


void MainWindow::createToolBox() {

    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup,QOverload<int>::of((&QButtonGroup::buttonClicked)),this,&MainWindow::buttonGroupClicked);

    auto *toolboxLayout= new QGridLayout;
    toolboxLayout->addWidget(createCellWidget(tr("resistor"),":/images/resistor.png",Component::resistor),0,0);
    toolboxLayout->addWidget(createCellWidget(tr("Voltage Source"),":/images/voltagesource.png",Component::voltageSource),0,1);
    toolboxLayout->addWidget(createCellWidget(tr("Current Source"),":/images/currentsource.png",Component::currentSource),1,0);
    toolboxLayout->addWidget(createCellWidget(tr("wire"),":/images/wire.png",Component::wire),1,1);
    toolboxLayout->addWidget(createCellWidget(tr("amperometer"),":/images/amperometer.png",Component::amperometer),2,1);
    toolboxLayout->addWidget(createCellWidget(tr("voltmeter"),":/images/voltm.png",Component::voltmeter),2,0);
    toolboxLayout->addWidget(createCellWidget(tr("ground"),":/images/ground.png",Component::ground),0,2);
    toolboxLayout->addWidget(createCellWidget(tr("vcvs"),":/images/vcvs.png",Component::vcvs),1,2);
    toolboxLayout->setRowStretch(3,10);
    toolboxLayout->setColumnStretch(3,10);

    auto itemWidget= new QWidget;
    itemWidget->setLayout(toolboxLayout);

    toolBox=new QToolBox;
    toolBox->setMinimumWidth(100);
    toolBox->addItem(itemWidget,tr("Electric Components"));


}

void MainWindow::createActions() {

    QIcon icon_delete= QIcon(":/images/delete.png");
    deleteAction=new QAction(icon_delete,tr("&Delete"),this);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteItems);

    QIcon icon_select= QIcon(":/images/pointer.png");
    selectAction=new QAction(icon_select,tr("&Select"),this);
    connect(selectAction, &QAction::triggered, this, &MainWindow::selectItems);

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit example"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);


    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("F1"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    QIcon icon_run=QIcon(":/images/play.png");
    runCircuitAction= new QAction(icon_run,tr("&Run"),this);
    connect(runCircuitAction,&QAction::triggered,this,&MainWindow::runCircuit);

}

void MainWindow::deleteItems() {
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    for (auto it : selectedItems)
        delete it;

}

void MainWindow::selectItems() {
    scene->setMode(CircuitScene::moveItem);
    //Qt non permette alcuna altra soluzione!
    //bool check=false;
    //for(const auto button:buttonGroup->buttons())
        //if(button->isChecked())
            //check=true;

    //if(check) {
        //buttonGroup->setExclusive(false);
        //buttonGroup->checkedButton()->setChecked(false);
        //buttonGroup->setExclusive(true);
    //}

}

void MainWindow::createToolbars() {

    editToolBar = addToolBar(tr("Edit"));

    editToolBar->addAction(deleteAction);
    editToolBar->addAction(selectAction);
    editToolBar->addAction(runCircuitAction);

    viewToolBar= addToolBar(tr("View"));

    sceneScaleCombo = new QComboBox;        //ZOOM,poco interessante
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),this, &MainWindow::sceneScaleChanged);

    viewToolBar->addWidget(sceneScaleCombo);


}


QWidget* MainWindow::createCellWidget(const QString &text, const QString &image, int id ) {

    QToolButton *button= new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50,50));
    button->setCheckable(true);
    buttonGroup->addButton(button,Qt::NoModifier);
    buttonGroup->setId(button,id);

    auto *layout= new QGridLayout;
    layout->addWidget(button,0,0,Qt::AlignCenter);
    layout->addWidget(new QLabel(text),1,0,Qt::AlignCenter);

    auto *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

void MainWindow::createMenus() {
    fileMenu=menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    itemMenu= menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);

    aboutMenu= menuBar()->addMenu(tr("&About"));
    aboutMenu->addAction(aboutAction);
}


void MainWindow::buttonGroupClicked(int type) {
    //TODO maybe there's a mode?
    buttonGroup->checkedButton()->setChecked(false);
    repaint(); //FIXME bruttissimo

    scene->setType(Component::types(type));
    scene->setMode(CircuitScene::modes(CircuitScene::insertItem));
    if(type!=Component::types::wire&&type!=Component::types::voltmeter&&type!=Component::types::amperometer&&type!=Component::types::ground) {
        std::string text =
                "Please,insert the correct value\n for your " + ResourceManager::getName(Component::types(type));
        QString string = QString::fromStdString(text);
        float value = QInputDialog::getDouble(this->parentWidget(), "Insert Value", string);
        scene->setcValue(value);
    }

}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Circuit Simulator"),
                       tr("Our <b>Circuit Simulator</b> can evaluate every kind "
                          "of ideal electronic circuit"));
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();                                             //metodo grafico per zoom
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::runCircuit() {

    scene->getCircuit()->solve();


}

