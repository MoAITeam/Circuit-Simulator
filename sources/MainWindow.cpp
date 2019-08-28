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
#include "SparseMatrix.h"
#include "FileManager.h"
#include "ComponentData.h"

#include <QtWidgets>
#include <iostream>
#include <QFrame>


MainWindow::MainWindow(CircuitScene *scene) {

    this->scene=scene;

    componentsToolboxLayout= new QGridLayout;
    samplesLayout= new QGridLayout;
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

    connect(scene,SIGNAL(insertValue(ActiveComponent*)),this,SLOT(showValueDialog(ActiveComponent * )));
    connect(view->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(handleScroll()));
    connect(view->horizontalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(handleScroll()));
    connect(scene,SIGNAL(insertName(ActiveComponent*)),this,SLOT(showNameDialog(ActiveComponent * )));
    connect(scene,SIGNAL(insertedComponent()),this,SLOT (addedComponent()));



}

void MainWindow::handleScroll() {   //handle scrolling graphic
    scene->display=QPointF(view->horizontalScrollBar()->value(),view->verticalScrollBar()->value());
}

void MainWindow::showValueDialog(ActiveComponent *c){  //allows component's value changing
    std::string text = "Value in ";
    QString string = QString::fromStdString(text);
    QString unit= "Unit";
    float oldVal=0;
    if(c!= nullptr) {
        oldVal = c->getValue();
        unit=c->getUnit();
    }
    float value = QInputDialog::getDouble(this->parentWidget(), "Dialog", string+unit,oldVal);
    scene->setcValue(value);
}

void MainWindow::showNameDialog(ActiveComponent *c) {   //allows component's name changing

    std::string text = "Name ";
    QString string = QString::fromStdString(text);
    QString oldName="";
    if(c!= nullptr)
        oldName = c->getLabel();

    QString name = QInputDialog::getText(this->parentWidget(), "Dialog", string,QLineEdit::Normal,oldName);
    scene->setcName(name);
}

void MainWindow::addedComponent() {

    componentsButtonGroup->setExclusive(false);
    componentsButtonGroup->checkedButton()->setChecked(false);
    componentsButtonGroup->setExclusive(true);


}

void MainWindow::createToolBox() {

    samplesButtonGroup= new QButtonGroup(this);
    samplesButtonGroup->setExclusive(false);
    connect(samplesButtonGroup,QOverload<QAbstractButton *>::of((&QButtonGroup::buttonClicked)),this,
            &MainWindow::samplesButtonGroupClicked);

    componentsButtonGroup = new QButtonGroup(this);
    componentsButtonGroup->setExclusive(true);
    connect(componentsButtonGroup,QOverload<int>::of((&QButtonGroup::buttonClicked)),this,
            &MainWindow::componentsButtonGroupClicked);

    fillComponentsToolbox();
    fillSamplesToolbox();

    auto componentsFrameWidget= new QFrame;
    componentsFrameWidget->setLayout(componentsToolboxLayout);
    componentsFrameWidget->setFrameShape(QFrame::Box);
    componentsFrameWidget->setStyleSheet("background-color:whitesmoke;");

    auto samplesFrameWidget=new QFrame;
    samplesFrameWidget->setLayout(samplesLayout);
    samplesFrameWidget->setFrameShape(QFrame::Box);
    samplesFrameWidget->setStyleSheet("background-color:whitesmoke;");

    toolBox=new QToolBox;
    toolBox->setMinimumWidth(222);
    toolBox->setMaximumWidth(222);
    toolBox->addItem(componentsFrameWidget,tr("Electric Components"));
    toolBox->addItem(samplesFrameWidget,tr("Sample Circuit"));

}

