//
// Created by Sierra on 2019-07-01.
//

#ifndef FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_H
#define FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_H

#include <QtTest/QtTest>
#include <iostream>


class TestCircuitWidget: public QObject {
Q_OBJECT
public:
    void testAddItem();
    void removeRandomComponent();
    void createAndRemoveOrsaMaggiore(); //TODO
};



#endif //FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_H CIRCUITWIDGET_H