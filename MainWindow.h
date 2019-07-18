
//
// Created by cipher on 18/07/19.
//

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QButtonGroup>
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


    QGraphicsScene *scene;
    QGraphicsView *view;

    QAction *exitAction;
    //QAction *addAction;
    QAction *deleteAction;



    QMenu *fileMenu;
    QMenu *itemMenu;

    QToolBar *editToolBar;
    QToolBar *pointerToolbar;

    QComboBox *sceneScaleCombo;


    QToolBox *toolBox;
    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *backgroundButtonGroup;

};