#include "ComplexVector.h"
#include "gtest/gtest.h"
#include <ctime>


TEST(ComplexVectorInit, Ctor_Size) {
    MatrixDSP::ComplexVector<float> buf(50);
    
    EXPECT_EQ(50, buf.vec.size());
    for (std::complex<float> e : buf.vec) {
        EXPECT_EQ(std::complex<float>(0, 0), e);
    }
    EXPECT_EQ(false, buf.rowVector);
}

TEST(ComplexVectorInit, Ctor_Vector) {
    MatrixDSP::ComplexVector<float> buf(new std::vector< std::complex<float> >(5));
    
    EXPECT_EQ(5, buf.vec.size());
    EXPECT_EQ(false, buf.rowVector);
}

TEST(ComplexVectorInit, Ctor_Array) {
    std::complex<float> data[] = {1, 2, {3, 1}, 4, 5};
    MatrixDSP::ComplexVector<float> buf(data, 5);
    
    EXPECT_EQ(5, buf.vec.size());
    for (unsigned index=0; index<5; index++) {
        EXPECT_EQ(data[index], buf.vec[index]);
    }
    EXPECT_EQ(false, buf.rowVector);
}

TEST(ComplexVectorInit, Ctor_Initializer_List) {
    MatrixDSP::ComplexVector<float> buf({{3, 7}, 4, 5});
    
    EXPECT_EQ(3, buf.vec.size());
    EXPECT_EQ(std::complex<float>(3, 7), buf.vec[0]);
    EXPECT_EQ(std::complex<float>(4, 0), buf.vec[1]);
    EXPECT_EQ(std::complex<float>(5, 0), buf.vec[2]);
    EXPECT_EQ(false, buf.rowVector);
}

TEST(ComplexVectorInit, Parenthesis_Indexing) {
    MatrixDSP::ComplexVector<float> buf({3, {4, 1}, 5});
    
    EXPECT_EQ(3, buf(0).real());
    EXPECT_EQ(0, buf(0).imag());
    EXPECT_EQ(4, buf(1).real());
    EXPECT_EQ(1, buf(1).imag());
    EXPECT_EQ(5, buf(2).real());
    EXPECT_EQ(0, buf(2).imag());
}

TEST(ComplexVector_Operator, Negation) {
    MatrixDSP::ComplexVector<float> buf1({1, {2, 1}, 3});
    MatrixDSP::ComplexVector<float> buf2;
    
    buf2 = -buf1;
    EXPECT_EQ(3, buf2.size());
    EXPECT_EQ(-1, buf2[0].real());
    EXPECT_EQ(0, buf2[0].imag());
    EXPECT_EQ(-2, buf2[1].real());
    EXPECT_EQ(-1, buf2[1].imag());
    EXPECT_EQ(-3, buf2[2].real());
    EXPECT_EQ(0, buf2[2].imag());
}

TEST(ComplexVector_Operator, AddEqualVector) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::ComplexVector<float> buf2({8, 9, 10});
    
    buf1 += buf2;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(std::complex<float>(9, 0), buf1[0]);
    EXPECT_EQ(std::complex<float>(11, 0), buf1[1]);
    EXPECT_EQ(std::complex<float>(13, 0), buf1[2]);
}

TEST(ComplexVector_Operator, AddEqualScalar) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, {3, 6}});
    
    buf1 += std::complex<float>(5.0f, 2);
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(std::complex<float>(6, 2), buf1[0]);
    EXPECT_EQ(std::complex<float>(7, 2), buf1[1]);
    EXPECT_EQ(std::complex<float>(8, 8), buf1[2]);
}

TEST(ComplexVector_Operator, AddVector) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::ComplexVector<float> buf2({8, 9, 10});
    
    MatrixDSP::ComplexVector<float> buf3 = buf1 + buf2;
    EXPECT_EQ(3, buf3.size());
    EXPECT_EQ(std::complex<float>(9, 0), buf3[0]);
    EXPECT_EQ(std::complex<float>(11, 0), buf3[1]);
    EXPECT_EQ(std::complex<float>(13, 0), buf3[2]);
}

