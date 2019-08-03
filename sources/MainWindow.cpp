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

    this->scene=scene;

    createToolBox();
    createActions();
    menuBar()->setNativeMenuBar(false);
    createMenus();
    createToolbars();

    auto *layout= new QHBoxLayout;
    view= new QGraphicsView(scene);
    view->centerOn(0,0);

    layout->addWidget(toolBox,1);
    layout->addWidget(view,5);

    QWidget *w=new QWidget;
    w->setLayout(layout);

    setCentralWidget(w);

    setWindowTitle(tr("Circuit Simulator"));
    setUnifiedTitleAndToolBarOnMac(true);

    connect(scene,SIGNAL(insertValue()),this,SLOT(showDialog()));

}

void MainWindow::showDialog(){
    std::string text = "Please,insert the correct value";
    QString string = QString::fromStdString(text);
    float value = QInputDialog::getDouble(this->parentWidget(), "Insert Value", string);
    scene->setcValue(value);
}

void MainWindow::createToolBox() {

    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup,QOverload<int>::of((&QButtonGroup::buttonClicked)),this,&MainWindow::buttonGroupClicked);

    toolboxLayout= new QGridLayout;
    loadImages();
    toolboxLayout->setRowStretch(3,10);
    toolboxLayout->setColumnStretch(3,10);

    auto itemWidget= new QWidget;
    itemWidget->setLayout(toolboxLayout);

   circuitButtonGroup= new QButtonGroup(this);
   circuitButtonGroup->setExclusive(false);
    connect(circuitButtonGroup,QOverload<QAbstractButton *>::of((&QButtonGroup::buttonClicked)),this,&MainWindow::backgroundButtonGroupClicked);

    samplesLayout= new QGridLayout;

    samplesLayout->addWidget(createBackgroundCellWidget("Parallel Circuit",":/images/parallelcircuit.png"),0,0);
    samplesLayout->addWidget(createBackgroundCellWidget("Voltage Divider",":/images/voltagedivider.png"),0,1);
    samplesLayout->addWidget(createBackgroundCellWidget("Current Divider",":/images/currentdivider.png"),1,1);
    samplesLayout->addWidget(createBackgroundCellWidget("Strange One",":/images/strangeone.png"),1,0);
    samplesLayout->addWidget(createBackgroundCellWidget("Controlled One",":/images/controlled.png"),2,0);
    samplesLayout->addWidget(createBackgroundCellWidget("Trasformatore",":/images/trasformatore.png"),2,1);


    samplesLayout->setRowStretch(2,10);
    samplesLayout->setColumnStretch(2,10);

    auto backgroundWidget=new QWidget;
    backgroundWidget->setLayout(samplesLayout);

    toolBox=new QToolBox;
    toolBox->setMinimumWidth(100);
    toolBox->addItem(itemWidget,tr("Electric Components"));
    toolBox->addItem(backgroundWidget,tr("Sample Circuit"));


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

    QIcon icon_clear=QIcon(":/images/clear.png");
    clearAction= new QAction(icon_clear,tr("&Clear"),this);
    connect(clearAction,&QAction::triggered,this,&MainWindow::clearAll);

    QIcon icon_selAll=QIcon(":/images/selectall");
    selectAllAction= new QAction(icon_selAll,tr("&Select All"),this);
    connect(selectAllAction,&QAction::triggered,this,&MainWindow::selectAll);

}


void MainWindow::createToolbars() {

    editToolBar = addToolBar(tr("Edit"));

    editToolBar->addAction(deleteAction);
    editToolBar->addAction(selectAction);
    editToolBar->addAction(runCircuitAction);
    editToolBar->addAction(clearAction);
    editToolBar->addAction(selectAllAction);

    viewToolBar= addToolBar(tr("View"));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),this, &MainWindow::sceneScaleChanged);

    viewToolBar->addWidget(sceneScaleCombo);


}


QWidget* MainWindow::createCellWidget(const QString &text, const QPixmap &image, int id ) {

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

QWidget* MainWindow::createBackgroundCellWidget(const QString &text, const QString &image) {

    auto *button= new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50,50));
    button->setCheckable(true);
    circuitButtonGroup->addButton(button);

    auto layout= new QGridLayout;
    layout->addWidget(button,0,0,Qt::AlignHCenter);
    layout->addWidget(new QLabel(text),1,0,Qt::AlignCenter);

    auto widget= new QWidget;
    widget->setLayout(layout);

    return widget;


}

void MainWindow::createMenus() {
    fileMenu=menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    itemMenu= menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addAction(clearAction);
    itemMenu->addAction(selectAllAction);

    aboutMenu= menuBar()->addMenu(tr("&About"));
    aboutMenu->addAction(aboutAction);
}


