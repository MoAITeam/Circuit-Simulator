
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

    void buttonGroupClicked(int type);
    void sceneScaleChanged(const QString &scale);

    void deleteItems();
    void selectItems();
    void runCircuit();

    void about();

    QWidget *createCellWidget(const QString &text,const QString &image, int id);
    CircuitScene *scene;
    QGraphicsView *view;

    QToolBar *editToolBar;
    QToolBar *viewToolBar;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

    QComboBox *sceneScaleCombo;

    QAction *deleteAction;
    QAction *selectAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *runCircuitAction;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;

};