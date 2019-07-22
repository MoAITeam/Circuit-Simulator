
//
// Created by cipher on 18/07/19.
//


#include "CircuitScene.h"

#include <QtWidgets>



class MainWindow: public QMainWindow{

    Q_OBJECT

public:
    MainWindow(CircuitScene *scene);
    enum types {Resistor, CurrentSource, VoltageSource};
private:
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolbars();
    void keyPressEvent(QKeyEvent *event) override;

    void deleteItems();

    QWidget *createCellWidget(const QString &text,const QString &image, int id);
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