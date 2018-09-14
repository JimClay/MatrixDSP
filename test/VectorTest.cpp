#include "Vector.h"
#include "gtest/gtest.h"


void PrintVector(char const *str, MatrixDSP::Vector<float> &vec)
{
    printf("%s =", str);
    for (float e : vec.vec) {
        printf(" %f", e);
    }
    printf("\n");
}


TEST(VectorInit, Ctor_Size) {
    MatrixDSP::Vector<float> buf(50);
    
    EXPECT_EQ(50, buf.vec.size());
    for (float e : buf.vec) {
        EXPECT_EQ(0, e);
    }
    EXPECT_EQ(false, buf.rowVector);
}

TEST(VectorInit, Ctor_Vector) {
    MatrixDSP::Vector<float> buf(new std::vector<float>(5));
    
    EXPECT_EQ(5, buf.vec.size());
    EXPECT_EQ(false, buf.rowVector);
}

TEST(VectorInit, Ctor_Array) {
    float data[] = {1, 2, 3, 4, 5};
    MatrixDSP::Vector<float> buf(data, 5);
    
    EXPECT_EQ(5, buf.vec.size());
    for (unsigned index=0; index<5; index++) {
        EXPECT_EQ(data[index], buf.vec[index]);
    }
    EXPECT_EQ(false, buf.rowVector);
}

TEST(VectorInit, Ctor_Initializer_List) {
    MatrixDSP::Vector<float> buf({3, 4, 5});
    
    EXPECT_EQ(3, buf.vec.size());
    EXPECT_EQ(3, buf.vec[0]);
    EXPECT_EQ(4, buf.vec[1]);
    EXPECT_EQ(5, buf.vec[2]);
    EXPECT_EQ(false, buf.rowVector);
}

TEST(Operator, AddEqualVector) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 9, 10});
    
    buf1 += buf2;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(9, buf1[0]);
    EXPECT_EQ(11, buf1[1]);
    EXPECT_EQ(13, buf1[2]);
}

TEST(Operator, AddEqualScalar) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    
    buf1 += 5.0f;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(6, buf1[0]);
    EXPECT_EQ(7, buf1[1]);
    EXPECT_EQ(8, buf1[2]);
}

TEST(Operator, AddVector) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 9, 10});
    
    MatrixDSP::Vector<float> buf3 = buf1 + buf2;
    EXPECT_EQ(3, buf3.size());
    EXPECT_EQ(9, buf3[0]);
    EXPECT_EQ(11, buf3[1]);
    EXPECT_EQ(13, buf3[2]);
}

TEST(Operator, AddScalar) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    
    MatrixDSP::Vector<float> buf2 = buf1 + 5.0f;
    EXPECT_EQ(3, buf2.size());
    EXPECT_EQ(6, buf2[0]);
    EXPECT_EQ(7, buf2[1]);
    EXPECT_EQ(8, buf2[2]);
}

TEST(Operator, SubtractEqualVector) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 7, 6});
    
    buf1 -= buf2;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(-7, buf1[0]);
    EXPECT_EQ(-5, buf1[1]);
    EXPECT_EQ(-3, buf1[2]);
}

TEST(Operator, SubtractEqualScalar) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    
    buf1 -= 5.0f;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(-4, buf1[0]);
    EXPECT_EQ(-3, buf1[1]);
    EXPECT_EQ(-2, buf1[2]);
}

TEST(Operator, SubtractVector) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 7, 6});
    
    MatrixDSP::Vector<float> buf3 = buf1 - buf2;
    EXPECT_EQ(3, buf3.size());
    EXPECT_EQ(-7, buf3[0]);
    EXPECT_EQ(-5, buf3[1]);
    EXPECT_EQ(-3, buf3[2]);
}

TEST(Operator, SubtractScalar) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    
    MatrixDSP::Vector<float> buf2 = buf1 - 5.0f;
    EXPECT_EQ(3, buf2.size());
    EXPECT_EQ(-4, buf2[0]);
    EXPECT_EQ(-3, buf2[1]);
    EXPECT_EQ(-2, buf2[2]);
}

TEST(Operator, MultiplyEqualVector) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 7, 6});
    
    buf1 *= buf2;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(8, buf1[0]);
    EXPECT_EQ(14, buf1[1]);
    EXPECT_EQ(18, buf1[2]);
}

