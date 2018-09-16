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
    
    EXPECT_EQ(-1, MatrixDSP::find(buf, 6.0f));
    EXPECT_EQ(0, buf.find(5));
    EXPECT_EQ(2, buf.find(3));
    EXPECT_EQ(5, buf.find(1));
}

TEST(Method, Sum) {
    MatrixDSP::Vector<float> buf({5, 2, 3, 3, 4, 1});
    
    EXPECT_EQ(18, MatrixDSP::sum(buf));
}

TEST(Method, Pow) {
    MatrixDSP::Vector<float> buf({1, 2, 3});
    MatrixDSP::pow(buf, 2.0f);
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(1, buf[0]);
    EXPECT_EQ(4, buf[1]);
    EXPECT_EQ(9, buf[2]);
}

TEST(Method, Mean) {
    MatrixDSP::Vector<float> buf({11, 2, 3, 3, 4, 1});
    
    EXPECT_EQ(4, MatrixDSP::mean(buf));
}

TEST(Method, Var) {
    MatrixDSP::Vector<float> buf({5, 2, 3, 3, 4, 1});
    
    EXPECT_EQ(2, buf.var());
    EXPECT_NEAR(1.66666f, MatrixDSP::var(buf, false), .001);
}

TEST(Method, StdDev) {
    MatrixDSP::Vector<float> buf({5, 2, 3, 3, 4, 1});
    
    EXPECT_NEAR(1.4142f, MatrixDSP::stdDev(buf), .001);
    EXPECT_NEAR(1.2910f, MatrixDSP::stdDev(buf, false), .001);
}

TEST(Method, Median) {
    MatrixDSP::Vector<float> buf1({10, 2, 3, 8, 9});
    EXPECT_EQ(8, MatrixDSP::median(buf1));
    
    MatrixDSP::Vector<float> buf2({1, 10, 2, 3, 8, 9});
    EXPECT_EQ(5.5f, MatrixDSP::median(buf2));
}

TEST(Method, Max) {
    MatrixDSP::Vector<float> buf1({10, 2, 3, 8, 9});
    EXPECT_EQ(10, MatrixDSP::max(buf1));
    
    MatrixDSP::Vector<float> buf2({1, 10, 2, 3, 8, 9});
    unsigned maxLoc;
    EXPECT_EQ(10, MatrixDSP::max(buf2, &maxLoc));
    EXPECT_EQ(1, maxLoc);
}

TEST(Method, Min) {
    MatrixDSP::Vector<float> buf1({10, 2, 3, 8, 9});
    EXPECT_EQ(2, MatrixDSP::min(buf1));
    
    MatrixDSP::Vector<float> buf2({1, 10, 2, 3, 8, 9});
    unsigned minLoc;
    EXPECT_EQ(1, MatrixDSP::min(buf2, &minLoc));
    EXPECT_EQ(0, minLoc);
}

TEST(Method, Saturate) {
    MatrixDSP::Vector<float> buf({-10, 8, 3});
    MatrixDSP::saturate(buf, 5.0f);
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-5, buf[0]);
    EXPECT_EQ(5, buf[1]);
    EXPECT_EQ(3, buf[2]);
}

TEST(Method, Ceil) {
    MatrixDSP::Vector<float> buf({-1.2, 2.6, 4});
    MatrixDSP::ceil(buf);
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-1, buf[0]);
    EXPECT_EQ(3, buf[1]);
    EXPECT_EQ(4, buf[2]);
}

TEST(Method, Floor) {
    MatrixDSP::Vector<float> buf({-1.2, 2.6, 4});
    MatrixDSP::floor(buf);
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-2, buf[0]);
    EXPECT_EQ(2, buf[1]);
    EXPECT_EQ(4, buf[2]);
}

TEST(Method, Round) {
    MatrixDSP::Vector<float> buf({-1.2, 2.6, 4});
    MatrixDSP::round(buf);
    
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(-1, buf[0]);
    EXPECT_EQ(3, buf[1]);
    EXPECT_EQ(4, buf[2]);
}

TEST(Method, Abs) {
    MatrixDSP::Vector<float> buf({-1.2, 2.6, 4});
    MatrixDSP::abs(buf);
    
    EXPECT_EQ(3, buf.size());
    EXPECT_NEAR(1.2, buf[0], .001);
    EXPECT_NEAR(2.6, buf[1], .001);
    EXPECT_EQ(4, buf[2]);
}

