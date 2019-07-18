
//
// Created by cipher on 18/07/19.
//

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QAction>
#include "CircuitWidget.h"



class MainWindow: public QMainWindow{

    Q_OBJECT

public:
    MainWindow(CircuitWidget *view);
private:
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolbars();



    QToolBar *editToolBar;


    QAction *deleteAction;
    QToolBox *toolBox;
    QButtonGroup *buttonGroup;

};