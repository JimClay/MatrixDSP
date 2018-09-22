//
//  VectorMatrixTest.cpp
//  MatrixDspTests
//
//  Created by Jim Clay on 9/21/18.
//

#include "VectorMatrix.h"
#include "gtest/gtest.h"


TEST(VectorMatrix, MatrixVectorMult) {
    MatrixDSP::Vector<float> vec({1, 2, 3});
    MatrixDSP::Matrix2d<float> mat({{1, 2, 3}, {4, 5, 6}});
    
    MatrixDSP::Vector<float> result = mat * vec;
    EXPECT_EQ(2, result.size());
    EXPECT_EQ(false, result.rowVector);
    EXPECT_EQ(14, result[0]);
    EXPECT_EQ(32, result[1]);
}

TEST(VectorMatrix, MatrixComplexVectorMult) {
    MatrixDSP::ComplexVector<float> vec({1, {2, 1}, 3});
    MatrixDSP::Matrix2d<float> mat({{1, 2, 3}, {4, 5, 6}});
    
    MatrixDSP::ComplexVector<float> result = mat * vec;
    EXPECT_EQ(2, result.size());
    EXPECT_EQ(false, result.rowVector);
    EXPECT_EQ(14, result[0].real());
    EXPECT_EQ(2, result[0].imag());
    EXPECT_EQ(32, result[1].real());
    EXPECT_EQ(5, result[1].imag());
}