TEST(ComplexVector_Operator, AddScalar) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    
    MatrixDSP::ComplexVector<float> buf2 = buf1 + std::complex<float>(5.0f, 0);
    EXPECT_EQ(3, buf2.size());
    EXPECT_EQ(std::complex<float>(6, 0), buf2[0]);
    EXPECT_EQ(std::complex<float>(7, 0), buf2[1]);
    EXPECT_EQ(std::complex<float>(8, 0), buf2[2]);
}

TEST(ComplexVector_Operator, SubtractEqualVector) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::ComplexVector<float> buf2({8, 7, 6});
    
    buf1 -= buf2;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(std::complex<float>(-7, 0), buf1[0]);
    EXPECT_EQ(std::complex<float>(-5, 0), buf1[1]);
    EXPECT_EQ(std::complex<float>(-3, 0), buf1[2]);
}

TEST(ComplexVector_Operator, SubtractEqualScalar) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    
    buf1 -= std::complex<float>(5.0f, 0);
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(std::complex<float>(-4, 0), buf1[0]);
    EXPECT_EQ(std::complex<float>(-3, 0), buf1[1]);
    EXPECT_EQ(std::complex<float>(-2, 0), buf1[2]);
}

TEST(ComplexVector_Operator, SubtractVector) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::ComplexVector<float> buf2({8, 7, 6});
    
    MatrixDSP::ComplexVector<float> buf3 = buf1 - buf2;
    EXPECT_EQ(3, buf3.size());
    EXPECT_EQ(std::complex<float>(-7, 0), buf3[0]);
    EXPECT_EQ(std::complex<float>(-5, 0), buf3[1]);
    EXPECT_EQ(std::complex<float>(-3, 0), buf3[2]);
}

TEST(ComplexVector_Operator, SubtractScalar) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    
    MatrixDSP::ComplexVector<float> buf2 = buf1 - std::complex<float>(5.0f, 0);
    EXPECT_EQ(3, buf2.size());
    EXPECT_EQ(std::complex<float>(-4, 0), buf2[0]);
    EXPECT_EQ(std::complex<float>(-3, 0), buf2[1]);
    EXPECT_EQ(std::complex<float>(-2, 0), buf2[2]);
}

TEST(ComplexVector_Operator, MultiplyEqualVector) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::ComplexVector<float> buf2({8, 7, 6});
    
    buf1 *= buf2;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(std::complex<float>(8, 0), buf1[0]);
    EXPECT_EQ(std::complex<float>(14, 0), buf1[1]);
    EXPECT_EQ(std::complex<float>(18, 0), buf1[2]);
}

TEST(ComplexVector_Operator, MultiplyEqualScalar) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    
    buf1 *= std::complex<float>(2.0f, 0);
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(std::complex<float>(2, 0), buf1[0]);
    EXPECT_EQ(std::complex<float>(4, 0), buf1[1]);
    EXPECT_EQ(std::complex<float>(6, 0), buf1[2]);
}

TEST(ComplexVector_Operator, MultiplyVector) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::ComplexVector<float> buf2({8, 7, 6});
    
    MatrixDSP::ComplexVector<float> buf3 = buf1 * buf2;
    EXPECT_EQ(3, buf3.size());
    EXPECT_EQ(std::complex<float>(8, 0), buf3[0]);
    EXPECT_EQ(std::complex<float>(14, 0), buf3[1]);
    EXPECT_EQ(std::complex<float>(18, 0), buf3[2]);
}

TEST(ComplexVector_Operator, MultiplyScalar) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    
    MatrixDSP::ComplexVector<float> buf2 = buf1 * std::complex<float>(2.0f, 0);
    EXPECT_EQ(3, buf2.size());
    EXPECT_EQ(std::complex<float>(2, 0), buf2[0]);
    EXPECT_EQ(std::complex<float>(4, 0), buf2[1]);
    EXPECT_EQ(std::complex<float>(6, 0), buf2[2]);
}

TEST(ComplexVector_Operator, DivideEqualVector) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::ComplexVector<float> buf2({8, 7, 6});
    
    buf1 /= buf2;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(std::complex<float>(1.0f/8, 0), buf1[0]);
    EXPECT_EQ(std::complex<float>(2.0f/7, 0), buf1[1]);
    EXPECT_EQ(std::complex<float>(3.0f/6, 0), buf1[2]);
}

