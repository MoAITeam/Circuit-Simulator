//
// Created by Sierra on 2019-07-06.
//

#include "SparseMatrix.h"
#include <iostream>

SparseMatrix::SparseMatrix(): CompsIndex(0) {
    m=new MyMatrix();
}

void SparseMatrix::add(Node *n) {
    m->addRow();
    m->addCol();
    std::cout<<*m<<std::endl;
}

void SparseMatrix::remove(Node *n, std::list<Node*> v){
    int i=0;
    for (auto &node:v) {
        if (node == n) {
            m->removeRow(CompsIndex + i);
            m->removeColumn(CompsIndex + i);
        }
        i++;
    }
    std::cout<<*m<<std::endl;
}