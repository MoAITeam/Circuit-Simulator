//
// Created by Sierra on 2019-07-06.
//

#ifndef FIRSTSIMULATORTEST_SPARSEMATRIX_H
#define FIRSTSIMULATORTEST_SPARSEMATRIX_H

#include "EigenInterface.h"
#include <memory>
#include <vector>

#define notFound -1

class SparseMatrix: public EigenInterface{
public:
    SparseMatrix();
    ~SparseMatrix();
    void add();
    void add(const float behavior[3],int a,int b);
    void add(const float behavior[3],int d,int s,int a,int b);
    void removeNode(int i);
    void removeComponent(int i);
    void update(int i,int a,int b);
    void update(int i, const float behavior[3]);
    void print();
    std::vector<float> solve();

private:
    int components;
    EigenInterface* terms;
};


#endif //FIRSTSIMULATORTEST_SPARSEMATRIX_H
