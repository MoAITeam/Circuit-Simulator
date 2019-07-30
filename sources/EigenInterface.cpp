//
// Created by cipher on 01/07/19.
//

#include "EigenInterface.h"
#include <iostream>

EigenInterface::EigenInterface(){
    this->setZero(0,0);
}

void EigenInterface::addRow() {
    conservativeResize(rows()+1,NoChange);
    row(rows()-1).setZero();
}

void EigenInterface::addCol() {
    conservativeResize(NoChange,cols()+1);
    col(cols()-1).setZero();
}

void EigenInterface::insertRow(int x) {
    Matrix<float,Dynamic,Dynamic> updated = Matrix<float,Dynamic,Dynamic>::Zero(rows()+1, cols());
    updated.topRows(x)= this->topRows(x);
    updated.bottomRows(rows()-x) =  this->bottomRows(rows()-x);
    this->resize(rows()+1,cols());
    matrix().swap(updated);
}

void EigenInterface::insertCol(int x) {
    Matrix<float,Dynamic,Dynamic> updated = Matrix<float,Dynamic,Dynamic>::Zero(rows(), cols()+1);
    updated.leftCols(x) = leftCols(x);
    updated.rightCols(cols()-x) =  rightCols(cols()-x);
    this->resize(rows(),cols()+1);
    matrix().swap(updated);
}

void EigenInterface::removeColumn(int index) {
    this->block(0,index,this->rows(),this->cols()-index-1)
            <<this->rightCols(this->cols()-index-1);
    this->conservativeResize(NoChange,this->cols()-1);
}

void EigenInterface::removeRow(int index) {
    this->block(index,0,this->rows()-index-1,this->cols())
            <<this->bottomRows(this->rows()-index-1);
    this->conservativeResize(this->rows()-1,NoChange);
}