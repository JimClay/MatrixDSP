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
#include "RowColIterator.h"

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
    /*
    void actuallyDoTranspose() {
        if (!transposed) {
            return;
        }
        
        *scratchBuf = vec;
        unsigned newNumRows = numCols;
        unsigned newNumCols = numRows;
        for (unsigned from=0, row=0; row<newNumRows; row++) {
            for (unsigned col=0; col<newNumCols; col++, from++) {
                vec[row*newNumRows + col] = (*scratchBuf)[from];
            }
        }
        numRows = newNumRows;
        numCols = newNumCols;
        transposed = false;
    }*/

public:
    typedef std::pair<unsigned, unsigned> size_type;
    
    /*****************************************************************************************
                                    Constructors
    *****************************************************************************************/
    Matrix2d(unsigned row, unsigned col, std::shared_ptr< std::vector<T> > scratch = nullptr) {
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
    Matrix2d<T> & operator+=(Matrix2d<U> &rhs) {
        assert(size() == rhs.size());
        
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] += rhs[index];
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
    Matrix2d<T> & operator-=(Matrix2d<U> &rhs) {
        assert(size() == rhs.size());
        
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] -= rhs[index];
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
    size_type size() {return std::make_pair(getRows(), getCols());}
    
    unsigned getRows(void) const {return numRows;}
    unsigned getCols(void) const {return numCols;}

    Matrix2d & transpose(void) {
        *scratchBuf = vec;
        unsigned newNumRows = numCols;
        unsigned newNumCols = numRows;
        for (unsigned from=0, col=0; col<newNumCols; col++) {
            for (unsigned row=0; row<newNumRows; row++, from++) {
                vec[row*newNumCols + col] = (*scratchBuf)[from];
            }
        }
        numRows = newNumRows;
        numCols = newNumCols;
        return *this;
    }

    RowColIterator<T> rowBegin(int rowNum) {
        checkAddr(rowNum, 0);
        return RowColIterator<T>(vec, numRows, numCols, false, true, rowNum, false);
    }
    RowColIterator<T> rowEnd(int rowNum) {
        checkAddr(rowNum, 0);
        return RowColIterator<T>(vec, numRows, numCols, false, true, rowNum, true);
    }
    RowColIterator<T> colBegin(int colNum) {
        checkAddr(0, colNum);
        return RowColIterator<T>(vec, numRows, numCols, false, false, colNum, false);
    }
    RowColIterator<T> colEnd(int colNum) {
        checkAddr(0, colNum);
        return RowColIterator<T>(vec, numRows, numCols, false, false, colNum, true);
    }
};

}

#endif

