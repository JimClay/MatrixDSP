//
//  Matrix2d.h
//  MatrixDSP
//
//  Created by Jim Clay on 9/5/18.
//

#ifndef __MATRIX_DSP_MATRIX2D__
#define __MATRIX_DSP_MATRIX2D__

#include <vector>
#include <memory>
#include <initializer_list>
#include <cassert>
#include <utility>
#include "RowColIterator.h"
#include "Matrix2dIterator.h"
#include "Vector.h"


namespace MatrixDSP {
 
template <class T>
class Matrix2d {
protected:
    std::vector<T> vec;
    std::shared_ptr< std::vector<T> > scratchBuf;
    unsigned numRows;
    unsigned numCols;

    void copyToScratchBuf(std::vector<T> &from) {
        scratchBuf->resize(from.size());
        for (unsigned index=0; index<from.size(); index++) {
            (*scratchBuf)[index] = from[index];
        }
    }

    void initializeScratchBuf(std::shared_ptr< std::vector<T> > scratch) {
        if (scratch == nullptr) {
            scratchBuf = std::shared_ptr< std::vector<T> >(new std::vector<T>);
        }
        else {
            scratchBuf = scratch;
        }
    }

    void checkAddr(unsigned row, unsigned col) {
        assert(row < numRows);
        assert(col < numCols);
    }
    
    void doTranspose(const std::vector<T> &input) {
        unsigned newNumRows = numCols;
        unsigned newNumCols = numRows;
        for (unsigned from=0, col=0; col<newNumCols; col++) {
            for (unsigned row=0; row<newNumRows; row++, from++) {
                vec[row*newNumCols + col] = input[from];
            }
        }
        numRows = newNumRows;
        numCols = newNumCols;
    }

	void doReshape(std::vector<T> &input, unsigned fromRows, unsigned fromCols, unsigned toRows, unsigned toCols) {
		Matrix2dIterator<T> itFrom = Matrix2dIterator<T>(input, fromRows, fromCols, false, false);
		Matrix2dIterator<T> itEnd = Matrix2dIterator<T>(input, fromRows, fromCols, true, false);
		Matrix2dIterator<T> itTo = Matrix2dIterator<T>(vec, toRows, toCols, false, false);
		for (; itFrom != itEnd; ++itFrom, ++itTo) {
			*itTo = *itFrom;
		}
		numRows = toRows;
		numCols = toCols;
	}

public:
    typedef std::pair<unsigned, unsigned> size_type;
    
    /*****************************************************************************************
                                    Constructors
    *****************************************************************************************/
    Matrix2d(unsigned row = 0, unsigned col = 0, std::shared_ptr< std::vector<T> > scratch = nullptr) {
        vec.resize(row * col);
        numRows = row;
        numCols = col;
        initializeScratchBuf(scratch);
    }

    Matrix2d(std::initializer_list< std::initializer_list<T> > initVals, std::shared_ptr< std::vector<T> > scratch = nullptr) {
        numRows = initVals.size();
        assert(numRows > 0);
        numCols = initVals.begin()->size();
        assert(numCols > 0);
        vec.resize(numRows * numCols);
        
        unsigned vecIndex = 0;
        for (auto rowInitList : initVals) {
            assert(rowInitList.size() == numCols);
            for (auto element : rowInitList) {
                vec[vecIndex++] = element;
            }
        }
        initializeScratchBuf(scratch);
    }

    /**
     * \brief Virtual destructor.
     */
    virtual ~Matrix2d() = default;

    /*****************************************************************************************
                                        Operators
    *****************************************************************************************/
    T& operator()(unsigned row, unsigned col) {return vec[row * numCols + col];}

    const T& operator()(unsigned row, unsigned col) const {return vec[row * numCols + col];}

    /**
     * \brief Assignment operator.
     */
    Matrix2d<T>& operator=(const Matrix2d<T>& rhs) {
        vec = rhs.vec;
        scratchBuf = rhs.scratchBuf;
        numRows = rhs.numRows;
        numCols = rhs.numCols;
        return *this;
    }
    