void MainWindow::createActions() {  //buttons and menus action

    QIcon icon_delete = QIcon(":/images/delete.png");
    deleteAction = new QAction(icon_delete, tr("&Delete"), this);
    deleteAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteItems);

    QIcon icon_select = QIcon(":/images/pointer.png");
    selectAction = new QAction(icon_select, tr("&Select"), this);
    connect(selectAction, &QAction::triggered, this, &MainWindow::selectItems);

    QIcon icon_exit = QIcon(":/images/delete.png");
    exitAction = new QAction(icon_exit, tr("&Exit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit example"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("F1"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    QIcon icon_run = QIcon(":/images/play.png");
    runCircuitAction = new QAction(icon_run, tr("&Run"), this);
    runCircuitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    connect(runCircuitAction, &QAction::triggered, this, &MainWindow::runCircuit);

    QIcon icon_clear = QIcon(":/images/clear.png");
    clearAction = new QAction(icon_clear, tr("&Clear"), this);
    clearAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    connect(clearAction, &QAction::triggered, this, &MainWindow::clearAll);

    QIcon icon_selAll = QIcon(":/images/selectall");
    selectAllAction = new QAction(icon_selAll, tr("&Select All"), this);
    selectAllAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    connect(selectAllAction, &QAction::triggered, this, &MainWindow::selectAll);

    QIcon icon_export = QIcon(":/images/export.png");
    exportAction = new QAction(icon_export, tr("&Export"), this);
    exportAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    connect(exportAction, &QAction::triggered, this, &MainWindow::exportImage);

    QIcon icon_showMatrix = QIcon(":/images/matrix.png");
    showMatrixAction = new QAction(icon_showMatrix, tr("&Show Matrix"), this);
    showMatrixAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    connect(showMatrixAction, &QAction::triggered, this, &MainWindow::showMatrix);

    QIcon icon_save=QIcon(":/images/save.png");
    saveAction = new QAction(icon_save,tr("&Save"), this);
    saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    QIcon icon_load=QIcon(":/images/load.png");
    loadAction = new QAction(icon_load,tr("&Load"), this);
    loadAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
    connect(loadAction, &QAction::triggered, this, &MainWindow::load);

}

void MainWindow::save() {
    QString dir = QFileDialog::getSaveFileName(this, tr("Open File"),"/");
    if(!dir.isNull()) {
        FileManager file(dir.toStdString());       //handle dir thanks to filemanager
        std::string data= scene->getCircuitData();
        file.write(data);
    }
}

void MainWindow::load() {
    QString dir = QFileDialog::getOpenFileName(this, tr("Save File"),"/circuit.txt",tr("Circuit Files (*.txt)"));
    if(!dir.isNull()) {
        FileManager file(dir.toStdString());
        std::vector<ComponentData> data=file.read();
        scene->loadCircuitData(data);
    }
}


void MainWindow::createToolbars() {

    editToolBar = addToolBar(tr("Edit"));

    editToolBar->addAction(deleteAction);
    editToolBar->addAction(selectAction);
    editToolBar->addAction(runCircuitAction);
    editToolBar->addAction(clearAction);
    editToolBar->addAction(selectAllAction);
    editToolBar->addAction(exportAction);
    editToolBar->addAction(showMatrixAction);

    viewToolBar= addToolBar(tr("View"));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),this, &MainWindow::sceneScaleChanged);

    viewToolBar->addWidget(sceneScaleCombo);

}


QWidget* MainWindow::createCellWidget(const QString &text, const QPixmap &image, int id, QButtonGroup* buttonGroup ) {   //square button inside the toolbox

    auto *button= new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(45,45));
    button->setCheckable(true);
    buttonGroup->addButton(button,Qt::NoModifier);
    buttonGroup->setId(button,id);
    button->setStyleSheet("background-color:gainsboro;");

    auto *layout= new QGridLayout;
    layout->addWidget(button,0,0,Qt::AlignCenter);
    layout->addWidget(new QLabel(text),1,0,Qt::AlignCenter);
    layout->setMargin(0);

    auto *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