void MainWindow::buttonGroupClicked(int type) {
    buttonGroup->checkedButton()->setChecked(false);
    toolboxLayout->update();
    samplesLayout->update();

    scene->setType(Component::types(type));
    if(type==Component::vcvs||type==Component::vccs||type==Component::cccs||type==Component::ccvs)
        scene->setMode(CircuitScene::selectDependent);
    else
        scene->setMode(CircuitScene::insertItem);

    if(type!=Component::wire&&type!=Component::voltmeter&&type!=Component::amperometer&&type!=Component::ground) {
        showDialog();
    }

}


void MainWindow::backgroundButtonGroupClicked(QAbstractButton *button) {

    const QList<QAbstractButton *> buttons = circuitButtonGroup->buttons();      //metodo per cliccare sui bottoni del backgrnd
    for (QAbstractButton *myButton : buttons) {
        if (myButton != button)
            button->setChecked(false);
    }

QString text=button->text();
    drawCircuits(text);

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
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::runCircuit() {

    scene->getCircuit()->solve();

}

void MainWindow::clearAll() {

    scene->getCircuit()->clear();

}

void MainWindow::selectAll() {

    for(auto &item : scene->items())
        if (item->type()>=Component::component)
            item->setSelected(true);
}

void MainWindow::deleteItems() {

    for(auto &item : scene->items())
        if(item->isSelected())
            delete item;
}

void MainWindow::selectItems() {
    scene->setMode(CircuitScene::moveItem);
}

void MainWindow::loadImages(){

    toolboxLayout->addWidget(createCellWidget(tr("resistor"),ResourceManager::getImage(Component::types::resistor),Component::resistor),0,0);
    toolboxLayout->addWidget(createCellWidget(tr("Voltage Source"),ResourceManager::getImage(Component::types::voltageSource),Component::voltageSource),0,1);
    toolboxLayout->addWidget(createCellWidget(tr("Current Source"),ResourceManager::getImage(Component::types::currentSource),Component::currentSource),1,0);
    toolboxLayout->addWidget(createCellWidget(tr("wire"),ResourceManager::getImage(Component::types::wire),Component::wire),1,1);
    toolboxLayout->addWidget(createCellWidget(tr("amperometer"),ResourceManager::getImage(Component::types::amperometer),Component::amperometer),2,1);
    toolboxLayout->addWidget(createCellWidget(tr("voltmeter"),ResourceManager::getImage(Component::types::voltmeter),Component::voltmeter),2,0);
    toolboxLayout->addWidget(createCellWidget(tr("ground"),ResourceManager::getImage(Component::types::ground),Component::ground),0,2);
    toolboxLayout->addWidget(createCellWidget(tr("vcvs"),ResourceManager::getImage(Component::types::vcvs),Component::vcvs),1,2);
    toolboxLayout->addWidget(createCellWidget(tr("vccs"),ResourceManager::getImage(Component::types::vccs),Component::vccs),2,2);
    toolboxLayout->addWidget(createCellWidget(tr("ccvs"),ResourceManager::getImage(Component::types::ccvs),Component::ccvs),0,3);
    toolboxLayout->addWidget(createCellWidget(tr("cccs"),ResourceManager::getImage(Component::types::cccs),Component::cccs),1,3);
}

void MainWindow::drawCircuits(QString text) {

    if(text=="Parallel Circuit"){

        scene->getCircuit()->clear();

        auto res=new Resistor(10);
        auto n1=new Node(400,160);
        auto n2=new Node(400,60);
        scene->getCircuit()->add(res,n1,n2);

        auto w1= new Wire;
        auto n3=new Node(300,60);
        scene->getCircuit()->add(w1,n2,n3);

        auto w2= new Wire;
        auto n4=new Node(300,160);
        scene->getCircuit()->add(w2,n1,n4);

        auto w3=new Wire;
        scene->getCircuit()->add(w3,n4,n3);

        auto w4=new Wire;
        auto n5=new Node(200,160);
        scene->getCircuit()->add(w4,n4,n5);

        auto w5= new Wire;
        auto n6=new Node(200,60);
        scene->getCircuit()->add(w5,n3,n6);

        auto vol= new VoltageSource(10);
        scene->getCircuit()->add(vol,n5,n6);
        //n3->setGnd(true);


    }
    else if(text==tr("Voltage Divider")){

        scene->getCircuit()->clear();

        auto res1=new Resistor(10);
        auto n1=new Node(400,160);
        auto n2=new Node(400,60);
        scene->getCircuit()->add(res1,n1,n2);

        auto res2= new Resistor(10);
        auto n3=new Node(300,60);
        scene->getCircuit()->add(res2,n2,n3);

        auto res3= new Resistor(10);
        auto n4=new Node(300,160);
        scene->getCircuit()->add(res3,n1,n4);

        auto res4=new Resistor(10);
        auto n5=new Node(200,160);
        scene->getCircuit()->add(res4,n4,n5);

        auto res5= new Resistor(10);
        auto n6=new Node(200,60);
        scene->getCircuit()->add(res5,n3,n6);

        auto vol= new VoltageSource(10);
        scene->getCircuit()->add(vol,n5,n6);


    }

    else if(text=="Current Divider"){

        scene->getCircuit()->clear();

        auto res1=new Resistor(10);
        auto n1=new Node(400,160);
        auto n2=new Node(400,60);
        scene->getCircuit()->add(res1,n1,n2);

        auto w1= new Wire;
        auto n3=new Node(300,60);
        scene->getCircuit()->add(w1,n2,n3);

        auto w2= new Wire;
        auto n4=new Node(300,160);
        scene->getCircuit()->add(w2,n1,n4);

        auto res2=new Resistor(10);
        scene->getCircuit()->add(res2,n4,n3);

        auto w4=new Wire;
        auto n5=new Node(200,160);
        scene->getCircuit()->add(w4,n4,n5);

        auto w5= new Wire;
        auto n6=new Node(200,60);
        scene->getCircuit()->add(w5,n3,n6);

        auto curr= new CurrentSource(10);
        scene->getCircuit()->add(curr,n5,n6);


    }

    else if(text=="Strange One"){

        scene->getCircuit()->clear();

        auto vol1=new VoltageSource(10);
        auto n1=new Node(400,200);
        auto n2=new Node(400,50);
        scene->getCircuit()->add(vol1,n1,n2);

        auto res1= new Resistor(10);
        auto n3=new Node(250,50);
        scene->getCircuit()->add(res1,n2,n3);

        auto res2= new Resistor(10);
        auto n4=new Node(250,200);
        scene->getCircuit()->add(res2,n1,n4);

        auto vol2=new VoltageSource(10);
        scene->getCircuit()->add(vol2,n4,n3);

        auto res3= new Resistor(10);
        scene->getCircuit()->add(res3,n2,n4);


    }

    else if(text=="Controlled One"){

        scene->getCircuit()->clear();

        auto res1=new Resistor(10);
        auto n2= new Node(300,160);
        auto n7=new Node(300,60);
        scene->getCircuit()->add(res1,n2,n7);

        auto wir1=new Wire;
        auto n1=new Node(400,160);
        scene->getCircuit()->add(wir1,n2,n1);

        auto vcvs=new VCVS(10,res1);
        auto n8=new Node(400,60);
        scene->getCircuit()->add(vcvs,n1,n8);

        auto wir2=new Wire;
        scene->getCircuit()->add(wir2,n8,n7);

        auto wir4=new Wire;
        auto n5=new Node(100,60);
        scene->getCircuit()->add(wir4,n7,n5);

        auto wir5=new Wire;
        auto n4=new Node(100,160);
        scene->getCircuit()->add(wir5,n2,n4);

        auto curr=new CurrentSource(10);
        scene->getCircuit()->add(curr,n4,n5);

    }

    else if(text=="Trasformatore"){

        //rapporto di 2
        scene->getCircuit()->clear();

        auto vol=new VoltageSource(10);
        auto n1=new Node(500,200);
        auto n2=new Node(500,100);
        scene->getCircuit()->add(vol,n1,n2);

        auto res1=new Resistor(10);
        auto n3=new Node(400,200);
        scene->getCircuit()->add(res1,n1,n3);

        auto w1=new Wire;
        auto n4=new Node(400,100);
        scene->getCircuit()->add(w1,n2,n4);

        auto w2=new Wire;
        auto n6= new Node(300,100);
        scene->getCircuit()->add(w2,n4,n6);

        auto n8=new Node(200,100);
        auto n7=new Node(200,200);


        auto n5=new Node(300,200);
        auto w3=new Wire;
        scene->getCircuit()->add(w3,n5,n7);

        auto w4=new Wire;
        scene->getCircuit()->add(w4,n6,n8);

        auto cccs=new CCCS(2,w3);
        w3->setControlled();
        scene->getCircuit()->add(cccs,n3,n4);

        auto vcvs= new VCVS(2,cccs);
        cccs->setControlled();
        scene->getCircuit()->add(vcvs,n6,n5);

        auto w5=new Wire;
        auto n9=new Node(100,200);
        scene->getCircuit()->add(w5,n9,n7);

        auto w6=new Wire;
        auto n10=new Node(100,100);
        scene->getCircuit()->add(w6,n10,n8);

        auto curr=new CurrentSource(10);
        scene->getCircuit()->add(curr,n9,n10);


    }

}