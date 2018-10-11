#include "Matrix2d.h"
#include "gtest/gtest.h"
#include <cstdio>
//#include "Timer.h"

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

	//Timer timer;
	//timer.startTimer();
	//for (int index = 0; index < 1000000; index++)
	{
		reshape(mat1, mat2, 2, 6);
	}
	//double timeDiff = timer.getTimeDiff();
	//printf("Reshape time = %g s\n", timeDiff);
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

	//timer.startTimer();
	//for (int index = 0; index < 1000000; index++)
	{
		reshape(mat1, 4, 3);
	}
	//timeDiff = timer.getTimeDiff();
	//printf("Reshape time = %g s\n", timeDiff);
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

TEST(Matrix2d_Methods, Transpose) {
	MatrixDSP::Matrix2d<float> mat1({ {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} });
	MatrixDSP::Matrix2d<float> mat2(1, 1);

	//Timer timer;
	//timer.startTimer();
	//for (int index = 0; index < 1000001; index++)
	{
		transpose(mat1, mat2);
	}
	//double timeDiff = timer.getTimeDiff();
	//printf("Transpose time = %g s\n", timeDiff);
	EXPECT_EQ(4, mat2.getRows());
	EXPECT_EQ(3, mat2.getCols());
	EXPECT_EQ(1, mat2(0, 0));
	EXPECT_EQ(2, mat2(1, 0));
	EXPECT_EQ(3, mat2(2, 0));
	EXPECT_EQ(4, mat2(3, 0));
	EXPECT_EQ(5, mat2(0, 1));
	EXPECT_EQ(6, mat2(1, 1));
	EXPECT_EQ(7, mat2(2, 1));
	EXPECT_EQ(8, mat2(3, 1));
	EXPECT_EQ(9, mat2(0, 2));
	EXPECT_EQ(10, mat2(1, 2));
	EXPECT_EQ(11, mat2(2, 2));
	EXPECT_EQ(12, mat2(3, 2));

	//timer.startTimer();
	//for (int index = 0; index < 1000001; index++)
	{
		transpose(mat1);
	}
	//timeDiff = timer.getTimeDiff();
	//printf("Transpose time = %g s\n", timeDiff);
	EXPECT_EQ(4, mat1.getRows());
	EXPECT_EQ(3, mat1.getCols());
	EXPECT_EQ(1, mat1(0, 0));
	EXPECT_EQ(2, mat1(1, 0));
	EXPECT_EQ(3, mat1(2, 0));
	EXPECT_EQ(4, mat1(3, 0));
	EXPECT_EQ(5, mat1(0, 1));
	EXPECT_EQ(6, mat1(1, 1));
	EXPECT_EQ(7, mat1(2, 1));
	EXPECT_EQ(8, mat1(3, 1));
	EXPECT_EQ(9, mat1(0, 2));
	EXPECT_EQ(10, mat1(1, 2));
	EXPECT_EQ(11, mat1(2, 2));
	EXPECT_EQ(12, mat1(3, 2));
}

