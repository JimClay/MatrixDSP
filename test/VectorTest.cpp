#include "Vector.h"

int main(int argc, char *argv[])
{
	MatrixDSP::Vector<float> vec1(5);
    MatrixDSP::Vector<float> vec2(new std::vector<float>(5));

	return 0;
}

