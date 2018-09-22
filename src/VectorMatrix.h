//
//  VectorMatrix.h
//  MatrixDSP
//
//  Created by Jim Clay on 9/21/18.
//

#ifndef VectorMatrix_h
#define VectorMatrix_h

#include "ComplexVector.h"
#include "Matrix2d.h"

namespace MatrixDSP {

// (m x n) * (n x 1) = (m x 1) - 2/4
// (m x n) * (n x p) = (m x p) - 1/4
// (1 x m) * (m x n) = (1 x n) - 2/4

template <class T>
Vector<T> operator*(Matrix2d<T> lhs, const Vector<T> &rhs) {
    assert(lhs.getCols() == rhs.size());
    assert(rhs.rowVector == false);
    
    Vector<T> result(lhs.getRows(), false);
    for (unsigned row=0; row<lhs.getRows(); row++) {
        for (unsigned col=0; col<lhs.getCols(); col++) {
            result[row] += lhs(row, col) * rhs[col];
        }
    }
    return result;
}

template <class T>
ComplexVector<T> operator*(Matrix2d<T> lhs, const ComplexVector<T> &rhs) {
    assert(lhs.getCols() == rhs.size());
    assert(rhs.rowVector == false);
    
    ComplexVector<T> result(lhs.getRows(), false);
    for (unsigned row=0; row<lhs.getRows(); row++) {
        for (unsigned col=0; col<lhs.getCols(); col++) {
            result[row] += lhs(row, col) * rhs[col];
        }
    }
    return result;
}

template <class T>
Vector<T> operator*(Vector<T> lhs, const Matrix2d<T> &rhs) {
    assert(lhs.size() == rhs.getRows());
    assert(lhs.rowVector == true);
    
    Vector<T> result(rhs.getCols(), true);
    for (unsigned col=0; col<rhs.getCols(); col++) {
        for (unsigned row=0; row<rhs.getRows(); row++) {
            result[col] += lhs[row] * rhs(row, col);
        }
    }
    return result;
}

template <class T>
ComplexVector<T> operator*(ComplexVector<T> lhs, const Matrix2d<T> &rhs) {
    assert(lhs.size() == rhs.getRows());
    assert(lhs.rowVector == true);
    
    ComplexVector<T> result(rhs.getCols(), true);
    for (unsigned col=0; col<rhs.getCols(); col++) {
        for (unsigned row=0; row<rhs.getRows(); row++) {
            result[col] += lhs[row] * rhs(row, col);
        }
    }
    return result;
}

template <class T>
Matrix2d<T> operator*(Matrix2d<T> lhs, const Matrix2d<T> &rhs) {
    assert(lhs.getCols() == rhs.getRows());
    
    Matrix2d<T> result(lhs.getRows(), rhs.getCols());
    for (unsigned row=0; row<lhs.getRows(); row++) {
        for (unsigned col=0; col<rhs.getCols(); col++) {
            for (unsigned colRow=0; colRow<lhs.getCols(); colRow++) {
                result(row, col) += lhs(row, colRow) * rhs(colRow, col);
            }
        }
    }
    return result;
}



}

#endif /* VectorMatrix_h */
