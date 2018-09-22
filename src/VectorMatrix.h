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

// (m x n) * (n x 1) = (m x 1)
// (m x n) * (n x p) = (m x p)
// (1 x m) * (m x n) = (1 x n)
// (1 x m) * (m x 1) = (1 x 1)
// (m x 1) * (1 x n) = (m x n)
/*
template <class T, class U>
inline Vector<T> operator+(Vector<T> lhs, const Vector<U>& rhs)
{
    lhs += rhs;
    return lhs;
}*/

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



}

#endif /* VectorMatrix_h */
