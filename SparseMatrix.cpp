//
// Created by Sierra on 2019-07-06.
//

#include "SparseMatrix.h"
#include "Component.h"
#include <iostream>

SparseMatrix::SparseMatrix(): components(0) {
    terms=new EigenInterface();
    terms->resize(0,1);
}

SparseMatrix::~SparseMatrix(){
    delete terms;
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

    int index=components+1;
    insertRow(index);
    insertCol(index);

    terms->insertRow(index);
    matrix()(index,0)=c->behavior[0];
    matrix()(index,index)=c->behavior[1];
    (*terms)(index)=c->behavior[2];

    components++;

    index=2*components+a;
    matrix()(0,index)=1;
    matrix()(index,components)=1;

    index=2*components+b;
    matrix()(0,index)=1;
    matrix()(index,components)=1;

    //print();
}

void SparseMatrix::update(int i,int a, int b){

    int index=components-i-1;
    int nodes=cols()-2*components;
    row(index).rightCols(nodes).setZero();
    col(index+components).bottomRows(nodes).setZero();
    matrix()(index,components*2+a)=1;
    matrix()(2*components+a,index+components)=1;
    matrix()(index,components*2+b)=1;
    matrix()(2*components+b,index+components)=1;
    //print();
}

void SparseMatrix::removeNode(int i){

    int index=2*components+i;
    removeRow(index);
    removeColumn(index);
    terms->removeRow(index);

    //print();
}

void SparseMatrix::removeComponent(int i){
    int index=components-i-1;
    removeRow(index);
    removeColumn(index);
    terms->removeRow(i);
    index=index+components-1;
    removeRow(index);
    removeColumn(index);
    terms->removeRow(index);
    components--;

    //print();
}

void SparseMatrix::print(){
    std::cout<<"-----Matrix-----"<<std::endl;
    for(int i=0;i<rows();i++){
        std::cout<<row(i)<<"[X]"<<terms->row(i)<<std::endl;
    }
    std::cout<<"-----End--------"<<std::endl;
}