TEST(ComplexVector_Operator, DivideEqualScalar) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    
    buf1 /= std::complex<float>(2.0f, 0);
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(std::complex<float>(0.5f, 0), buf1[0]);
    EXPECT_EQ(std::complex<float>(1, 0), buf1[1]);
    EXPECT_EQ(std::complex<float>(1.5f, 0), buf1[2]);
}

TEST(ComplexVector_Operator, DivideVector) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::ComplexVector<float> buf2({8, 7, 6});
    
    MatrixDSP::ComplexVector<float> buf3 = buf1 / buf2;
    EXPECT_EQ(3, buf3.size());
    EXPECT_EQ(std::complex<float>(1.0f/8, 0), buf3[0]);
    EXPECT_EQ(std::complex<float>(2.0f/7, 0), buf3[1]);
    EXPECT_EQ(std::complex<float>(3.0f/6, 0), buf3[2]);
}

TEST(ComplexVector_Operator, DivideScalar) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    
    MatrixDSP::ComplexVector<float> buf2 = buf1 / std::complex<float>(2.0f, 0);
    EXPECT_EQ(3, buf2.size());
    EXPECT_EQ(std::complex<float>(0.5f, 0), buf2[0]);
    EXPECT_EQ(std::complex<float>(1, 0), buf2[1]);
    EXPECT_EQ(std::complex<float>(1.5f, 0), buf2[2]);
}

TEST(ComplexVector_Operator, AddEqualVector_Real) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 9, 10});
    
    buf1 += buf2;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(std::complex<float>(9, 0), buf1[0]);
    EXPECT_EQ(std::complex<float>(11, 0), buf1[1]);
    EXPECT_EQ(std::complex<float>(13, 0), buf1[2]);
}

TEST(ComplexVector_Operator, AddVector_Real) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 9, 10});
    
    MatrixDSP::ComplexVector<float> buf3 = buf1 + buf2;
    EXPECT_EQ(3, buf3.size());
    EXPECT_EQ(std::complex<float>(9, 0), buf3[0]);
    EXPECT_EQ(std::complex<float>(11, 0), buf3[1]);
    EXPECT_EQ(std::complex<float>(13, 0), buf3[2]);
}

TEST(ComplexVector_Operator, SubtractEqualVector_Real) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 7, 6});
    
    buf1 -= buf2;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(std::complex<float>(-7, 0), buf1[0]);
    EXPECT_EQ(std::complex<float>(-5, 0), buf1[1]);
    EXPECT_EQ(std::complex<float>(-3, 0), buf1[2]);
}

TEST(ComplexVector_Operator, SubtractVector_Real) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 7, 6});
    
    MatrixDSP::ComplexVector<float> buf3 = buf1 - buf2;
    EXPECT_EQ(3, buf3.size());
    EXPECT_EQ(std::complex<float>(-7, 0), buf3[0]);
    EXPECT_EQ(std::complex<float>(-5, 0), buf3[1]);
    EXPECT_EQ(std::complex<float>(-3, 0), buf3[2]);
}

TEST(ComplexVector_Operator, MultiplyEqualVector_Real) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 7, 6});
    
    buf1 *= buf2;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(std::complex<float>(8, 0), buf1[0]);
    EXPECT_EQ(std::complex<float>(14, 0), buf1[1]);
    EXPECT_EQ(std::complex<float>(18, 0), buf1[2]);
}

TEST(ComplexVector_Operator, MultiplyVector_Real) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 7, 6});
    
    MatrixDSP::ComplexVector<float> buf3 = buf1 * buf2;
    EXPECT_EQ(3, buf3.size());
    EXPECT_EQ(std::complex<float>(8, 0), buf3[0]);
    EXPECT_EQ(std::complex<float>(14, 0), buf3[1]);
    EXPECT_EQ(std::complex<float>(18, 0), buf3[2]);
}

