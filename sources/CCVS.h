//
// Created by Sierra on 2019-07-29.
//

#ifndef FIRSTSIMULATORTEST_CCVS_H
#define FIRSTSIMULATORTEST_CCVS_H


#include "ActiveComponent.h"

class CCVS : public ActiveComponent{
public:
    CCVS(float value,Component *d= nullptr);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override final;
    void setValue(float value) override{
        behavior[0]=1/value;
        this->value=value;
    }
    std::string getData() override{
        return std::to_string(myType)+"/"+label.toStdString()+"/"+std::to_string(value)+"/"+std::to_string(nodes.first->x())+"/"+std::to_string(nodes.first->y())+"/"+std::to_string(nodes.second->x())+"/"+std::to_string(nodes.second->y())+"/"+controller->getLabel().toStdString()+"/";
    }
};



#endif //FIRSTSIMULATORTEST_CCVS_H