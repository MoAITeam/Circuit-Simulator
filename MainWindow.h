
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

    void deleteItems();
    void selectItems();

    QWidget *createCellWidget(const QString &text,const QString &image, int id);
    CircuitScene *scene;

    QToolBar *editToolBar;

    QMenu *fileMenu;
    QMenu *itemMenu;

    QAction *deleteAction;
    QAction *selectAction;
    QAction *exitAction;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;

};