TEST(ComplexVector_Operator, DivideEqualVector_Real) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 7, 6});
    
    buf1 /= buf2;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(std::complex<float>(1.0f/8, 0), buf1[0]);
    EXPECT_EQ(std::complex<float>(2.0f/7, 0), buf1[1]);
    EXPECT_EQ(std::complex<float>(3.0f/6, 0), buf1[2]);
}

TEST(ComplexVector_Operator, DivideVector_Real) {
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 7, 6});
    
    MatrixDSP::ComplexVector<float> buf3 = buf1 / buf2;
    EXPECT_EQ(3, buf3.size());
    EXPECT_EQ(std::complex<float>(1.0f/8, 0), buf3[0]);
    EXPECT_EQ(std::complex<float>(2.0f/7, 0), buf3[1]);
    EXPECT_EQ(std::complex<float>(3.0f/6, 0), buf3[2]);
}

TEST(ComplexVector_Method, Find) {
    MatrixDSP::ComplexVector<float> buf({5, 2, 3, 3, 4, 1});
    
	auto locs = find(buf == std::complex<float>(6, 0));
	EXPECT_EQ(0, locs.size());

	locs = find(buf == std::complex<float>(5, 0));
	EXPECT_EQ(1, locs.size());
	EXPECT_EQ(0, locs[0]);

	locs = find(buf != std::complex<float>(5, 0));
	EXPECT_EQ(5, locs.size());
	EXPECT_EQ(1, locs[0]);
	EXPECT_EQ(2, locs[1]);
	EXPECT_EQ(3, locs[2]);
	EXPECT_EQ(4, locs[3]);
	EXPECT_EQ(5, locs[4]);

	locs = find(buf == std::complex<float>(1, 0));
	EXPECT_EQ(1, locs.size());
	EXPECT_EQ(5, locs[0]);
}

TEST(ComplexVector_Method, Sum) {
    MatrixDSP::ComplexVector<float> buf({5, 2, 3, 3, 4, 1});
    
    EXPECT_EQ(std::complex<float>(18, 0), buf.sum());
}

TEST(ComplexVector_Method, Pow) {
    MatrixDSP::ComplexVector<float> buf({1, 2, 3});
    buf.pow(2);
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(std::complex<float>(1, 0), buf[0]);
    EXPECT_EQ(std::complex<float>(4, 0), buf[1]);
    EXPECT_EQ(std::complex<float>(9, 0), buf[2]);
}

TEST(ComplexVector_Method, Mean) {
    MatrixDSP::ComplexVector<float> buf({11, {2, 6}, 3, 3, 4, 1});
    
    EXPECT_EQ(4, buf.mean().real());
    EXPECT_EQ(1, buf.mean().imag());
}

TEST(ComplexVector_Method, Var) {
    MatrixDSP::ComplexVector<float> buf({5, 2, 3, 3, 4, 1});
    
    EXPECT_EQ(std::complex<float>(2, 0), buf.var());
    std::complex<float> var = buf.var(false);
    EXPECT_NEAR(1.66666f, var.real(), .001);
    EXPECT_NEAR(0, var.imag(), .001);
}

TEST(ComplexVector_Method, StdDev) {
    MatrixDSP::ComplexVector<float> buf({5, 2, 3, 3, 4, 1});
    
    EXPECT_NEAR(1.4142f, buf.stdDev().real(), .001);
    EXPECT_NEAR(1.2910f, buf.stdDev(false).real(), .001);
}

TEST(ComplexVector_Method, Max) {
    MatrixDSP::ComplexVector<float> buf({1, 4, {3, 4}, 2, 4.9});
    unsigned maxLoc;
    
    EXPECT_EQ(std::complex<float>(3, 4), buf.max(&maxLoc));
    EXPECT_EQ(2, maxLoc);
}

TEST(ComplexVector_Method, Min) {
    MatrixDSP::ComplexVector<float> buf({3, 4, {0, 4}, 2, 4.9});
    unsigned minLoc;
    
    EXPECT_EQ(std::complex<float>(2, 0), buf.min(&minLoc));
    EXPECT_EQ(3, minLoc);
}

