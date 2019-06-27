//
// Created by Sierra on 2019-06-20.
//

#include "IMatrix.h"

IMatrix::IMatrix(){
    this->setZero(0,0);
}

void IMatrix::addRow() {
    this->conservativeResize(this->rows()+1,NoChange);
    this->row(this->rows()-1).setZero();
}

void IMatrix::addCol() {
    this->conservativeResize(NoChange,this->cols()+1);
    this->rightCols(1).setZero();
}

int IMatrix::end() {
    return this->cols()-1;
}

int IMatrix::bottom() {
    return this->rows()-1;
}

void IMatrix::removeColumn(int index) {
    this->block(0,index,this->rows(),this->cols()-index-1)
            <<this->rightCols(this->cols()-index-1);
    this->conservativeResize(NoChange,this->cols()-1);
}

void IMatrix::removeRow(int index) {
    this->block(index,0,this->rows()-index-1,this->cols())
            <<this->bottomRows(this->rows()-index-1);
    this->conservativeResize(this->rows()-1,NoChange);
}