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
    
        void copyToScratchBuf(std::vector<T> &from);
        void initializeScratchBuf(std::shared_ptr< std::vector<T> > scratch);

    public:
        unsigned numRows;
        unsigned numCols;
        bool transpose;
    
        Matrix2d(unsigned row, unsigned col, std::shared_ptr< std::vector<T> > scratch = nullptr);
        Matrix2d(std::initializer_list< std::initializer_list<T> > data, std::shared_ptr< std::vector<T> > scratch = nullptr);
    
        const T& operator()(unsigned row, unsigned col) const {
            if (!transpose) {
                return vec[row * numCols + col];
            }
            else {
                return vec[col * numCols + row];
            }
        }
    
        RowColIterator<T> rowBegin(int rowNum) {
            return RowColIterator<T>(vec, numRows, numCols, transpose, true, rowNum, false);
        }
        RowColIterator<T> rowEnd(int rowNum) {
            return RowColIterator<T>(vec, numRows, numCols, transpose, true, rowNum, true);
        }
        RowColIterator<T> colBegin(int colNum) {
            return RowColIterator<T>(vec, numRows, numCols, transpose, false, colNum, false);
        }
        RowColIterator<T> colEnd(int colNum) {
            return RowColIterator<T>(vec, numRows, numCols, transpose, false, colNum, true);
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
    transpose = false;
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
        for (auto element : rowInitList) {
            vec[vecIndex++] = element;
        }
    }
    transpose = false;
    initializeScratchBuf(scratch);
}







}

#endif