TEST(ComplexVector_Method, Saturate) {
    MatrixDSP::ComplexVector<float> buf({{-10, 1}, {8, 12}, {3, -6}});
    buf.saturate(std::complex<float>(5, 4));
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-5, buf[0].real());
    EXPECT_EQ(1, buf[0].imag());
    EXPECT_EQ(5, buf[1].real());
    EXPECT_EQ(4, buf[1].imag());
    EXPECT_EQ(3, buf[2].real());
    EXPECT_EQ(-4, buf[2].imag());
}

TEST(ComplexVector_Method, Ceil) {
    MatrixDSP::ComplexVector<float> buf({-1.2, {2.6, -1.9}, 4});
    buf.ceil();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-1, buf[0].real());
    EXPECT_EQ(0, buf[0].imag());
    EXPECT_EQ(3, buf[1].real());
    EXPECT_EQ(-1, buf[1].imag());
    EXPECT_EQ(4, buf[2].real());
    EXPECT_EQ(0, buf[2].imag());
}

TEST(ComplexVector_Method, Floor) {
    MatrixDSP::ComplexVector<float> buf({-1.2, {2.6, -1.9}, 4});
    buf.floor();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-2, buf[0].real());
    EXPECT_EQ(0, buf[0].imag());
    EXPECT_EQ(2, buf[1].real());
    EXPECT_EQ(-2, buf[1].imag());
    EXPECT_EQ(4, buf[2].real());
    EXPECT_EQ(0, buf[2].imag());
}

TEST(ComplexVector_Method, Round) {
    MatrixDSP::ComplexVector<float> buf({-1.2, {2.6, -1.9}, 4});
    buf.round();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-1, buf[0].real());
    EXPECT_EQ(0, buf[0].imag());
    EXPECT_EQ(3, buf[1].real());
    EXPECT_EQ(-2, buf[1].imag());
    EXPECT_EQ(4, buf[2].real());
    EXPECT_EQ(0, buf[2].imag());
}

TEST(ComplexVector_Method, Abs) {
    MatrixDSP::ComplexVector<float> buf({-1.2, 2.6, 4});
    buf.abs();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_NEAR(1.2, buf[0].real(), .001);
    EXPECT_NEAR(0, buf[0].imag(), .001);
    EXPECT_NEAR(2.6, buf[1].real(), .001);
    EXPECT_NEAR(0, buf[1].imag(), .001);
    EXPECT_EQ(4, buf[2].real());
    EXPECT_EQ(0, buf[2].imag());
}

TEST(ComplexVector_Method, Exp) {
    MatrixDSP::ComplexVector<float> buf({-1.2, {2.6, 1}, 4});
    buf.exp();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_NEAR(.3012, buf[0].real(), .001);
    EXPECT_NEAR(0, buf[0].imag(), .001);
    EXPECT_NEAR(7.2745, buf[1].real(), .001);
    EXPECT_NEAR(11.3293, buf[1].imag(), .001);
    EXPECT_NEAR(54.5982, buf[2].real(), .001);
    EXPECT_NEAR(0, buf[2].imag(), .001);
}

TEST(ComplexVector_Method, Log) {
    MatrixDSP::ComplexVector<float> buf({1.2, {2.6, 1}, 4});
    buf.log();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_NEAR(0.1823, buf[0].real(), .001);
    EXPECT_NEAR(0, buf[0].imag(), .001);
    EXPECT_NEAR(1.0245, buf[1].real(), .001);
    EXPECT_NEAR(0.3672, buf[1].imag(), .001);
    EXPECT_NEAR(1.3863, buf[2].real(), .001);
    EXPECT_NEAR(0, buf[2].imag(), .001);
}

TEST(ComplexVector_Method, Log10) {
    MatrixDSP::ComplexVector<float> buf({.1, {10, 1}, 1000});
    buf.log10();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-1, buf[0].real());
    EXPECT_NEAR(0, buf[0].imag(), .001);
    EXPECT_NEAR(1.0022, buf[1].real(), .001);
    EXPECT_NEAR(0.0433, buf[1].imag(), .001);
    EXPECT_EQ(3, buf[2].real());
    EXPECT_NEAR(0, buf[2].imag(), .001);
}

