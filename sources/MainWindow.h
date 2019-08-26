//
// Created by cipher on 18/07/19.
//


#include "CircuitScene.h"

#include <QtWidgets>



class MainWindow: public QMainWindow{

Q_OBJECT
public:
    QAction *getSelectAction() const;

public:
    enum samples {parallelCircuit, voltageDivider, currentDivider, strangeOne, controlledOne, trasformatore};
    MainWindow(CircuitScene *scene);
public slots:
    void showValueDialog(ActiveComponent *c);
    void showNameDialog(ActiveComponent* c);
    void handleScroll();
    QAction* getDeleteAction();
    QAction* getClearAction();
    QAction* getSelectAllAction();
    QAction *getRunCircuitAction() const;

private:
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolbars();

    void componentsButtonGroupClicked(int type);
    void samplesButtonGroupClicked(QAbstractButton *button);

    void sceneScaleChanged(const QString &scale);

    void selectItems();
    void deleteItems();
    void runCircuit();
    void fillComponentsToolbox();
    void fillSamplesToolbox();
    void drawCircuits(QString text);
    void clearAll();
    void selectAll();
    void exportImage();
    void about();

    static QWidget *createCellWidget(const QString &text,const QPixmap &image, int id, QButtonGroup*);

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
    QAction *clearAction;
    QAction *selectAllAction;
    QAction *exportAction;

    QToolBox *toolBox;
    QButtonGroup *componentsButtonGroup;
    QButtonGroup *samplesButtonGroup;
    QGridLayout *componentsToolboxLayout;
    QGridLayout *samplesLayout;
};