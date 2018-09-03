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