TEST(ComplexVector_Method, Rotate) {
    MatrixDSP::ComplexVector<float> buf({10, 2, 3, 8, 9});
    
    buf.vectorRotate(2);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(3, buf[0].real());
    EXPECT_EQ(8, buf[1].real());
    EXPECT_EQ(9, buf[2].real());
    EXPECT_EQ(10, buf[3].real());
    EXPECT_EQ(2, buf[4].real());
    
    buf.vectorRotate(-3);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(9, buf[0].real());
    EXPECT_EQ(10, buf[1].real());
    EXPECT_EQ(2, buf[2].real());
    EXPECT_EQ(3, buf[3].real());
    EXPECT_EQ(8, buf[4].real());
    
    buf.vectorRotate(5);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(9, buf[0].real());
    EXPECT_EQ(10, buf[1].real());
    EXPECT_EQ(2, buf[2].real());
    EXPECT_EQ(3, buf[3].real());
    EXPECT_EQ(8, buf[4].real());
    
    buf.vectorRotate(-11);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(8, buf[0].real());
    EXPECT_EQ(9, buf[1].real());
    EXPECT_EQ(10, buf[2].real());
    EXPECT_EQ(2, buf[3].real());
    EXPECT_EQ(3, buf[4].real());
}

TEST(ComplexVector_Method, Reverse) {
    MatrixDSP::ComplexVector<float> buf({10, 2, 3, 8, 9});
    
    buf.reverse();
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(9, buf[0].real());
    EXPECT_EQ(8, buf[1].real());
    EXPECT_EQ(3, buf[2].real());
    EXPECT_EQ(2, buf[3].real());
    EXPECT_EQ(10, buf[4].real());
}

TEST(ComplexVector_Method, Resize) {
    MatrixDSP::ComplexVector<float> buf({10, 2, 3});
    
    buf.resize(5, std::complex<float>(1, -1));
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(10, buf[0].real());
    EXPECT_EQ(0, buf[0].imag());
    EXPECT_EQ(2, buf[1].real());
    EXPECT_EQ(0, buf[1].imag());
    EXPECT_EQ(3, buf[2].real());
    EXPECT_EQ(0, buf[2].imag());
    EXPECT_EQ(1, buf[3].real());
    EXPECT_EQ(-1, buf[3].imag());
    EXPECT_EQ(1, buf[4].real());
    EXPECT_EQ(-1, buf[4].imag());
}

TEST(ComplexVector_Method, Pad) {
    MatrixDSP::ComplexVector<float> buf({10, 2, 3});
    
    buf.pad(3, std::complex<float>(1, -1));
    EXPECT_EQ(6, buf.size());
    EXPECT_EQ(10, buf[0].real());
    EXPECT_EQ(0, buf[0].imag());
    EXPECT_EQ(2, buf[1].real());
    EXPECT_EQ(0, buf[1].imag());
    EXPECT_EQ(3, buf[2].real());
    EXPECT_EQ(0, buf[2].imag());
    EXPECT_EQ(1, buf[3].real());
    EXPECT_EQ(-1, buf[3].imag());
    EXPECT_EQ(1, buf[4].real());
    EXPECT_EQ(-1, buf[4].imag());
    EXPECT_EQ(1, buf[5].real());
    EXPECT_EQ(-1, buf[5].imag());
}

TEST(ComplexVector_Method, Upsmaple) {
    MatrixDSP::ComplexVector<float> buf({9, 2, 3});
    
    buf.upsample(3, 1);
    EXPECT_EQ(9, buf.size());
    EXPECT_EQ(0, buf[0].real());
    EXPECT_EQ(9, buf[1].real());
    EXPECT_EQ(0, buf[2].real());
    EXPECT_EQ(0, buf[3].real());
    EXPECT_EQ(2, buf[4].real());
    EXPECT_EQ(0, buf[5].real());
    EXPECT_EQ(0, buf[6].real());
    EXPECT_EQ(3, buf[7].real());
    EXPECT_EQ(0, buf[8].real());
}

TEST(ComplexVector_Method, Downsmaple) {
    MatrixDSP::ComplexVector<float> buf({0, 9, 0, 0, 2, 0, 0, 3, 0});
    
    buf.downsample(3, 1);
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(9, buf[0].real());
    EXPECT_EQ(2, buf[1].real());
    EXPECT_EQ(3, buf[2].real());
}