    /**
     * \brief Unary minus (negation) operator.
     */
    Matrix2d<T> & operator-() {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] = -vec[index];
        }
        return *this;
    }
    
    /**
     * \brief Add Buffer/Assignment operator.
     */
    template <class U>
    Matrix2d<T> & operator+=(const Matrix2d<U> &rhs) {
        assert(size() == rhs.size());
        
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] += rhs.vec[index];
        }
        return *this;
    }
    
    /**
     * \brief Add Scalar/Assignment operator.
     */
    Matrix2d<T> & operator+=(const T &rhs) {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] += rhs;
        }
        return *this;
    }
    
    /**
     * \brief Subtract Buffer/Assignment operator.
     */
    template <class U>
    Matrix2d<T> & operator-=(const Matrix2d<U> &rhs) {
        assert(size() == rhs.size());
        
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] -= rhs.vec[index];
        }
        return *this;
    }
    
    /**
     * \brief Subtract Scalar/Assignment operator.
     */
    Matrix2d<T> & operator-=(const T &rhs) {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] -= rhs;
        }
        return *this;
    }
    
    /**
     * \brief Multiply Scalar/Assignment operator.
     */
    Matrix2d<T> & operator*=(const T &rhs) {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] *= rhs;
        }
        return *this;
    }

    /**
     * \brief Divide Scalar/Assignment operator.
     */
    Matrix2d<T> & operator/=(const T &rhs) {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] /= rhs;
        }
        return *this;
    }
    
    /*****************************************************************************************
                                            Methods
    *****************************************************************************************/
    size_type size() const {return std::make_pair(getRows(), getCols());}
    
    unsigned getRows(void) const {return numRows;}
    unsigned getCols(void) const {return numCols;}

	Matrix2dIterator<T> begin(bool horizontalFirst = false) {return Matrix2dIterator<T>(vec, numRows, numCols, false, horizontalFirst);}
	Matrix2dIterator<T> end(bool horizontalFirst = false) {return Matrix2dIterator<T>(vec, numRows, numCols, true, horizontalFirst);}

    Matrix2d<T> & transpose(void) {
        *scratchBuf = vec;
        doTranspose(*scratchBuf);
        return *this;
    }

    Matrix2d<T> & transpose(const Matrix2d<T> input) {
        numRows = input.numRows;
        numCols = input.numCols;
        vec.resize(input.vec.size());
        doTranspose(input.vec);
        return *this;
    }

    RowColIterator<T> rowBegin(int rowNum) {
        checkAddr(rowNum, 0);
        return RowColIterator<T>(vec, numRows, numCols, true, rowNum, false);
    }
    RowColIterator<T> rowEnd(int rowNum) {
        checkAddr(rowNum, 0);
        return RowColIterator<T>(vec, numRows, numCols, true, rowNum, true);
    }
    RowColIterator<T> colBegin(int colNum) {
        checkAddr(0, colNum);
        return RowColIterator<T>(vec, numRows, numCols, false, colNum, false);
    }
    RowColIterator<T> colEnd(int colNum) {
        checkAddr(0, colNum);
        return RowColIterator<T>(vec, numRows, numCols, false, colNum, true);
    }

	Matrix2d<T> & resize(unsigned rows, unsigned cols, T val = 0) {
		unsigned minRows = std::min(rows, numRows);
		if (cols < numCols) {
			for (unsigned row = 1; row < minRows; row++) {
				for (unsigned to = row * cols, from = row * numCols; to < row * cols + cols; to++, from++) {
					vec[to] = vec[from];
				}
			}
			vec.resize(minRows * cols);
		}
		else if (cols > numCols) {
			vec.resize(minRows * cols);
			unsigned to = minRows * cols - 1;
			unsigned from = minRows * numCols - 1;
			unsigned colDiff = cols - numCols;
			for (unsigned row = minRows - 1; row > 0; row--) {
				for (unsigned index=0; index<colDiff; to--, index++) {
					vec[to] = val;
				}
				for (unsigned index = 0; index < numCols; index++, to--, from--) {
					vec[to] = vec[from];
				}
			}
			for (unsigned index = 0; index < colDiff; to--, index++) { // Zero out the end of the first row
				vec[to] = val;
			}
		}
		vec.resize(rows * cols, val);
		numRows = rows;
		numCols = cols;
		return *this;
	}

	Matrix2d<T> & reshape(unsigned rows, unsigned cols) {
		assert(rows * cols == numRows * numCols);
		*scratchBuf = vec;
		doReshape(*scratchBuf, numRows, numCols, rows, cols);
		return *this;
	}

	Matrix2d<T> & reshape(Matrix2d<T> & mat, unsigned rows, unsigned cols) {
		assert(rows * cols == mat.numRows * mat.numCols);
		doReshape(mat.vec, mat.numRows, mat.numCols, rows, cols);
		return *this;
	}

	Matrix2d<T> & appendRow(Vector<T> & appendVec) {
		assert(appendVec.size() == numCols);

		vec.reserve(vec.size() + appendVec.size());
		vec.insert(vec.end(), appendVec.begin(), appendVec.end());
		numRows++;
		return *this;
	}

	Matrix2d<T> & appendRows(Matrix2d<T> & appendMat) {
		assert(appendMat.getCols() == numCols);

		vec.reserve(vec.size() + appendMat.getRows() * appendMat.getCols());
		vec.insert(vec.end(), appendMat.begin(true), appendMat.end(true));
		numRows += appendMat.getRows();
		return *this;
	}

	Matrix2d<T> & appendCol(Vector<T> & appendVec) {
		assert(appendVec.size() == numRows);

		vec.resize(vec.size() + appendVec.size());
		for (unsigned from = numRows * numCols - 1, to = numRows * (numCols + 1) - 1, row = numRows - 1; row > 0; row--) {
			vec[to--] = appendVec[row];
			for (unsigned col = 0; col < numCols; col++) {
				vec[to--] = vec[from--];
			}
		}
		vec[numCols] = appendVec[0];
		numCols++;
		return *this;
	}

	Matrix2d<T> & appendCols(Matrix2d<T> & appendMat) {
		assert(appendMat.getRows() == numRows);

		vec.resize(vec.size() + appendMat.getRows() * appendMat.getCols());
		unsigned from = numRows * numCols - 1;
		unsigned to = numRows * (numCols + appendMat.getCols()) - 1;
		unsigned fromAppend = appendMat.getRows() * appendMat.getCols() - 1;
		for (unsigned row = numRows - 1; row > 0; row--) {
			for (unsigned col = 0; col < appendMat.getCols(); col++) {
				vec[to--] = appendMat.vec[fromAppend--];
			}
			for (unsigned col = 0; col < numCols; col++) {
				vec[to--] = vec[from--];
			}
		}
		for (unsigned col = 0; col < appendMat.getCols(); col++) {
			vec[to--] = appendMat.vec[fromAppend--];
		}
		numCols += appendMat.getCols();
		return *this;
	}

	std::vector< std::pair<unsigned, unsigned> > find() {
		std::vector< std::pair<unsigned, unsigned> > list(0);
		Matrix2dIterator<T> it = this->begin(true);
		Matrix2dIterator<T> itEnd = this->end(true);
		for (; it != itEnd; ++it) {
			if (*it) {
				list.push_back(std::make_pair(it.getRow(), it.getCol()));
			}
		}
		return list;
	}
};

