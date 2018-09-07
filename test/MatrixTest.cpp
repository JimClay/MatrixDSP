#include "Matrix2d.h"
#include "gtest/gtest.h"
#include <cstdio>


TEST(Iterator, Sort) {
    MatrixDSP::Matrix2d<float> mat({{3, 1, 2}, {5, -1, 7}});
    
    EXPECT_EQ(2, mat.numRows);
    EXPECT_EQ(3, mat.numCols);
    
    EXPECT_EQ(3, mat(0, 0));
    EXPECT_EQ(1, mat(0, 1));
    EXPECT_EQ(2, mat(0, 2));
    EXPECT_EQ(5, mat(1, 0));
    EXPECT_EQ(-1, mat(1, 1));
    EXPECT_EQ(7, mat(1, 2));
    
    std::sort(mat.rowBegin(1), mat.rowEnd(1));
    EXPECT_EQ(3, mat(0, 0));
    EXPECT_EQ(1, mat(0, 1));
    EXPECT_EQ(2, mat(0, 2));
    EXPECT_EQ(-1, mat(1, 0));
    EXPECT_EQ(5, mat(1, 1));
    EXPECT_EQ(7, mat(1, 2));
    
    std::sort(mat.rowBegin(0), mat.rowEnd(0));
    EXPECT_EQ(1, mat(0, 0));
    EXPECT_EQ(2, mat(0, 1));
    EXPECT_EQ(3, mat(0, 2));
    EXPECT_EQ(-1, mat(1, 0));
    EXPECT_EQ(5, mat(1, 1));
    EXPECT_EQ(7, mat(1, 2));
    
    std::sort(mat.colBegin(0), mat.colEnd(0));
    EXPECT_EQ(-1, mat(0, 0));
    EXPECT_EQ(2, mat(0, 1));
    EXPECT_EQ(3, mat(0, 2));
    EXPECT_EQ(1, mat(1, 0));
    EXPECT_EQ(5, mat(1, 1));
    EXPECT_EQ(7, mat(1, 2));
    
}



