//
// Created by Sierra on 2019-07-28.
//

#ifndef FIRSTSIMULATORTEST_VCVS_H
#define FIRSTSIMULATORTEST_VCVS_H

#include "ActiveComponent.h"

class VCVS : public ActiveComponent{
public:
    VCVS(float value,Component *d= nullptr);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
    void setValue(float value) override{
        behavior[0]=1/value;
        this->value=value;
    }
    std::string getData() override{
        return std::to_string(myType)+"/"+label.toStdString()+"/"+std::to_string(value)+"/"+std::to_string(nodes.first->x())+"/"+std::to_string(nodes.first->y())+"/"+std::to_string(nodes.second->x())+"/"+std::to_string(nodes.second->y())+"/"+controller->getLabel().toStdString()+"/";
    }
};


#endif //FIRSTSIMULATORTEST_VCVS_H