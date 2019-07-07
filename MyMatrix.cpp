//
// Created by cipher on 01/07/19.
//

#include "MyMatrix.h"

MyMatrix::MyMatrix(){
    this->setZero(0,0);
}

void MyMatrix::addRow() {
    this->conservativeResize(this->rows()+1,NoChange);
    this->row(this->rows()-1).setZero();
}

void MyMatrix::addCol() {
    this->conservativeResize(NoChange,this->cols()+1);
    this->rightCols(1).setZero();
}

int MyMatrix::end() {
    return this->cols()-1;
}

int MyMatrix::bottom() {
    return this->rows()-1;
}

void MyMatrix::removeColumn(int index) {
    this->block(0,index,this->rows(),this->cols()-index-1)
            <<this->rightCols(this->cols()-index-1);
    this->conservativeResize(NoChange,this->cols()-1);
}

void MyMatrix::removeRow(int index) {
    this->block(index,0,this->rows()-index-1,this->cols())
            <<this->bottomRows(this->rows()-index-1);
    this->conservativeResize(this->rows()-1,NoChange);
}