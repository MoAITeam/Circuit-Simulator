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

    int p=a>b?1:-1;
    index=2*components+a;
    matrix()(0,index)=p;
    matrix()(index,components)=-p;

    index=2*components+b;
    matrix()(0,index)=-p;
    matrix()(index,components)=p;
}

void SparseMatrix::update(int i,int a, int b){

    int index=components-i-1;
    int nodes=cols()-2*components;
    row(index).rightCols(nodes).setZero();
    col(index+components).bottomRows(nodes).setZero();

    int p=a>b?1:-1;
    matrix()(index,components*2+a)=p;
    matrix()(2*components+a,index+components)=-p;
    matrix()(index,components*2+b)=-p;
    matrix()(2*components+b,index+components)=p;
}

void SparseMatrix::removeNode(int i){

    int index=2*components+i;
    removeRow(index);
    removeColumn(index);
    terms->removeRow(index);
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
}

void SparseMatrix::print(){

    EigenInterface zeroNodeMatrix=(*this);
    EigenInterface zeroNodeTerms=(*terms);
    int index=2*components;
    zeroNodeMatrix.removeRow(index);
    zeroNodeMatrix.removeColumn(index);
    zeroNodeTerms.removeRow(index);
    VectorXf solution;
    solution=(zeroNodeMatrix.cast <float> ()).colPivHouseholderQr().solve(((zeroNodeTerms).cast <float> ()).col(0));
    std::cout<<"-----Matrix-----"<<std::endl;
    DynamicMatrix print(rows(),cols()+1);
    print<<matrix(),*terms;
    std::cout<<print<<std::endl;
    std::cout<<"-----End--------"<<std::endl;
    std::cout<<"-----Solution---"<<std::endl;
    std::cout<<solution<<std::endl;
    std::cout<<"-----EndSol-----"<<std::endl;
}