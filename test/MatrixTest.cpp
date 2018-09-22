#include "Matrix2d.h"
#include "gtest/gtest.h"
#include <cstdio>

/*
TEST(Iterator, Sort) {
    MatrixDSP::Matrix2d<float> mat({{3, 1, 2}, {5, -1, 7}});
    
    EXPECT_EQ(2, mat.getRows());
    EXPECT_EQ(3, mat.getCols());
    
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

TEST(Iterator, SortTransposed) {
    MatrixDSP::Matrix2d<float> mat({{3, 1, 2}, {5, -1, 7}});
    
    EXPECT_EQ(2, mat.getRows());
    EXPECT_EQ(3, mat.getCols());
    
    EXPECT_EQ(3, mat(0, 0));
    EXPECT_EQ(1, mat(0, 1));
    EXPECT_EQ(2, mat(0, 2));
    EXPECT_EQ(5, mat(1, 0));
    EXPECT_EQ(-1, mat(1, 1));
    EXPECT_EQ(7, mat(1, 2));
    
    mat.transpose();
    
    EXPECT_EQ(3, mat.getRows());
    EXPECT_EQ(2, mat.getCols());
    
    EXPECT_EQ(3, mat(0, 0));
    EXPECT_EQ(1, mat(1, 0));
    EXPECT_EQ(2, mat(2, 0));
    EXPECT_EQ(5, mat(0, 1));
    EXPECT_EQ(-1, mat(1, 1));
    EXPECT_EQ(7, mat(2, 1));
    
    std::sort(mat.colBegin(0), mat.colEnd(0));
    
    EXPECT_EQ(1, mat(0, 0));
    EXPECT_EQ(2, mat(1, 0));
    EXPECT_EQ(3, mat(2, 0));
    EXPECT_EQ(5, mat(0, 1));
    EXPECT_EQ(-1, mat(1, 1));
    EXPECT_EQ(7, mat(2, 1));
    
    std::sort(mat.rowBegin(1), mat.rowEnd(1));
    
    EXPECT_EQ(1, mat(0, 0));
    EXPECT_EQ(-1, mat(1, 0));
    EXPECT_EQ(3, mat(2, 0));
    EXPECT_EQ(5, mat(0, 1));
    EXPECT_EQ(2, mat(1, 1));
    EXPECT_EQ(7, mat(2, 1));
    
    std::sort(mat.colBegin(1), mat.colEnd(1));
    
    EXPECT_EQ(1, mat(0, 0));
    EXPECT_EQ(-1, mat(1, 0));
    EXPECT_EQ(3, mat(2, 0));
    EXPECT_EQ(2, mat(0, 1));
    EXPECT_EQ(5, mat(1, 1));
    EXPECT_EQ(7, mat(2, 1));
}
*/


