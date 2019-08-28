//
// Created by Sierra on 2019-07-13.
//

#ifndef FIRSTSIMULATORTEST_MODELEXCEPTION_H
#define FIRSTSIMULATORTEST_MODELEXCEPTION_H

#include <exception>

//handle errors associated to model's problem
class ModelException: public std::exception {
public:
    ModelException(std::string s):spec(s){};
    const char* what() const throw() override{
        std::string except="Model Exception: "+spec;
        return except.c_str();
    }
private:
    std::string spec;
};


#endif //FIRSTSIMULATORTEST_MODELEXCEPTION_H
