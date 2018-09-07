//
//  Matrix2d.h
//  MatrixDSP
//
//  Created by Jim Clay on 9/5/18.
//

#ifndef __MATRIX_DSP_MATRIX2D__
#define __MATRIX_DSP_MATRIX2D__

#include <vector>
#include <initializer_list>
#include "RowColIterator.h"

namespace MatrixDSP {
 
template <class T>
class Matrix2d {
    protected:
        std::vector<T> vec;
        std::shared_ptr< std::vector<T> > scratchBuf;
        unsigned numRows;
        unsigned numCols;
        bool transposed;
    
        void copyToScratchBuf(std::vector<T> &from);
        void initializeScratchBuf(std::shared_ptr< std::vector<T> > scratch);

    public:
    
        Matrix2d(unsigned row, unsigned col, std::shared_ptr< std::vector<T> > scratch = nullptr);
        Matrix2d(std::initializer_list< std::initializer_list<T> > data, std::shared_ptr< std::vector<T> > scratch = nullptr);
    
        const T& operator()(unsigned row, unsigned col) const {
            if (!transposed) {
                return vec[row * numCols + col];
            }
            else {
                return vec[col * numCols + row];
            }
        }
    
        unsigned getRows(void) {
            if (!transposed) {
                return numRows;
            }
            return numCols;
        }
        unsigned getCols(void)  {
            if (!transposed) {
                return numCols;
            }
            return numRows;
        }
    
        Matrix2d & transpose(void) {
            transposed = not transposed;
            return *this;
        }
    
        void checkAddr(unsigned row, unsigned col) {
            if (!transposed) {
                assert(row < numRows);
                assert(col < numCols);
            }
            else {
                assert(row < numCols);
                assert(col < numRows);
            }
        }
    
        RowColIterator<T> rowBegin(int rowNum) {
            checkAddr(rowNum, 0);
            return RowColIterator<T>(vec, numRows, numCols, transposed, true, rowNum, false);
        }
        RowColIterator<T> rowEnd(int rowNum) {
            checkAddr(rowNum, 0);
            return RowColIterator<T>(vec, numRows, numCols, transposed, true, rowNum, true);
        }
        RowColIterator<T> colBegin(int colNum) {
            checkAddr(0, colNum);
            return RowColIterator<T>(vec, numRows, numCols, transposed, false, colNum, false);
        }
        RowColIterator<T> colEnd(int colNum) {
            checkAddr(0, colNum);
            return RowColIterator<T>(vec, numRows, numCols, transposed, false, colNum, true);
        }
    
    
};
    

template <class T>
void Matrix2d<T>::copyToScratchBuf(std::vector<T> &from)
{
    scratchBuf->resize(from.size());
    for (unsigned index=0; index<from.size(); index++) {
        (*scratchBuf)[index] = from[index];
    }
}

template <class T>
void Matrix2d<T>::initializeScratchBuf(std::shared_ptr< std::vector<T> > scratch)
{
    if (scratch == nullptr) {
        scratchBuf = std::shared_ptr< std::vector<T> >(new std::vector<T>);
    }
    else {
        scratchBuf = scratch;
    }
}

template <class T>
Matrix2d<T>::Matrix2d(unsigned row, unsigned col, std::shared_ptr< std::vector<T> > scratch)
{
    vec.resize(row * col);
    numRows = row;
    numCols = col;
    transposed = false;
    initializeScratchBuf(scratch);
}

template <class T>
Matrix2d<T>::Matrix2d(std::initializer_list< std::initializer_list<T> > initVals, std::shared_ptr< std::vector<T> > scratch)
{
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
    transposed = false;
    initializeScratchBuf(scratch);
}







}

#endif

