//
// Created by Sierra on 2019-07-06.
//

#include "SparseMatrix.h"
#include "Component.h"
#include <iostream>

SparseMatrix::SparseMatrix(): CompsIndex(0) {
    m=new MyMatrix();
    terms=new MyMatrix();
    terms->resize(0,1);
}

void SparseMatrix::add(Node *n) {
    m->addRow();
    m->addCol();
    terms->addRow();
}

void SparseMatrix::add(Component *c,std::list<Node*> v) {
    m->ROWinsertBetweenNthAndNthplusOne(0);
    m->COLinsertBetweenNthAndNthplusOne(0);
    terms->ROWinsertBetweenNthAndNthplusOne(0);
    (*m)(0,0)=1;
    (*terms)(0,0)=0;
    m->ROWinsertBetweenNthAndNthplusOne(CompsIndex+1);
    m->COLinsertBetweenNthAndNthplusOne(CompsIndex+1);
    terms->ROWinsertBetweenNthAndNthplusOne(CompsIndex+1);
    (*m)(CompsIndex+1,0)=c->behavior[0];
    (*m)(CompsIndex+1,CompsIndex+1)=c->behavior[1];
    (*terms)(CompsIndex+1)=c->behavior[2];
    CompsIndex++;
    int i=0;
    for (auto &node:v) {
        if (node == c->getNodes().first || node==c->getNodes().second) {
            (*m)(0,CompsIndex*2+i)=-1;
            (*m)(2*CompsIndex+i,CompsIndex)=1;
        }
        i++;
    }
    std::cout<<(*m)<<"\n*[x]=\n"<<(*terms)<<std::endl;
}

void SparseMatrix::remove(Node *n, std::list<Node*> v){
    int i=0;
    for (auto &node:v) {
        if (node == n) {
            m->removeRow(2*CompsIndex + i);
            m->removeColumn(2*CompsIndex + i);
        }
        i++;
    }
    std::cout<<*m<<std::endl;
}