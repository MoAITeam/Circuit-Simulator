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
    void add(Component* c,int a, Node* p, int b, Node* n);
    void removeNode(int i);
    void removeComponent(int i);
    void update(int i,int a, Node* p, int b, Node* n);
    void print();
    std::vector<float> solve();

private:
    int components;
    EigenInterface* terms;
};


#endif //FIRSTSIMULATORTEST_SPARSEMATRIX_H