TEST(Matrix2dIterator, PlusPlus) {
	MatrixDSP::Matrix2d<float> mat({ {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} });
	float horizontalResults[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	float verticalResults[] = { 1, 5, 9, 2, 6, 10, 3, 7, 11, 4, 8, 12 };

	auto it = mat.begin(true);
	auto itEnd = mat.end(true);
	for (int index = 0; it != itEnd; ++it, index++) {
		EXPECT_EQ(horizontalResults[index], *it);
	}

	it = mat.begin();
	itEnd = mat.end();
	for (int index = 0; it != itEnd; ++it, index++) {
		EXPECT_EQ(verticalResults[index], *it);
	}
}

TEST(Matrix2dIterator, Sort) {
	MatrixDSP::Matrix2d<float> matStart({ {4, 3, 2, 1}, {9, 10, 11, 12}, {5, 6, 7, 8} });
	float results[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

	MatrixDSP::Matrix2d<float> mat(matStart);
	std::sort(mat.begin(true), mat.end(true));
	auto it = mat.begin(true);
	auto itEnd = mat.end(true);
	for (int index = 0; it != itEnd; ++it, index++) {
		EXPECT_EQ(results[index], *it);
	}

	mat = matStart;
	std::sort(mat.begin(), mat.end());
	it = mat.begin();
	itEnd = mat.end();
	for (int index = 0; it != itEnd; ++it, index++) {
		EXPECT_EQ(results[index], *it);
	}
}

TEST(Matrix2d_Operator, Negation) {
	MatrixDSP::Matrix2d<float> mat1({ { 1, 2, 3 }, { 4, 5, 6 } });
	MatrixDSP::Matrix2d<float> mat2;

	mat2 = -mat1;
	EXPECT_EQ(2, mat2.getRows());
	EXPECT_EQ(3, mat2.getCols());
	EXPECT_EQ(-1, mat2(0, 0));
	EXPECT_EQ(-2, mat2(0, 1));
	EXPECT_EQ(-3, mat2(0, 2));
	EXPECT_EQ(-4, mat2(1, 0));
	EXPECT_EQ(-5, mat2(1, 1));
	EXPECT_EQ(-6, mat2(1, 2));
}

TEST(Matrix2d_Operator, AddEqualMatrix) {
	MatrixDSP::Matrix2d<float> mat1({ { 1, 2, 3 }, { 4, 5, 6 } });
	MatrixDSP::Matrix2d<float> mat2({ { 2, 3, 4 }, { 6, 7, 8 } });

	mat2 += mat1;
	EXPECT_EQ(2, mat2.getRows());
	EXPECT_EQ(3, mat2.getCols());
	EXPECT_EQ(3, mat2(0, 0));
	EXPECT_EQ(5, mat2(0, 1));
	EXPECT_EQ(7, mat2(0, 2));
	EXPECT_EQ(10, mat2(1, 0));
	EXPECT_EQ(12, mat2(1, 1));
	EXPECT_EQ(14, mat2(1, 2));
}

TEST(Matrix2d_Operator, AddEqualScalar) {
	MatrixDSP::Matrix2d<float> mat({ { 1, 2, 3 }, { 4, 5, 6 } });

	mat += 2;
	EXPECT_EQ(2, mat.getRows());
	EXPECT_EQ(3, mat.getCols());
	EXPECT_EQ(3, mat(0, 0));
	EXPECT_EQ(4, mat(0, 1));
	EXPECT_EQ(5, mat(0, 2));
	EXPECT_EQ(6, mat(1, 0));
	EXPECT_EQ(7, mat(1, 1));
	EXPECT_EQ(8, mat(1, 2));
}

TEST(Matrix2d_Operator, AddMatrix) {
	MatrixDSP::Matrix2d<float> mat1({ { 1, 2, 3 }, { 4, 5, 6 } });
	MatrixDSP::Matrix2d<float> mat2({ { 2, 3, 4 }, { 6, 7, 8 } });
	MatrixDSP::Matrix2d<float> mat3;

	mat3 = mat2 + mat1;
	EXPECT_EQ(2, mat3.getRows());
	EXPECT_EQ(3, mat3.getCols());
	EXPECT_EQ(3, mat3(0, 0));
	EXPECT_EQ(5, mat3(0, 1));
	EXPECT_EQ(7, mat3(0, 2));
	EXPECT_EQ(10, mat3(1, 0));
	EXPECT_EQ(12, mat3(1, 1));
	EXPECT_EQ(14, mat3(1, 2));
}

TEST(Matrix2d_Operator, AddScalar) {
	MatrixDSP::Matrix2d<float> mat1({ { 1, 2, 3 }, { 4, 5, 6 } });
	MatrixDSP::Matrix2d<float> mat2;

	mat2 = mat1 + 2.0f;
	EXPECT_EQ(2, mat2.getRows());
	EXPECT_EQ(3, mat2.getCols());
	EXPECT_EQ(3, mat2(0, 0));
	EXPECT_EQ(4, mat2(0, 1));
	EXPECT_EQ(5, mat2(0, 2));
	EXPECT_EQ(6, mat2(1, 0));
	EXPECT_EQ(7, mat2(1, 1));
	EXPECT_EQ(8, mat2(1, 2));
}

TEST(Matrix2d_Operator, SubtractEqualMatrix) {
	MatrixDSP::Matrix2d<float> mat1({ { 1, 2, 3 }, { 4, 5, 6 } });
	MatrixDSP::Matrix2d<float> mat2({ { 2, 3, 4 }, { 6, 7, 8 } });

	mat2 -= mat1;
	EXPECT_EQ(2, mat2.getRows());
	EXPECT_EQ(3, mat2.getCols());
	EXPECT_EQ(1, mat2(0, 0));
	EXPECT_EQ(1, mat2(0, 1));
	EXPECT_EQ(1, mat2(0, 2));
	EXPECT_EQ(2, mat2(1, 0));
	EXPECT_EQ(2, mat2(1, 1));
	EXPECT_EQ(2, mat2(1, 2));
}

TEST(Matrix2d_Operator, SubtractEqualScalar) {
	MatrixDSP::Matrix2d<float> mat({ { 1, 2, 3 }, { 4, 5, 6 } });

	mat -= 2.0f;
	EXPECT_EQ(2, mat.getRows());
	EXPECT_EQ(3, mat.getCols());
	EXPECT_EQ(-1, mat(0, 0));
	EXPECT_EQ(0, mat(0, 1));
	EXPECT_EQ(1, mat(0, 2));
	EXPECT_EQ(2, mat(1, 0));
	EXPECT_EQ(3, mat(1, 1));
	EXPECT_EQ(4, mat(1, 2));
}

TEST(Matrix2d_Operator, SubtractMatrix) {
	MatrixDSP::Matrix2d<float> mat1({ { 1, 2, 3 }, { 4, 5, 6 } });
	MatrixDSP::Matrix2d<float> mat2({ { 2, 3, 4 }, { 6, 7, 8 } });
	MatrixDSP::Matrix2d<float> mat3;

	mat3 = mat2 - mat1;
	EXPECT_EQ(2, mat3.getRows());
	EXPECT_EQ(3, mat3.getCols());
	EXPECT_EQ(1, mat3(0, 0));
	EXPECT_EQ(1, mat3(0, 1));
	EXPECT_EQ(1, mat3(0, 2));
	EXPECT_EQ(2, mat3(1, 0));
	EXPECT_EQ(2, mat3(1, 1));
	EXPECT_EQ(2, mat3(1, 2));
}

TEST(Matrix2d_Operator, SubtractScalar) {
	MatrixDSP::Matrix2d<float> mat1({ { 1, 2, 3 }, { 4, 5, 6 } });
	MatrixDSP::Matrix2d<float> mat2;

	mat2 = mat1 - 2.0f;
	EXPECT_EQ(2, mat2.getRows());
	EXPECT_EQ(3, mat2.getCols());
	EXPECT_EQ(-1, mat2(0, 0));
	EXPECT_EQ(0, mat2(0, 1));
	EXPECT_EQ(1, mat2(0, 2));
	EXPECT_EQ(2, mat2(1, 0));
	EXPECT_EQ(3, mat2(1, 1));
	EXPECT_EQ(4, mat2(1, 2));
}

TEST(Matrix2d_Operator, MultiplyEqualScalar) {
	MatrixDSP::Matrix2d<float> mat({ { 1, 2, 3 }, { 4, 5, 6 } });

	mat *= 2.0f;
	EXPECT_EQ(2, mat.getRows());
	EXPECT_EQ(3, mat.getCols());
	EXPECT_EQ(2, mat(0, 0));
	EXPECT_EQ(4, mat(0, 1));
	EXPECT_EQ(6, mat(0, 2));
	EXPECT_EQ(8, mat(1, 0));
	EXPECT_EQ(10, mat(1, 1));
	EXPECT_EQ(12, mat(1, 2));
}

TEST(Matrix2d_Operator, MultiplyScalar) {
	MatrixDSP::Matrix2d<float> mat1({ { 1, 2, 3 }, { 4, 5, 6 } });
	MatrixDSP::Matrix2d<float> mat2;

	mat2 = mat1 * 2.0f;
	EXPECT_EQ(2, mat2.getRows());
	EXPECT_EQ(3, mat2.getCols());
	EXPECT_EQ(2, mat2(0, 0));
	EXPECT_EQ(4, mat2(0, 1));
	EXPECT_EQ(6, mat2(0, 2));
	EXPECT_EQ(8, mat2(1, 0));
	EXPECT_EQ(10, mat2(1, 1));
	EXPECT_EQ(12, mat2(1, 2));
}

TEST(Matrix2d_Operator, DivideEqualScalar) {
	MatrixDSP::Matrix2d<float> mat({ { 2, 4, 6 }, { 8, 10, 12 } });

	mat /= 2.0f;
	EXPECT_EQ(2, mat.getRows());
	EXPECT_EQ(3, mat.getCols());
	EXPECT_EQ(1, mat(0, 0));
	EXPECT_EQ(2, mat(0, 1));
	EXPECT_EQ(3, mat(0, 2));
	EXPECT_EQ(4, mat(1, 0));
	EXPECT_EQ(5, mat(1, 1));
	EXPECT_EQ(6, mat(1, 2));
}

TEST(Matrix2d_Operator, DivideScalar) {
	MatrixDSP::Matrix2d<float> mat1({ { 2, 4, 6 }, { 8, 10, 12 } });
	MatrixDSP::Matrix2d<float> mat2;

	mat2 = mat1 / 2.0f;
	EXPECT_EQ(2, mat2.getRows());
	EXPECT_EQ(3, mat2.getCols());
	EXPECT_EQ(1, mat2(0, 0));
	EXPECT_EQ(2, mat2(0, 1));
	EXPECT_EQ(3, mat2(0, 2));
	EXPECT_EQ(4, mat2(1, 0));
	EXPECT_EQ(5, mat2(1, 1));
	EXPECT_EQ(6, mat2(1, 2));
}

TEST(Matrix2d_Method, AppendRow) {
	MatrixDSP::Matrix2d<float> mat({ { 1, 2, 3 }, { 4, 5, 6 } });
	MatrixDSP::Vector<float> buf({ 7, 8, 9 });

	mat.appendRow(buf);

	EXPECT_EQ(3, mat.getRows());
	EXPECT_EQ(3, mat.getCols());
	EXPECT_EQ(1, mat(0, 0));
	EXPECT_EQ(2, mat(0, 1));
	EXPECT_EQ(3, mat(0, 2));
	EXPECT_EQ(4, mat(1, 0));
	EXPECT_EQ(5, mat(1, 1));
	EXPECT_EQ(6, mat(1, 2));
	EXPECT_EQ(7, mat(2, 0));
	EXPECT_EQ(8, mat(2, 1));
	EXPECT_EQ(9, mat(2, 2));
}

TEST(Matrix2d_Method, AppendRows) {
	MatrixDSP::Matrix2d<float> mat1({ { 1, 2, 3 }, { 4, 5, 6 } });
	MatrixDSP::Matrix2d<float> mat2({ { 7, 8, 9 }, {10, 11, 12} });

	mat1.appendRows(mat2);

	EXPECT_EQ(4, mat1.getRows());
	EXPECT_EQ(3, mat1.getCols());
	EXPECT_EQ(1, mat1(0, 0));
	EXPECT_EQ(2, mat1(0, 1));
	EXPECT_EQ(3, mat1(0, 2));
	EXPECT_EQ(4, mat1(1, 0));
	EXPECT_EQ(5, mat1(1, 1));
	EXPECT_EQ(6, mat1(1, 2));
	EXPECT_EQ(7, mat1(2, 0));
	EXPECT_EQ(8, mat1(2, 1));
	EXPECT_EQ(9, mat1(2, 2));
	EXPECT_EQ(10, mat1(3, 0));
	EXPECT_EQ(11, mat1(3, 1));
	EXPECT_EQ(12, mat1(3, 2));
}

TEST(Matrix2d_Method, AppendCol) {
	MatrixDSP::Matrix2d<float> mat({ { 1, 2, 3 }, { 4, 5, 6 } });
	MatrixDSP::Vector<float> buf({ 7, 8});

	mat.appendCol(buf);

	EXPECT_EQ(2, mat.getRows());
	EXPECT_EQ(4, mat.getCols());
	EXPECT_EQ(1, mat(0, 0));
	EXPECT_EQ(2, mat(0, 1));
	EXPECT_EQ(3, mat(0, 2));
	EXPECT_EQ(7, mat(0, 3));
	EXPECT_EQ(4, mat(1, 0));
	EXPECT_EQ(5, mat(1, 1));
	EXPECT_EQ(6, mat(1, 2));
	EXPECT_EQ(8, mat(1, 3));
}

TEST(Matrix2d_Method, AppendCols) {
	MatrixDSP::Matrix2d<float> mat1({ { 1, 2, 3 }, { 4, 5, 6 } });
	MatrixDSP::Matrix2d<float> mat2({ { 7, 8 }, {9, 10} });

	mat1.appendCols(mat2);

	EXPECT_EQ(2, mat1.getRows());
	EXPECT_EQ(5, mat1.getCols());
	EXPECT_EQ(1, mat1(0, 0));
	EXPECT_EQ(2, mat1(0, 1));
	EXPECT_EQ(3, mat1(0, 2));
	EXPECT_EQ(7, mat1(0, 3));
	EXPECT_EQ(8, mat1(0, 4));
	EXPECT_EQ(4, mat1(1, 0));
	EXPECT_EQ(5, mat1(1, 1));
	EXPECT_EQ(6, mat1(1, 2));
	EXPECT_EQ(9, mat1(1, 3));
	EXPECT_EQ(10, mat1(1, 4));
}

TEST(Matrix2d_Method, Find) {
	MatrixDSP::Matrix2d<float> mat({ { 1, 2}, {2, 3}, {0, 1} });

	auto locs = mat.find();
	EXPECT_EQ(5, locs.size());
	EXPECT_EQ(std::make_pair(0, 0).first, locs[0].first);
	EXPECT_EQ(std::make_pair(0, 0).second, locs[0].second);
	EXPECT_EQ(std::make_pair(0, 1).first, locs[1].first);
	EXPECT_EQ(std::make_pair(0, 1).second, locs[1].second);
	EXPECT_EQ(std::make_pair(1, 0).first, locs[2].first);
	EXPECT_EQ(std::make_pair(1, 0).second, locs[2].second);
	EXPECT_EQ(std::make_pair(1, 1).first, locs[3].first);
	EXPECT_EQ(std::make_pair(1, 1).second, locs[3].second);
	EXPECT_EQ(std::make_pair(2, 1).first, locs[4].first);
	EXPECT_EQ(std::make_pair(2, 1).second, locs[4].second);

	auto mat2 = mat >= 2.0f;
	locs = mat2.find();
	EXPECT_EQ(3, locs.size());
	EXPECT_EQ(std::make_pair(0, 1).first, locs[0].first);
	EXPECT_EQ(std::make_pair(0, 1).second, locs[0].second);
	EXPECT_EQ(std::make_pair(1, 0).first, locs[1].first);
	EXPECT_EQ(std::make_pair(1, 0).second, locs[1].second);
	EXPECT_EQ(std::make_pair(1, 1).first, locs[2].first);
	EXPECT_EQ(std::make_pair(1, 1).second, locs[2].second);

	mat2 = mat >= 4.0f;
	locs = mat2.find();
	EXPECT_EQ(0, locs.size());
}

TEST(Matrix2d_Operator, ComparisonScalar) {
	MatrixDSP::Matrix2d<float> mat({{ 11, 2, 3 }, { 3, 1, 5 }});
	MatrixDSP::Matrix2d<float> result;

	result = mat == 3.0f;
	EXPECT_EQ(2, result.getRows());
	EXPECT_EQ(3, result.getCols());
	EXPECT_EQ(0, result(0, 0));
	EXPECT_EQ(0, result(0, 1));
	EXPECT_EQ(1, result(0, 2));
	EXPECT_EQ(1, result(1, 0));
	EXPECT_EQ(0, result(1, 1));
	EXPECT_EQ(0, result(1, 2));

	result = mat != 3.0f;
	EXPECT_EQ(1, result(0, 0));
	EXPECT_EQ(1, result(0, 1));
	EXPECT_EQ(0, result(0, 2));
	EXPECT_EQ(0, result(1, 0));
	EXPECT_EQ(1, result(1, 1));
	EXPECT_EQ(1, result(1, 2));

	result = mat > 3.0f;
	EXPECT_EQ(1, result(0, 0));
	EXPECT_EQ(0, result(0, 1));
	EXPECT_EQ(0, result(0, 2));
	EXPECT_EQ(0, result(1, 0));
	EXPECT_EQ(0, result(1, 1));
	EXPECT_EQ(1, result(1, 2));

	result = mat >= 3.0f;
	EXPECT_EQ(1, result(0, 0));
	EXPECT_EQ(0, result(0, 1));
	EXPECT_EQ(1, result(0, 2));
	EXPECT_EQ(1, result(1, 0));
	EXPECT_EQ(0, result(1, 1));
	EXPECT_EQ(1, result(1, 2));

	result = mat < 3.0f;
	EXPECT_EQ(0, result(0, 0));
	EXPECT_EQ(1, result(0, 1));
	EXPECT_EQ(0, result(0, 2));
	EXPECT_EQ(0, result(1, 0));
	EXPECT_EQ(1, result(1, 1));
	EXPECT_EQ(0, result(1, 2));

	result = mat <= 3.0f;
	EXPECT_EQ(0, result(0, 0));
	EXPECT_EQ(1, result(0, 1));
	EXPECT_EQ(1, result(0, 2));
	EXPECT_EQ(1, result(1, 0));
	EXPECT_EQ(1, result(1, 1));
	EXPECT_EQ(0, result(1, 2));
}

TEST(Matrix2d_Operator, ComparisonMatrix) {
    MatrixDSP::Matrix2d<float> mat1({{ 11, 2, 3 }, { 3, 1, 5 }});
    MatrixDSP::Matrix2d<float> mat2({{ 10, 2, 4 }, { 4, 2, 4 }});
    MatrixDSP::Matrix2d<float> result;

    result = mat1 == mat2;
    EXPECT_EQ(2, result.getRows());
    EXPECT_EQ(3, result.getCols());
    EXPECT_EQ(0, result(0, 0));
    EXPECT_EQ(1, result(0, 1));
    EXPECT_EQ(0, result(0, 2));
    EXPECT_EQ(0, result(1, 0));
    EXPECT_EQ(0, result(1, 1));
    EXPECT_EQ(0, result(1, 2));

    result = mat1 != mat2;
    EXPECT_EQ(1, result(0, 0));
    EXPECT_EQ(0, result(0, 1));
    EXPECT_EQ(1, result(0, 2));
    EXPECT_EQ(1, result(1, 0));
    EXPECT_EQ(1, result(1, 1));
    EXPECT_EQ(1, result(1, 2));

    result = mat1 > mat2;
    EXPECT_EQ(1, result(0, 0));
    EXPECT_EQ(0, result(0, 1));
    EXPECT_EQ(0, result(0, 2));
    EXPECT_EQ(0, result(1, 0));
    EXPECT_EQ(0, result(1, 1));
    EXPECT_EQ(1, result(1, 2));

    result = mat1 >= mat2;
    EXPECT_EQ(1, result(0, 0));
    EXPECT_EQ(1, result(0, 1));
    EXPECT_EQ(0, result(0, 2));
    EXPECT_EQ(0, result(1, 0));
    EXPECT_EQ(0, result(1, 1));
    EXPECT_EQ(1, result(1, 2));

    result = mat1 < mat2;
    EXPECT_EQ(0, result(0, 0));
    EXPECT_EQ(0, result(0, 1));
    EXPECT_EQ(1, result(0, 2));
    EXPECT_EQ(1, result(1, 0));
    EXPECT_EQ(1, result(1, 1));
    EXPECT_EQ(0, result(1, 2));

    result = mat1 <= mat2;
    EXPECT_EQ(0, result(0, 0));
    EXPECT_EQ(1, result(0, 1));
    EXPECT_EQ(1, result(0, 2));
    EXPECT_EQ(1, result(1, 0));
    EXPECT_EQ(1, result(1, 1));
    EXPECT_EQ(0, result(1, 2));
}
