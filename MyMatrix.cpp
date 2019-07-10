//
// Created by cipher on 01/07/19.
//

#include "MyMatrix.h"
#include <iostream>

MyMatrix::MyMatrix(){
    this->setZero(0,0);
}

void MyMatrix::addRow() {
    conservativeResize(rows()+1,NoChange);
    row(rows()-1).setZero();
}

void MyMatrix::addCol() {
    conservativeResize(NoChange,cols()+1);
    col(cols()-1).setZero();
}

void MyMatrix::ROWinsertBetweenNthAndNthplusOne(int x) {
    Matrix<int,Dynamic,Dynamic> B = Matrix<int,Dynamic,Dynamic>::Zero(this->rows()+1, this->cols());
    B.topRows(x) = topRows(x);
    B.bottomRows(rows()-x) =  bottomRows(this->rows()-x);
    this->resize(rows()+1,cols());
    matrix().swap(B);
}

void MyMatrix::COLinsertBetweenNthAndNthplusOne(int x) {
    Matrix<int,Dynamic,Dynamic> B = Matrix<int,Dynamic,Dynamic>::Zero(rows(), cols()+1);
    B.leftCols(x) = leftCols(x);
    B.rightCols(cols()-x) =  rightCols(cols()-x);
    this->resize(rows(),cols()+1);
    matrix().swap(B);
}

int MyMatrix::end() {
    return this->cols()-1;
}

int MyMatrix::bottom() {
    return this->rows()-1;
}

void MyMatrix::removeColumn(int index) {
    this->block(0,index,this->rows(),this->cols()-index-1)<<this->rightCols(this->cols()-index-1);
    this->conservativeResize(NoChange,this->cols()-1);
}

void MyMatrix::removeRow(int index) {
    this->block(index,0,this->rows()-index-1,this->cols())<<this->bottomRows(this->rows()-index-1);
    this->conservativeResize(this->rows()-1,NoChange);
}