TEST(ComplexVector_Method, CumSum) {
    MatrixDSP::ComplexVector<float> buf({10, 2, 3});
    
    buf.cumsum();
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(10, buf[0].real());
    EXPECT_EQ(12, buf[1].real());
    EXPECT_EQ(15, buf[2].real());
}

TEST(ComplexVector_Method, Diff) {
    MatrixDSP::ComplexVector<float> buf1({10, 2, 3});
    
    buf1.diff();
    EXPECT_EQ(2, buf1.size());
    EXPECT_EQ(-8, buf1[0].real());
    EXPECT_EQ(1, buf1[1].real());
    
    MatrixDSP::ComplexVector<float> buf2({10, 2, 3});
    std::complex<float> previousVal = std::complex<float>(1, 2);
    buf2.diff(&previousVal);
    EXPECT_EQ(3, buf2.size());
    EXPECT_EQ(9, buf2[0].real());
    EXPECT_EQ(-2, buf2[0].imag());
    EXPECT_EQ(-8, buf2[1].real());
    EXPECT_EQ(0, buf2[1].imag());
    EXPECT_EQ(1, buf2[2].real());
    EXPECT_EQ(0, buf2[2].imag());
    EXPECT_EQ(std::complex<float>(3, 0), previousVal);
}

TEST(ComplexVector_Method, Tone) {
    MatrixDSP::ComplexVector<float> buf;
    
    float phase = buf.tone(0.25, 1, 0, 4);
    EXPECT_EQ(4, buf.size());
    EXPECT_NEAR(1, buf[0].real(), .0001);
    EXPECT_NEAR(0, buf[0].imag(), .0001);
    EXPECT_NEAR(0, buf[1].real(), .0001);
    EXPECT_NEAR(1, buf[1].imag(), .0001);
    EXPECT_NEAR(-1, buf[2].real(), .0001);
    EXPECT_NEAR(0, buf[2].imag(), .0001);
    EXPECT_NEAR(0, buf[3].real(), .0001);
    EXPECT_NEAR(-1, buf[3].imag(), .0001);
    EXPECT_NEAR(2 * M_PI, phase, .0001);
}

TEST(ComplexVector_Method, Modulate) {
    MatrixDSP::ComplexVector<float> buf({1, 1, 1, 1});
    
    float phase = buf.modulate(0.25, 1, 0);
    EXPECT_EQ(4, buf.size());
    EXPECT_NEAR(1, buf[0].real(), .0001);
    EXPECT_NEAR(0, buf[0].imag(), .0001);
    EXPECT_NEAR(0, buf[1].real(), .0001);
    EXPECT_NEAR(1, buf[1].imag(), .0001);
    EXPECT_NEAR(-1, buf[2].real(), .0001);
    EXPECT_NEAR(0, buf[2].imag(), .0001);
    EXPECT_NEAR(0, buf[3].real(), .0001);
    EXPECT_NEAR(-1, buf[3].imag(), .0001);
    EXPECT_NEAR(2 * M_PI, phase, .0001);
}

