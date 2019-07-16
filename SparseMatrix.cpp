//
// Created by Sierra on 2019-07-06.
//

#include "SparseMatrix.h"
#include "Component.h"
#include <iostream>
#include "MatrixException.h"

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

void SparseMatrix::add(const float behavior[3],int a, int b) {
    insertRow(0);
    insertCol(0);
    terms->insertRow(0);
    matrix()(0,0)=1;
    (*terms)(0,0)=0;
    

    int index=components+1;
    insertRow(index);
    insertCol(index);
    terms->insertRow(index);

    matrix()(index,0)=behavior[0];
    matrix()(index,index)=behavior[1];
    (*terms)(index)=behavior[2];

    components++;

    int i=a>b?1:-1;

    if(a!=notFound) {
        matrix()(0, 2 * components + a) = i;
        matrix()(2 * components + a, components) = -i;
    }

    if(b!=notFound) {
        matrix()(0, 2 * components + b) = -i;
        matrix()(2 * components + b, components) = i;
    }

}

void SparseMatrix::update(int i,int a,int b){

    int index=components-i-1;
    int nodes=cols()-2*components;
    row(index).rightCols(nodes).setZero();
    col(index+components).bottomRows(nodes).setZero();

    int c=a>b?1:-1;
    if(a!=notFound) {
        matrix()(index, components * 2 + a) = c;
        matrix()(2 * components + a, index + components) = -c;
    }

    if(b!=notFound) {
        matrix()(index, components * 2 + b) = -c;
        matrix()(2 * components + b, index + components) = c;
    }
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
    std::cout<<"-----Matrix-----"<<std::endl;
    DynamicMatrix print(rows(),cols()+1);
    print<<matrix(),*terms;
    std::cout<<print<<std::endl;
    std::cout<<"-----End--------"<<std::endl;
}


std::vector<float> SparseMatrix::solve(){

    VectorXf solution;
    solution=(*this).colPivHouseholderQr().solve((*terms).col(0));
    std::vector<float> sol;
    sol.resize(solution.size());
    VectorXf::Map(&sol[0],solution.size())=solution;
    return sol;

}