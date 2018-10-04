#include "Matrix2d.h"
#include "gtest/gtest.h"
#include <cstdio>


TEST(Matrix2d_Iterator, Sort) {
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

TEST(Matrix2d_Iterator, SortTransposed) {
    MatrixDSP::Matrix2d<float> mat({{3, 1, 2}, {5, -1, 7}});
    
    EXPECT_EQ(2, mat.getRows());
    EXPECT_EQ(3, mat.getCols());
    
    EXPECT_EQ(3, mat(0, 0));
    EXPECT_EQ(1, mat(0, 1));
    EXPECT_EQ(2, mat(0, 2));
    EXPECT_EQ(5, mat(1, 0));
    EXPECT_EQ(-1, mat(1, 1));
    EXPECT_EQ(7, mat(1, 2));
    
    transpose(mat);
    
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
    
    MatrixDSP::Matrix2d<float> mat2(1, 1);
    transpose(mat, mat2);
    
    EXPECT_EQ(2, mat2.getRows());
    EXPECT_EQ(3, mat2.getCols());
    
    EXPECT_EQ(1, mat2(0, 0));
    EXPECT_EQ(2, mat2(0, 1));
    EXPECT_EQ(3, mat2(0, 2));
    EXPECT_EQ(5, mat2(1, 0));
    EXPECT_EQ(-1, mat2(1, 1));
    EXPECT_EQ(7, mat2(1, 2));
}

TEST(Matrix2d_Methods, Resize) {
	MatrixDSP::Matrix2d<float> matStart({ {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}});
	MatrixDSP::Matrix2d<float> matResized(1, 1);
	unsigned rows, cols;
	float val;
	unsigned testRows[] = { 2, 1, 2, 3, 3, 3, 4, 5, 6 };
	unsigned testCols[] = { 1, 4, 5, 3, 4, 7, 2, 4, 6 };
	unsigned testVal[] = { 0, 1, 0, 1, 0, 1, 0, 1, 0 };

	for (int index = 0; index < 9; index++) {
		matResized = matStart;
		rows = testRows[index];
		cols = testCols[index];
		val = testVal[index];
		resize(matResized, rows, cols, val);
		unsigned minRows = std::min(rows, matStart.getRows());
		unsigned minCols = std::min(cols, matStart.getCols());
		EXPECT_EQ(rows, matResized.getRows());
		EXPECT_EQ(cols, matResized.getCols());
		for (unsigned row = 0; row < minRows; row++) {
			for (unsigned col = 0; col < minCols; col++) {
				EXPECT_EQ(matStart(row, col), matResized(row, col));
			}
			for (unsigned col = minCols; col < cols; col++) {
				EXPECT_EQ(val, matResized(row, col));
			}
		}
		for (unsigned row = minRows; row < rows; row++) {
			for (unsigned col = 0; col < cols; col++) {
				EXPECT_EQ(val, matResized(row, col));
			}
		}
	}
}

TEST(Matrix2d_Methods, Reshape) {
	MatrixDSP::Matrix2d<float> mat1({ {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} });
	MatrixDSP::Matrix2d<float> mat2(mat1);

	reshape(mat1, mat2, 2, 6);
	EXPECT_EQ(2, mat2.getRows());
	EXPECT_EQ(6, mat2.getCols());
	EXPECT_EQ(1, mat2(0, 0));
	EXPECT_EQ(5, mat2(1, 0));
	EXPECT_EQ(9, mat2(0, 1));
	EXPECT_EQ(2, mat2(1, 1));
	EXPECT_EQ(6, mat2(0, 2));
	EXPECT_EQ(10, mat2(1, 2));
	EXPECT_EQ(3, mat2(0, 3));
	EXPECT_EQ(7, mat2(1, 3));
	EXPECT_EQ(11, mat2(0, 4));
	EXPECT_EQ(4, mat2(1, 4));
	EXPECT_EQ(8, mat2(0, 5));
	EXPECT_EQ(12, mat2(1, 5));
	
	reshape(mat1, 4, 3);
	EXPECT_EQ(4, mat1.getRows());
	EXPECT_EQ(3, mat1.getCols());
	EXPECT_EQ(1, mat1(0, 0));
	EXPECT_EQ(5, mat1(1, 0));
	EXPECT_EQ(9, mat1(2, 0));
	EXPECT_EQ(2, mat1(3, 0));
	EXPECT_EQ(6, mat1(0, 1));
	EXPECT_EQ(10, mat1(1, 1));
	EXPECT_EQ(3, mat1(2, 1));
	EXPECT_EQ(7, mat1(3, 1));
	EXPECT_EQ(11, mat1(0, 2));
	EXPECT_EQ(4, mat1(1, 2));
	EXPECT_EQ(8, mat1(2, 2));
	EXPECT_EQ(12, mat1(3, 2));
}