TEST(Method, Exp) {
    MatrixDSP::Vector<float> buf({-1.2, 2.6, 4});
    MatrixDSP::exp(buf);
    
    EXPECT_EQ(3, buf.size());
    EXPECT_NEAR(.3012, buf[0], .001);
    EXPECT_NEAR(13.4637, buf[1], .001);
    EXPECT_NEAR(54.5982, buf[2], .001);
}

TEST(Method, Log) {
    MatrixDSP::Vector<float> buf({1.2, 2.6, 4});
    MatrixDSP::log(buf);
    
    EXPECT_EQ(3, MatrixDSP::size(buf));
    EXPECT_NEAR(0.1823, buf[0], .001);
    EXPECT_NEAR(0.9555, buf[1], .001);
    EXPECT_NEAR(1.3863, buf[2], .001);
}

TEST(Method, Log10) {
    MatrixDSP::Vector<float> buf({.1, 10, 1000});
    MatrixDSP::log10(buf);
    
    EXPECT_EQ(3, MatrixDSP::length(buf));
    EXPECT_EQ(-1, buf[0]);
    EXPECT_EQ(1, buf[1]);
    EXPECT_EQ(3, buf[2]);
}

TEST(Method, Rotate) {
    MatrixDSP::Vector<float> buf({10, 2, 3, 8, 9});
    
    MatrixDSP::vectorRotate(buf, 2);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(3, buf[0]);
    EXPECT_EQ(8, buf[1]);
    EXPECT_EQ(9, buf[2]);
    EXPECT_EQ(10, buf[3]);
    EXPECT_EQ(2, buf[4]);
    
    MatrixDSP::vectorRotate(buf, -3);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(9, buf[0]);
    EXPECT_EQ(10, buf[1]);
    EXPECT_EQ(2, buf[2]);
    EXPECT_EQ(3, buf[3]);
    EXPECT_EQ(8, buf[4]);
    
    MatrixDSP::vectorRotate(buf, 5);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(9, buf[0]);
    EXPECT_EQ(10, buf[1]);
    EXPECT_EQ(2, buf[2]);
    EXPECT_EQ(3, buf[3]);
    EXPECT_EQ(8, buf[4]);
    
    MatrixDSP::vectorRotate(buf, -11);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(8, buf[0]);
    EXPECT_EQ(9, buf[1]);
    EXPECT_EQ(10, buf[2]);
    EXPECT_EQ(2, buf[3]);
    EXPECT_EQ(3, buf[4]);
}

TEST(Method, Reverse) {
    MatrixDSP::Vector<float> buf({10, 2, 3, 8, 9});
    
    MatrixDSP::reverse(buf);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(9, buf[0]);
    EXPECT_EQ(8, buf[1]);
    EXPECT_EQ(3, buf[2]);
    EXPECT_EQ(2, buf[3]);
    EXPECT_EQ(10, buf[4]);
    
    buf.rowVector = true;
    MatrixDSP::flipud(buf);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(9, buf[0]);
    EXPECT_EQ(8, buf[1]);
    EXPECT_EQ(3, buf[2]);
    EXPECT_EQ(2, buf[3]);
    EXPECT_EQ(10, buf[4]);
    
    buf.rowVector = false;
    MatrixDSP::flipud(buf);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(10, buf[0]);
    EXPECT_EQ(2, buf[1]);
    EXPECT_EQ(3, buf[2]);
    EXPECT_EQ(8, buf[3]);
    EXPECT_EQ(9, buf[4]);
    
    MatrixDSP::fliplr(buf);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(10, buf[0]);
    EXPECT_EQ(2, buf[1]);
    EXPECT_EQ(3, buf[2]);
    EXPECT_EQ(8, buf[3]);
    EXPECT_EQ(9, buf[4]);
    
    buf.rowVector = true;
    MatrixDSP::fliplr(buf);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(9, buf[0]);
    EXPECT_EQ(8, buf[1]);
    EXPECT_EQ(3, buf[2]);
    EXPECT_EQ(2, buf[3]);
}

