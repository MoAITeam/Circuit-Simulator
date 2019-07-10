//
// Created by Sierra on 2019-07-06.
//

#ifndef FIRSTSIMULATORTEST_SPARSEMATRIX_H
#define FIRSTSIMULATORTEST_SPARSEMATRIX_H

#include "EigenInterface.h"
#include "Node.h"

class SparseMatrix: public EigenInterface{
public:
    SparseMatrix();
    ~SparseMatrix();
    void add();
    void add(Component* c,int a, int b);
    void removeNode(int i);
    void removeComponent(int i);
    void update(int i,int a, int b);
    void print();

private:
    int components;
    EigenInterface* terms;
};


#endif //FIRSTSIMULATORTEST_SPARSEMATRIX_H
