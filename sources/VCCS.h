//
// Created by Sierra on 2019-07-29.
//

#ifndef FIRSTSIMULATORTEST_VCCS_H
#define FIRSTSIMULATORTEST_VCCS_H

#include "ActiveComponent.h"

class VCCS : public ActiveComponent{
public:
    VCCS(float value,Component *d= nullptr);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
    void setValue(float value) override{
        behavior[1]=1/value;
        this->value=value;
    }
    std::string getData() override{
        return std::to_string(myType)+"/"+label.toStdString()+"/"+std::to_string(value)+"/"+std::to_string(nodes.first->x())+"/"+std::to_string(nodes.first->y())+"/"+std::to_string(nodes.second->x())+"/"+std::to_string(nodes.second->y())+"/"+controller->getLabel().toStdString()+"/";
    }
};



#endif //FIRSTSIMULATORTEST_VCCS_H