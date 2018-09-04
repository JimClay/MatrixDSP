#include "Vector.h"
#include "gtest/gtest.h"

//using namespace NimbleDSP;

bool FloatsEqual(double float1, double float2) {
    double epsilon = .00000001;
    if ((float1 < float2 + epsilon) && (float1 > float2 - epsilon))
        return true;
    return false;
}

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

/*
int main(int argc, char *argv[])
{
	MatrixDSP::Vector<float> vec1(5);
    MatrixDSP::Vector<float> vec2(new std::vector<float>(5));
    float data[] = {1, 2, 3, 4, 5};
    MatrixDSP::Vector<float> vec3(data, 5);
    MatrixDSP::Vector<float> vec4({6, 7, 8, 9, 10});
    
    PrintVector("vec1", vec1);
    PrintVector("vec2", vec2);
    PrintVector("vec3", vec3);
    PrintVector("vec4", vec4);
    //PrintVector("vec1 + vec2", vec1 + vec2);

	return 0;
}
*/