template <class T, class U>
Matrix2d<T> operator+(Matrix2d<T> lhs, const Matrix2d<U>& rhs)
{
	lhs += rhs;
	return lhs;
}

template <class T>
Matrix2d<T> operator+(Matrix2d<T> lhs, const T& rhs)
{
	lhs += rhs;
	return lhs;
}

template <class T, class U>
Matrix2d<T> operator-(Matrix2d<T> lhs, const Matrix2d<U>& rhs)
{
	lhs -= rhs;
	return lhs;
}

template <class T>
Matrix2d<T> operator-(Matrix2d<T> lhs, const T& rhs)
{
	lhs -= rhs;
	return lhs;
}

template <class T>
Matrix2d<T> operator*(Matrix2d<T> lhs, const T& rhs)
{
	lhs *= rhs;
	return lhs;
}

template <class T>
Matrix2d<T> operator/(Matrix2d<T> lhs, const T& rhs)
{
	lhs /= rhs;
	return lhs;
}

template <class T>
Matrix2d<T> operator==(Matrix2d<T> lhs, const T& rhs)
{
	for (auto it = lhs.begin(true); it != lhs.end(true); ++it) {
		*it = (T)(*it == rhs);
	}
	return lhs;
}

template <class T>
Matrix2d<T> operator!=(Matrix2d<T> lhs, const T& rhs)
{
	for (auto it = lhs.begin(true); it != lhs.end(true); ++it) {
		*it = (T)(*it != rhs);
	}
	return lhs;
}

template <class T>
Matrix2d<T> operator<=(Matrix2d<T> lhs, const T& rhs)
{
	for (auto it = lhs.begin(true); it != lhs.end(true); ++it) {
		*it = (T)(*it <= rhs);
	}
	return lhs;
}

template <class T>
Matrix2d<T> operator<(Matrix2d<T> lhs, const T& rhs)
{
	for (auto it = lhs.begin(true); it != lhs.end(true); ++it) {
		*it = (T)(*it < rhs);
	}
	return lhs;
}

template <class T>
Matrix2d<T> operator>=(Matrix2d<T> lhs, const T& rhs)
{
	for (auto it = lhs.begin(true); it != lhs.end(true); ++it) {
		*it = (T)(*it >= rhs);
	}
	return lhs;
}

template <class T>
Matrix2d<T> operator>(Matrix2d<T> lhs, const T& rhs)
{
	for (auto it = lhs.begin(true); it != lhs.end(true); ++it) {
		*it = (T)(*it > rhs);
	}
	return lhs;
}

template <class T>
Matrix2d<T> & transpose(Matrix2d<T> & mat) {return mat.transpose();}

template <class T>
Matrix2d<T> & transpose(const Matrix2d<T> & input, Matrix2d<T> & output) {return output.transpose(input);}

template <class T>
Matrix2d<T> & resize(Matrix2d<T> & mat, unsigned rows, unsigned cols, T val = 0) {
	return mat.resize(rows, cols, val);
}

template <class T>
Matrix2d<T> & reshape(Matrix2d<T> & fromMat, Matrix2d<T> & toMat, unsigned rows, unsigned cols) {
	return toMat.reshape(fromMat, rows, cols);
}

template <class T>
Matrix2d<T> & reshape(Matrix2d<T> & mat, unsigned rows, unsigned cols) {
	return mat.reshape(rows, cols);
}

}

#endif