TEST(ComplexVector_Method, Fft_Real) {
    MatrixDSP::Vector<float>  bufIn({1, 2, 3, 4, 5, 6});
    MatrixDSP::ComplexVector<float> bufOut;
    
    std::clock_t start = std::clock();
    //for (int index=0; index<1000000; index++)
    {
    fft(bufIn, bufOut);
    }
    std::clock_t end = std::clock();
    printf("FFT Real time = %f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    EXPECT_EQ(6, bufOut.size());
    EXPECT_NEAR(21, bufOut[0].real(), .0001);
    EXPECT_NEAR(0, bufOut[0].imag(), .0001);
    EXPECT_NEAR(-3, bufOut[1].real(), .0001);
    EXPECT_NEAR(5.1962, bufOut[1].imag(), .0001);
    EXPECT_NEAR(-3, bufOut[2].real(), .0001);
    EXPECT_NEAR(1.7321, bufOut[2].imag(), .0001);
    EXPECT_NEAR(-3, bufOut[3].real(), .0001);
    EXPECT_NEAR(0, bufOut[3].imag(), .0001);
    EXPECT_NEAR(-3, bufOut[4].real(), .0001);
    EXPECT_NEAR(-1.7321, bufOut[4].imag(), .0001);
    EXPECT_NEAR(-3, bufOut[5].real(), .0001);
    EXPECT_NEAR(-5.1962, bufOut[5].imag(), .0001);
}

TEST(ComplexVector_Method, Fft) {
    MatrixDSP::ComplexVector<float>  bufIn({1, 2, 3, 4, 5, 6});
    MatrixDSP::ComplexVector<float> bufOut;
    
    std::clock_t start = std::clock();
    //for (int index=0; index<1000000; index++)
    {
    fft(bufIn, bufOut);
    }
    std::clock_t end = std::clock();
    printf("FFT Complex time = %f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    EXPECT_EQ(6, bufOut.size());
    EXPECT_NEAR(21, bufOut[0].real(), .0001);
    EXPECT_NEAR(0, bufOut[0].imag(), .0001);
    EXPECT_NEAR(-3, bufOut[1].real(), .0001);
    EXPECT_NEAR(5.1962, bufOut[1].imag(), .0001);
    EXPECT_NEAR(-3, bufOut[2].real(), .0001);
    EXPECT_NEAR(1.7321, bufOut[2].imag(), .0001);
    EXPECT_NEAR(-3, bufOut[3].real(), .0001);
    EXPECT_NEAR(0, bufOut[3].imag(), .0001);
    EXPECT_NEAR(-3, bufOut[4].real(), .0001);
    EXPECT_NEAR(-1.7321, bufOut[4].imag(), .0001);
    EXPECT_NEAR(-3, bufOut[5].real(), .0001);
    EXPECT_NEAR(-5.1962, bufOut[5].imag(), .0001);
}

TEST(ComplexVector_Operator, Comparison) {
	MatrixDSP::ComplexVector<float> buf({ 11, 2, {3, 1}, 3, 1 });
	MatrixDSP::ComplexVector<float> result;

	result = buf == std::complex<float>(3, 0);
	EXPECT_EQ(5, result.size());
	EXPECT_EQ(0, result[0].real());
	EXPECT_EQ(0, result[1].real());
	EXPECT_EQ(0, result[2].real());
	EXPECT_EQ(1, result[3].real());
	EXPECT_EQ(0, result[4].real());

	result = buf != std::complex<float>(3, 0);
	EXPECT_EQ(5, result.size());
	EXPECT_EQ(1, result[0].real());
	EXPECT_EQ(1, result[1].real());
	EXPECT_EQ(1, result[2].real());
	EXPECT_EQ(0, result[3].real());
	EXPECT_EQ(1, result[4].real());

	result = buf > std::complex<float>(3, 0);
	EXPECT_EQ(5, result.size());
	EXPECT_EQ(1, result[0].real());
	EXPECT_EQ(0, result[1].real());
	EXPECT_EQ(1, result[2].real());
	EXPECT_EQ(0, result[3].real());
	EXPECT_EQ(0, result[4].real());

	result = buf >= std::complex<float>(3, 0);
	EXPECT_EQ(5, result.size());
	EXPECT_EQ(1, result[0].real());
	EXPECT_EQ(0, result[1].real());
	EXPECT_EQ(1, result[2].real());
	EXPECT_EQ(1, result[3].real());
	EXPECT_EQ(0, result[4].real());

	result = buf < std::complex<float>(3, 0);
	EXPECT_EQ(5, result.size());
	EXPECT_EQ(0, result[0].real());
	EXPECT_EQ(1, result[1].real());
	EXPECT_EQ(0, result[2].real());
	EXPECT_EQ(0, result[3].real());
	EXPECT_EQ(1, result[4].real());

	result = buf <= std::complex<float>(3, 0);
	EXPECT_EQ(5, result.size());
	EXPECT_EQ(0, result[0].real());
	EXPECT_EQ(1, result[1].real());
	EXPECT_EQ(0, result[2].real());
	EXPECT_EQ(1, result[3].real());
	EXPECT_EQ(1, result[4].real());
}

