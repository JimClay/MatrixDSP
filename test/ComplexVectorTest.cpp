#include "ComplexVector.h"
#include "gtest/gtest.h"



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
    std::complex<float> data[] = {1, 2, 3, 4, 5};
    MatrixDSP::ComplexVector<float> buf(data, 5);
    
    EXPECT_EQ(5, buf.vec.size());
    for (unsigned index=0; index<5; index++) {
        EXPECT_EQ(data[index], buf.vec[index]);
    }
    EXPECT_EQ(false, buf.rowVector);
}

TEST(ComplexVectorInit, Ctor_Initializer_List) {
    MatrixDSP::ComplexVector<float> buf({3, 4, 5});
    
    EXPECT_EQ(3, buf.vec.size());
    EXPECT_EQ(std::complex<float>(3, 0), buf.vec[0]);
    EXPECT_EQ(std::complex<float>(4, 0), buf.vec[1]);
    EXPECT_EQ(std::complex<float>(5, 0), buf.vec[2]);
    EXPECT_EQ(false, buf.rowVector);
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
    MatrixDSP::ComplexVector<float> buf1({1, 2, 3});
    
    buf1 += std::complex<float>(5.0f, 0);
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(std::complex<float>(6, 0), buf1[0]);
    EXPECT_EQ(std::complex<float>(7, 0), buf1[1]);
    EXPECT_EQ(std::complex<float>(8, 0), buf1[2]);
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

TEST(ComplexVector_Method, Find) {
    MatrixDSP::ComplexVector<float> buf({5, 2, 3, 3, 4, 1});
    
    EXPECT_EQ(-1, buf.find(6));
    EXPECT_EQ(0, buf.find(std::complex<float>(5, 0)));
    EXPECT_EQ(2, buf.find(std::complex<float>(3, 0)));
    EXPECT_EQ(5, buf.find(std::complex<float>(1, 0)));
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

TEST(ComplexVector_Method, Var) {
    MatrixDSP::ComplexVector<float> buf({5, 2, 3, 3, 4, 1});
    
    EXPECT_EQ(std::complex<float>(2, 0), buf.var());
    std::complex<float> var = buf.var(false);
    EXPECT_NEAR(1.66666f, var.real(), .001);
    EXPECT_NEAR(0, var.imag(), .001);
}

/*
int main(int argc, char *argv[])
{
	MatrixDSP::ComplexVector<float> vec1(5);
    MatrixDSP::ComplexVector<float> vec2(new std::vector<float>(5));
    float data[] = {1, 2, 3, 4, 5};
    MatrixDSP::ComplexVector<float> vec3(data, 5);
    MatrixDSP::ComplexVector<float> vec4({6, 7, 8, 9, 10});
    
    PrintVector("vec1", vec1);
    PrintVector("vec2", vec2);
    PrintVector("vec3", vec3);
    PrintVector("vec4", vec4);
    //PrintVector("vec1 + vec2", vec1 + vec2);

	return 0;
}
*/