void MainWindow::createMenus() {   //vertical menu

    fileMenu=menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(loadAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exportAction);
    fileMenu->addAction(exitAction);

    itemMenu= menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addAction(clearAction);
    itemMenu->addAction(selectAllAction);
    itemMenu->addAction(runCircuitAction);
    itemMenu->addAction(showMatrixAction);

    aboutMenu= menuBar()->addMenu(tr("&About"));
    aboutMenu->addAction(aboutAction);
}


void MainWindow::componentsButtonGroupClicked(int type) {

    scene->resetExSel();   //reset focus
    componentsToolboxLayout->update();
    samplesLayout->update();

    scene->setType(Component::types(type));
    if(type>=Component::vcvs)
        scene->setMode(CircuitScene::selectDependent);
    else
        scene->setMode(CircuitScene::insertItem);

}


void MainWindow::samplesButtonGroupClicked(QAbstractButton *button) {

    const QList<QAbstractButton *> buttons = samplesButtonGroup->buttons();      //metodo per cliccare sui bottoni del backgrnd
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

void MainWindow::sceneScaleChanged(const QString &scale)  //mofifies zoom on window
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::runCircuit() {

    scene->getCircuit()->solve();
    scene->update();

}

void MainWindow::showMatrix() {  //it opens a dialog in which show the circuit's matrix,then you can solve it from the dialog too

    QMessageBox mat;

    if(scene->items().size()!=0){
        DynamicMatrix print(scene->getCircuit()->getMatrix()->rows(),scene->getCircuit()->getMatrix()->cols()+1);
        print<<scene->getCircuit()->getMatrix()->matrix(),*(scene->getCircuit()->getMatrix()->getTerms());
    QString matrix="";
    for(int i=0;i<scene->getCircuit()->getMatrix()->rows();i++){
        for(int j=0;j<scene->getCircuit()->getMatrix()->cols()+1;j++){
                float val=(print)(i, j);
                matrix=matrix + "  " +  QString::number(val)+" ";
        }
        matrix=matrix+"\n";

    }

    QMessageBox mat;
    mat.setWindowTitle("Show Matrix");
    mat.setText("Here is the <b>matrix</b>:");
    mat.setInformativeText(matrix);
    QIcon icon(":/images/play.png");
    QPushButton *play_Button=mat.addButton("Run Circuit",QMessageBox::ActionRole);
    play_Button->setIcon(icon);
    connect(play_Button,&QPushButton::pressed,this,&MainWindow::runCircuit);
    play_Button->addAction(runCircuitAction);
    mat.addButton(QMessageBox::Ok);
    mat.setDefaultButton(QMessageBox::Ok);
    mat.exec();

    }
    else{
        mat.setText("No <b>matrix</b> due to components absence");
        mat.setWindowTitle("Show Matrix");
        mat.exec();
    }

}

void MainWindow::clearAll() {

    scene->getCircuit()->clear();

}

void MainWindow::selectAll() {
    for(auto &item : scene->items())
        if (item->type()>=Component::component)
            item->setSelected(true);
}

void MainWindow::exportImage() {  //create a png file in cmake-build-debug directory
    QMessageBox exp;
    if(scene->items().size()!=0) {
        scene->clearSelection();
        QRectF getRect = scene->sceneRect();
        scene->setSceneRect(scene->itemsBoundingRect());
        QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
        image.fill(Qt::transparent);
        QPainter painter(&image);
        scene->render(&painter);
        image.save("circuit.png");
        scene->setSceneRect(getRect);
        exp.setWindowTitle("Export Successful");
        exp.setText("Your circuit has been exported");
    }
    else {

        exp.setWindowTitle("Export not possible");
        exp.setText("<b>Export</b> is not possible,try creating a circuit");

    }
    exp.exec();
}

void MainWindow::deleteItems() {
    for(auto &item : scene->items())
        if(item->isSelected())
            if(item->type()>=Component::component)
                delete item;
}

void MainWindow::selectItems() {
    scene->setMode(CircuitScene::moveItem);
}

void MainWindow::fillComponentsToolbox(){
    auto verticalSpacer=new QSpacerItem(0,1000,QSizePolicy::Expanding,QSizePolicy::Expanding);
    componentsToolboxLayout->addWidget(createCellWidget(tr("Resistor"),ResourceManager::getImage(Component::types::resistor),Component::resistor,componentsButtonGroup),0,0);
    componentsToolboxLayout->addWidget(createCellWidget(tr("Voltage Source"),ResourceManager::getImage(Component::types::voltageSource),Component::voltageSource,componentsButtonGroup),0,1);
    componentsToolboxLayout->addWidget(createCellWidget(tr("Current Source"),ResourceManager::getImage(Component::types::currentSource),Component::currentSource,componentsButtonGroup),1,0);
    componentsToolboxLayout->addWidget(createCellWidget(tr("Wire"),ResourceManager::getImage(Component::types::wire),Component::wire,componentsButtonGroup),1,1);
    componentsToolboxLayout->addWidget(createCellWidget(tr("Amperometer"),ResourceManager::getImage(Component::types::voltmeter),Component::amperometer,componentsButtonGroup),2,0);
    componentsToolboxLayout->addWidget(createCellWidget(tr("Voltmeter"),ResourceManager::getImage(Component::types::voltmeter),Component::voltmeter,componentsButtonGroup),2,1);
    componentsToolboxLayout->addWidget(createCellWidget(tr("Ground"),ResourceManager::getImage(Component::types::ground),Component::ground,componentsButtonGroup),3,0);
    componentsToolboxLayout->addWidget(createCellWidget(tr("VCVS"),ResourceManager::getImage(Component::types::vcvs),Component::vcvs,componentsButtonGroup),3,1);
    componentsToolboxLayout->addWidget(createCellWidget(tr("VCCS"),ResourceManager::getImage(Component::types::vccs),Component::vccs,componentsButtonGroup),4,0);
    componentsToolboxLayout->addWidget(createCellWidget(tr("CCVS"),ResourceManager::getImage(Component::types::ccvs),Component::ccvs,componentsButtonGroup),4,1);
    componentsToolboxLayout->addWidget(createCellWidget(tr("CCCS"),ResourceManager::getImage(Component::types::cccs),Component::cccs,componentsButtonGroup),5,0);
    componentsToolboxLayout->addItem(verticalSpacer,6,0);
}

void MainWindow::fillSamplesToolbox(){
    auto verticalSpacer=new QSpacerItem(0,1000,QSizePolicy::Expanding,QSizePolicy::Expanding);
    samplesLayout->addWidget(createCellWidget("Parallel Circuit",QPixmap(":/images/parallelcircuit.png"),samples::parallelCircuit,samplesButtonGroup),0,0);
    samplesLayout->addWidget(createCellWidget("Voltage Divider",QPixmap(":/images/voltagedivider.png"),samples::voltageDivider,samplesButtonGroup),0,1);
    samplesLayout->addWidget(createCellWidget("Current Divider",QPixmap(":/images/currentdivider.png"),samples::currentDivider,samplesButtonGroup),1,1);
    samplesLayout->addWidget(createCellWidget("Strange One",QPixmap(":/images/strangeone.png"),samples::strangeOne,samplesButtonGroup),1,0);
    samplesLayout->addWidget(createCellWidget("Controlled One",QPixmap(":/images/controlled.png"),samples::controlledOne,samplesButtonGroup),2,0);
    samplesLayout->addWidget(createCellWidget("Trasformatore",QPixmap(":/images/trasformatore.png"),samples::trasformatore,samplesButtonGroup),2,1);
    samplesLayout->addItem(verticalSpacer,3,0);
}


//getter


QAction* MainWindow::getDeleteAction(){
    return deleteAction;
}

QAction* MainWindow::getSelectAllAction(){
    return selectAllAction;
}

QAction* MainWindow::getClearAction(){
    return clearAction;
}

QAction *MainWindow::getRunCircuitAction() const {
    return runCircuitAction;
}

QAction *MainWindow::getSelectAction() const {
    return selectAction;
}
