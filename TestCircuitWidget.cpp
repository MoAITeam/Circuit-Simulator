//
// Created by Sierra on 2019-07-01.
//

#include "TestCircuitWidget.h"

QTEST_MAIN(TestCircuitWidget)

void TestCircuitWidget::testAddItem() {
    Circuit* circuit= new Circuit;
    auto *c = new Component(5);
    circuit->add(c, 50, 50, 100,100);
    QVERIFY(c->getNode(1)->x()==50 && c->getNode(1)->y()==50 && c->getNode(2)->x()==100 && c->getNode(2)->y()==100);
}