//
// Created by Sierra on 2019-07-01.
//

#ifndef FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_H
#define FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_H

#include <QtTest/QtTest>
#include <iostream>
#include "CircuitWidget.h"

class TestCircuitWidget: public QObject {
Q_OBJECT
    void testAddItem();
    void removeRandomComponent(); //TODO
};


#endif //FIRSTSIMULATORTEST_TESTCIRCUITWIDGET_H