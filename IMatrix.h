//
// Created by Sierra on 2019-06-20.
//

#ifndef FIRSTSIMULATORTEST_IMATRIX_H
#define FIRSTSIMULATORTEST_IMATRIX_H

#include <Eigen/Dense>

using namespace Eigen;

typedef Matrix<int,Dynamic,Dynamic> DynamicMatrix;

class IMatrix: public DynamicMatrix {

public:
    IMatrix();
    void addRow();
    void addCol();
    int end();
    int bottom();
    void removeColumn(int index);
    void removeRow(int index);
};


#endif //FIRSTSIMULATORTEST_IMATRIX_H
