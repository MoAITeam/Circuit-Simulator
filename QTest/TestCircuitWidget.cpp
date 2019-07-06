//
// Created by Sierra on 2019-07-01.
//

#include "TestCircuitWidget.h"
#include "../CircuitWidget.h"

QTEST_MAIN(TestCircuitWidget)

void TestCircuitWidget::testAddItem() {

    Circuit* circuit= new Circuit;
    CircuitWidget* widget=new CircuitWidget(circuit);
    auto c = new Component(5);
    circuit->add(c, 50, 50, 100,100);
    QVERIFY(c->getNodes().first->x()==50 && c->getNodes().first->y()==50 && c->getNodes().second->x()==100 && c->getNodes().second->y()==100);
    bool found=false;
    for (auto item : widget->scene()->items()){
        if (item==c) {
            if (found==false)
            found=true;
            else
                found=false; //duplicated
        }
    }
    QVERIFY(found);

}

void TestCircuitWidget::removeRandomComponent() {

    auto circuit=new Circuit;
    auto widget= new CircuitWidget(circuit);
   auto c= new Component(10);
   circuit->add(c,50,50,100,100);
   QTest::mouseDClick(widget,Qt::LeftButton,Qt::NoModifier,QPoint(100,100));
   bool status =false;
   for(auto item : widget->scene()->items()){
       if(item!= nullptr)
           status=true;
   }
QVERIFY(status==false);
}
