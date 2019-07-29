//
// Created by Sierra on 2019-07-13.
//

#ifndef FIRSTSIMULATORTEST_MATRIXEXCEPTION_H
#define FIRSTSIMULATORTEST_MATRIXEXCEPTION_H

#include <exception>
class MatrixException: public std::exception{
public:
    MatrixException(std::string s):spec(s){};
    const char* what() const throw() override{
        std::string except="Matrix Exception: "+spec;
        return except.c_str();
    };
private:
    std::string spec;
};

#endif //FIRSTSIMULATORTEST_MATRIXEXCEPTION_H