//
// Created by Sierra on 2019-07-06.
//

#include "SparseMatrix.h"
#include "Component.h"
#include <iostream>

SparseMatrix::SparseMatrix(): CompsIndex(0) {
    terms=new MyMatrix();
    terms->resize(0,1);
}

void SparseMatrix::add() {
    addRow();
    addCol();
    terms->addRow();
}

void SparseMatrix::add(Component *c,int a, int b) {
    insertRow(0);
    insertCol(0);
    terms->insertRow(0);
    matrix()(0,0)=1;
    (*terms)(0,0)=0;

    insertRow(CompsIndex + 1);
    insertCol(CompsIndex + 1);
    terms->insertRow(CompsIndex + 1);
    matrix()(CompsIndex+1,0)=c->behavior[0];
    matrix()(CompsIndex+1,CompsIndex+1)=c->behavior[1];
    (*terms)(CompsIndex+1)=c->behavior[2];

    CompsIndex++;

    matrix()(0,CompsIndex*2+a)=1;
    matrix()(2*CompsIndex+a,CompsIndex)=1;
    matrix()(0,CompsIndex*2+b)=1;
    matrix()(2*CompsIndex+b,CompsIndex)=1;

    print();
}

void SparseMatrix::update(int i,int a, int b){

    col(2*CompsIndex-i-1).bottomRows(cols()-2*CompsIndex).setZero();
    row(CompsIndex-i-1).rightCols(cols()-2*CompsIndex).setZero();
    matrix()(CompsIndex-i-1,CompsIndex*2+a)=1;
    matrix()(2*CompsIndex+a,2*CompsIndex-i-1)=1;
    matrix()(CompsIndex-i-1,CompsIndex*2+b)=1;
    matrix()(2*CompsIndex+b,2*CompsIndex-i-1)=1;
    print();
}

void SparseMatrix::removeNode(int i){

    removeRow(2*CompsIndex + i);
    removeColumn(2*CompsIndex + i);
    terms->removeRow(2*CompsIndex+i);

    print();
}

void SparseMatrix::removeComponent(int i){
    removeRow(CompsIndex-i-1);
    removeColumn(CompsIndex-i-1);
    terms->removeRow(i);
    removeRow(2*CompsIndex-i-2);
    removeColumn(2*CompsIndex -i-2);
    terms->removeRow(2*CompsIndex-i-2);
    CompsIndex--;

    print();
}

void SparseMatrix::print(){
    std::cout<<"-----Matrix-----"<<std::endl;
    for(int i=0;i<rows();i++){
        std::cout<<row(i)<<"[X]"<<terms->row(i)<<std::endl;
    }
    std::cout<<"-----End--------"<<std::endl;
}