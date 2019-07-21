
//
// Created by cipher on 18/07/19.
//


#include "CircuitScene.h"

#include <QtWidgets>



class MainWindow: public QMainWindow{

    Q_OBJECT

public:
    MainWindow(CircuitScene *scene);
private:
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolbars();

    void deleteItems();

    QWidget *createCellWidget(const QString &text,const QString &image);
    QGraphicsScene *scene;


    QToolBar *editToolBar;
    QToolBar *pointerToolbar;


    QMenu *fileMenu;
    QMenu *itemMenu;

    QAction *deleteAction;
    QAction *exitAction;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;

};