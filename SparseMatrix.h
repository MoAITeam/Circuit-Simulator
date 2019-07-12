//
// Created by Sierra on 2019-07-06.
//

#ifndef FIRSTSIMULATORTEST_SPARSEMATRIX_H
#define FIRSTSIMULATORTEST_SPARSEMATRIX_H

#include "EigenInterface.h"
#include "Node.h"
#include <memory>

class SparseMatrix: public EigenInterface{
public:
    SparseMatrix();
    ~SparseMatrix();
    void add();
    void add(Component* c,int a, int b);
    void add(Component* c,int a);
    void add(Component* c);
    void removeNode(int i);
    void removeComponent(int i);
    void update(int i,int a, int b);
    void update(int i,int a);
    void update(int i);
    void print();
    std::vector<float> solve();

private:
    int components;
    EigenInterface* terms;
};


#endif //FIRSTSIMULATORTEST_SPARSEMATRIX_H
