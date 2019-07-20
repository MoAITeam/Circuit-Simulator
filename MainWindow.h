
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
    QWidget *createCellWidget(const QString &text,const QString &image);




    QToolBar *editToolBar;
    QToolBar *pointerToolbar;


    QMenu *fileMenu;
    QMenu *itemMenu;

    QComboBox *sceneScaleCombo;

    QAction *deleteAction;
    QAction *exitAction;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;

};