TEST(Operator, MultiplyEqualScalar) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    
    buf1 *= 2.0f;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(2, buf1[0]);
    EXPECT_EQ(4, buf1[1]);
    EXPECT_EQ(6, buf1[2]);
}

TEST(Operator, MultiplyVector) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 7, 6});
    
    MatrixDSP::Vector<float> buf3 = buf1 * buf2;
    EXPECT_EQ(3, buf3.size());
    EXPECT_EQ(8, buf3[0]);
    EXPECT_EQ(14, buf3[1]);
    EXPECT_EQ(18, buf3[2]);
}

TEST(Operator, MultiplyScalar) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    
    MatrixDSP::Vector<float> buf2 = buf1 * 2.0f;
    EXPECT_EQ(3, buf2.size());
    EXPECT_EQ(2, buf2[0]);
    EXPECT_EQ(4, buf2[1]);
    EXPECT_EQ(6, buf2[2]);
}

TEST(Operator, DivideEqualVector) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 7, 6});
    
    buf1 /= buf2;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(1.0f/8, buf1[0]);
    EXPECT_EQ(2.0f/7, buf1[1]);
    EXPECT_EQ(3.0f/6, buf1[2]);
}

TEST(Operator, DivideEqualScalar) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    
    buf1 /= 2.0f;
    EXPECT_EQ(3, buf1.size());
    EXPECT_EQ(0.5f, buf1[0]);
    EXPECT_EQ(1, buf1[1]);
    EXPECT_EQ(1.5f, buf1[2]);
}

TEST(Operator, DivideVector) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    MatrixDSP::Vector<float> buf2({8, 7, 6});
    
    MatrixDSP::Vector<float> buf3 = buf1 / buf2;
    EXPECT_EQ(3, buf3.size());
    EXPECT_EQ(1.0f/8, buf3[0]);
    EXPECT_EQ(2.0f/7, buf3[1]);
    EXPECT_EQ(3.0f/6, buf3[2]);
}

TEST(Operator, DivideScalar) {
    MatrixDSP::Vector<float> buf1({1, 2, 3});
    
    MatrixDSP::Vector<float> buf2 = buf1 / 2.0f;
    EXPECT_EQ(3, buf2.size());
    EXPECT_EQ(0.5f, buf2[0]);
    EXPECT_EQ(1, buf2[1]);
    EXPECT_EQ(1.5f, buf2[2]);
}

TEST(Method, Find) {
    MatrixDSP::Vector<float> buf({5, 2, 3, 3, 4, 1});
    
    EXPECT_EQ(-1, buf.find(6));
    EXPECT_EQ(0, buf.find(5));
    EXPECT_EQ(2, buf.find(3));
    EXPECT_EQ(5, buf.find(1));
}

TEST(Method, Sum) {
    MatrixDSP::Vector<float> buf({5, 2, 3, 3, 4, 1});
    
    EXPECT_EQ(18, buf.sum());
}

TEST(Method, Pow) {
    MatrixDSP::Vector<float> buf({1, 2, 3});
    buf.pow(2);
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(1, buf[0]);
    EXPECT_EQ(4, buf[1]);
    EXPECT_EQ(9, buf[2]);
}

TEST(Method, Mean) {
    MatrixDSP::Vector<float> buf({11, 2, 3, 3, 4, 1});
    
    EXPECT_EQ(4, buf.mean());
}

TEST(Method, Var) {
    MatrixDSP::Vector<float> buf({5, 2, 3, 3, 4, 1});
    
    EXPECT_EQ(2, buf.var());
    EXPECT_NEAR(1.66666f, buf.var(false), .001);
}

TEST(Method, StdDev) {
    MatrixDSP::Vector<float> buf({5, 2, 3, 3, 4, 1});
    
    EXPECT_NEAR(1.4142f, buf.stdDev(), .001);
    EXPECT_NEAR(1.2910f, buf.stdDev(false), .001);
}

TEST(Method, Median) {
    MatrixDSP::Vector<float> buf1({10, 2, 3, 8, 9});
    EXPECT_EQ(8, buf1.median());
    
    MatrixDSP::Vector<float> buf2({1, 10, 2, 3, 8, 9});
    EXPECT_EQ(5.5f, buf2.median());
}