TEST(Method, Resize) {
    MatrixDSP::Vector<float> buf({10, 2, 3});
    
    MatrixDSP::resize(buf, 5, 1.0f);
    EXPECT_EQ(5, buf.size());
    EXPECT_EQ(10, buf[0]);
    EXPECT_EQ(2, buf[1]);
    EXPECT_EQ(3, buf[2]);
    EXPECT_EQ(1, buf[3]);
    EXPECT_EQ(1, buf[4]);
}

TEST(Method, Pad) {
    MatrixDSP::Vector<float> buf({10, 2, 3});
    
    MatrixDSP::pad(buf, 3, -1.0f);
    EXPECT_EQ(6, buf.size());
    EXPECT_EQ(10, buf[0]);
    EXPECT_EQ(2, buf[1]);
    EXPECT_EQ(3, buf[2]);
    EXPECT_EQ(-1, buf[3]);
    EXPECT_EQ(-1, buf[4]);
    EXPECT_EQ(-1, buf[5]);
}

TEST(Method, Upsmaple) {
    MatrixDSP::Vector<float> buf({9, 2, 3});
    
    MatrixDSP::upsample(buf, 3, 1);
    EXPECT_EQ(9, buf.size());
    EXPECT_EQ(0, buf[0]);
    EXPECT_EQ(9, buf[1]);
    EXPECT_EQ(0, buf[2]);
    EXPECT_EQ(0, buf[3]);
    EXPECT_EQ(2, buf[4]);
    EXPECT_EQ(0, buf[5]);
    EXPECT_EQ(0, buf[6]);
    EXPECT_EQ(3, buf[7]);
    EXPECT_EQ(0, buf[8]);
}

TEST(Method, Downsmaple) {
    MatrixDSP::Vector<float> buf({0, 9, 0, 0, 2, 0, 0, 3, 0});
    
    MatrixDSP::downsample(buf, 3, 1);
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(9, buf[0]);
    EXPECT_EQ(2, buf[1]);
    EXPECT_EQ(3, buf[2]);
}

TEST(Method, CumSum) {
    MatrixDSP::Vector<float> buf({10, 2, 3});
    
    MatrixDSP::cumsum(buf);
    EXPECT_EQ(3, buf.size());
    EXPECT_EQ(10, buf[0]);
    EXPECT_EQ(12, buf[1]);
    EXPECT_EQ(15, buf[2]);
}

TEST(Method, Diff) {
    MatrixDSP::Vector<float> buf1({10, 2, 3});
    
    MatrixDSP::diff(buf1);
    EXPECT_EQ(2, buf1.size());
    EXPECT_EQ(-8, buf1[0]);
    EXPECT_EQ(1, buf1[1]);
    
    MatrixDSP::Vector<float> buf2({10, 2, 3});
    float previousVal = 5;
    MatrixDSP::diff(buf2, &previousVal);
    EXPECT_EQ(3, buf2.size());
    EXPECT_EQ(5, buf2[0]);
    EXPECT_EQ(-8, buf2[1]);
    EXPECT_EQ(1, buf2[2]);
    EXPECT_EQ(3, previousVal);
}

TEST(Method, Sine) {
    MatrixDSP::Vector<float> buf;
    
    float phase = MatrixDSP::sine(buf, 0.25f, 1.0f, 0.0f, 4);
    EXPECT_EQ(4, buf.size());
    EXPECT_NEAR(0, buf[0], .0001);
    EXPECT_NEAR(1, buf[1], .0001);
    EXPECT_NEAR(0, buf[2], .0001);
    EXPECT_NEAR(-1, buf[3], .0001);
    EXPECT_NEAR(2 * M_PI, phase, .0001);
}

TEST(Method, Modulate) {
    MatrixDSP::Vector<float> buf({1, 1, 1, 1});
    
    float phase = MatrixDSP::modulate(buf, 0.25f, 1.0f, 0.0f);
    EXPECT_EQ(4, buf.size());
    EXPECT_NEAR(0, buf[0], .0001);
    EXPECT_NEAR(1, buf[1], .0001);
    EXPECT_NEAR(0, buf[2], .0001);
    EXPECT_NEAR(-1, buf[3], .0001);
    EXPECT_NEAR(2 * M_PI, phase, .0001);
}

