//
// Created by cipher on 01/07/19.
//

#ifndef FIRSTSIMULATORTEST_IMATRIX_H
#define FIRSTSIMULATORTEST_IMATRIX_H

#include <Eigen/Dense>

using namespace Eigen;

typedef Matrix<float,Dynamic,Dynamic> DynamicMatrix;

class EigenInterface: public DynamicMatrix {

public:
    EigenInterface();
    void addRow();
    void insertRow(int x);
    void insertCol(int x);
    void addCol();
    void removeColumn(int index);
    void removeRow(int index);
};


#endif //FIRSTSIMULATORTEST_IMATRIX_H