TEST(Method, Max) {
    MatrixDSP::Vector<float> buf1({10, 2, 3, 8, 9});
    EXPECT_EQ(10, buf1.max());
    
    MatrixDSP::Vector<float> buf2({1, 10, 2, 3, 8, 9});
    unsigned maxLoc;
    EXPECT_EQ(10, buf2.max(&maxLoc));
    EXPECT_EQ(1, maxLoc);
}

TEST(Method, Min) {
    MatrixDSP::Vector<float> buf1({10, 2, 3, 8, 9});
    EXPECT_EQ(2, buf1.min());
    
    MatrixDSP::Vector<float> buf2({1, 10, 2, 3, 8, 9});
    unsigned minLoc;
    EXPECT_EQ(1, buf2.min(&minLoc));
    EXPECT_EQ(0, minLoc);
}

TEST(Method, Saturate) {
    MatrixDSP::Vector<float> buf({-10, 8, 3});
    buf.saturate(5);
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-5, buf[0]);
    EXPECT_EQ(5, buf[1]);
    EXPECT_EQ(3, buf[2]);
}

TEST(Method, Ceil) {
    MatrixDSP::Vector<float> buf({-1.2, 2.6, 4});
    buf.ceil();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-1, buf[0]);
    EXPECT_EQ(3, buf[1]);
    EXPECT_EQ(4, buf[2]);
}

TEST(Method, Floor) {
    MatrixDSP::Vector<float> buf({-1.2, 2.6, 4});
    buf.floor();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-2, buf[0]);
    EXPECT_EQ(2, buf[1]);
    EXPECT_EQ(4, buf[2]);
}

TEST(Method, Round) {
    MatrixDSP::Vector<float> buf({-1.2, 2.6, 4});
    buf.round();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-1, buf[0]);
    EXPECT_EQ(3, buf[1]);
    EXPECT_EQ(4, buf[2]);
}

TEST(Method, Abs) {
    MatrixDSP::Vector<float> buf({-1.2, 2.6, 4});
    buf.abs();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_NEAR(1.2, buf[0], .001);
    EXPECT_NEAR(2.6, buf[1], .001);
    EXPECT_EQ(4, buf[2]);
}

TEST(Method, Exp) {
    MatrixDSP::Vector<float> buf({-1.2, 2.6, 4});
    buf.exp();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_NEAR(.3012, buf[0], .001);
    EXPECT_NEAR(13.4637, buf[1], .001);
    EXPECT_NEAR(54.5982, buf[2], .001);
}

TEST(Method, Log) {
    MatrixDSP::Vector<float> buf({1.2, 2.6, 4});
    buf.log();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_NEAR(0.1823, buf[0], .001);
    EXPECT_NEAR(0.9555, buf[1], .001);
    EXPECT_NEAR(1.3863, buf[2], .001);
}

TEST(Method, Log10) {
    MatrixDSP::Vector<float> buf({.1, 10, 1000});
    buf.log10();
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-1, buf[0]);
    EXPECT_EQ(1, buf[1]);
    EXPECT_EQ(3, buf[2]);
}

TEST(Method, Rotate) {
    MatrixDSP::Vector<float> buf({10, 2, 3, 8, 9});
    
    buf.vectorRotate(2);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(3, buf[0]);
    EXPECT_EQ(8, buf[1]);
    EXPECT_EQ(9, buf[2]);
    EXPECT_EQ(10, buf[3]);
    EXPECT_EQ(2, buf[4]);
    
    buf.vectorRotate(-3);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(9, buf[0]);
    EXPECT_EQ(10, buf[1]);
    EXPECT_EQ(2, buf[2]);
    EXPECT_EQ(3, buf[3]);
    EXPECT_EQ(8, buf[4]);
    
    buf.vectorRotate(5);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(9, buf[0]);
    EXPECT_EQ(10, buf[1]);
    EXPECT_EQ(2, buf[2]);
    EXPECT_EQ(3, buf[3]);
    EXPECT_EQ(8, buf[4]);
    
    buf.vectorRotate(-11);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(8, buf[0]);
    EXPECT_EQ(9, buf[1]);
    EXPECT_EQ(10, buf[2]);
    EXPECT_EQ(2, buf[3]);
    EXPECT_EQ(3, buf[4]);
}
