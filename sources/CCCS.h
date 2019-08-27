//
// Created by Sierra on 2019-07-29.
//

#ifndef FIRSTSIMULATORTEST_CCCS_H
#define FIRSTSIMULATORTEST_CCCS_H


#include "ActiveComponent.h"

class CCCS : public ActiveComponent{
public:
    CCCS(float value,Component *d= nullptr);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
    void setValue(float value) override{
        behavior[1]=1/value;
        this->value=value;
    }
    std::string getData() override{
        return std::to_string(myType)+"/"+label.toStdString()+"/"+std::to_string(value)+"/"+std::to_string(nodes.first->x())+"/"+std::to_string(nodes.first->y())+"/"+std::to_string(nodes.second->x())+"/"+std::to_string(nodes.second->y())+"/"+controller->getLabel().toStdString()+"/";
    }
};



#endif //FIRSTSIMULATORTEST_CCCS_H