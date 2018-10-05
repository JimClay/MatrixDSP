//
//  Matrix2dIterator.h
//  MatrixDSP
//
//  Created by Jim Clay on 9/6/18.
//

#ifndef Matrix2dIterator_h
#define Matrix2dIterator_h

#include <vector>
#include <cassert>

namespace MatrixDSP {

template<typename T>
class Matrix2dIterator {
    private:
        typename std::vector<T>::iterator iterator;
		int rowIncrement;
		int colIncrement;
		int entireRowIncrement;
		int row;
		int col;
		int numRows;
		int numCols;
    
	protected:
		int serialLoc() const {return row * numCols + col;}

    public:
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::random_access_iterator_tag iterator_category;
    
        Matrix2dIterator(typename std::vector<T> &vec, unsigned rows, unsigned cols, bool end = false, bool traverseRowsFirst = false) {
            if (traverseRowsFirst) {
				numRows = rows;
				numCols = cols;
				rowIncrement = 1;
				colIncrement = 1;
				entireRowIncrement = numCols;
            }
            else {
				// We're going to traverse columns first.  In order to avoid a bunch of "if" statements in the iterator methods to find out if we're
				// traversing rows or columns first, we're going to pretend that we always traverse rows first, only the increments that we use will
				// change.  Thus, the number of cols becomes "numRows".  It's like we're transposed.
				numRows = cols;
				numCols = rows;
				colIncrement = cols;
				rowIncrement = 1 - (rows - 1) * cols;
				entireRowIncrement = 1;
            }

			if (end) {
				iterator = vec.end();
				if (traverseRowsFirst) {
					row = numRows;
					col = 0;
				}
				else {
					row = numRows;
					col = 0;
				}
			}
			else {
				iterator = vec.begin();
				row = 0;
				col = 0;
			}
        }

		Matrix2dIterator(const Matrix2dIterator<T> &otherIterator) {
			*this = otherIterator;
		}

        Matrix2dIterator<T> &operator=(const Matrix2dIterator<T> &otherIterator) {
			iterator = otherIterator.iterator;
			rowIncrement = otherIterator.rowIncrement;
			colIncrement = otherIterator.colIncrement;
			entireRowIncrement = otherIterator.entireRowIncrement;
			row = otherIterator.row;
			col = otherIterator.col;
			numRows = otherIterator.numRows;
			numCols = otherIterator.numCols;
            return *this;
        }

        T &operator*() const {
            return *iterator;
        }

        T *operator->() const {
            return &(*iterator);
        }

        Matrix2dIterator<T> &operator++() {
			//printf("## pos = %d %d; size = %d %d; inc = %d %d %d; ptr = 0x%X\n", row, col, numRows, numCols, rowIncrement, colIncrement, entireRowIncrement, (unsigned) &(*iterator));
			if (col < numCols - 1) {
				col++;
				iterator += colIncrement;
			}
			else {
				col = 0;
				row++;
				iterator += rowIncrement;
			}
            return *this;
        }

        Matrix2dIterator<T> operator++(int) {
            Matrix2dIterator<T>  result(*this);  // get a copy for return so this can be used unaltered in the expression
            // Now implement the current object.
            ++(*this);
            // Returned the saved copy.
            return result;
        }
    
        Matrix2dIterator<T> &operator--() {
			if (col > 0) {
				col--;
				iterator -= colIncrement;
			}
			else {
				col = numCols - 1;
				row--;
				iterator -= rowIncrement;
			}
			return *this;
        }

        Matrix2dIterator<T> operator--(int) {
            Matrix2dIterator<T>  result(*this);  // get a copy for return so this can be used unaltered in the expression
            // Now implement the current object.
            --(*this);
            // Returned the saved copy.
            return result;
        }
    
        Matrix2dIterator<T> & operator+=(const difference_type &rhs) {
			assert(rhs > 0);

			difference_type diff = rhs;
			while (diff >= numCols) {
				iterator += entireRowIncrement;
				row++;
				diff -= numCols;
			}
			for (; diff > 0; diff--) {
				++(*this);
			}
            return *this;
        }

        Matrix2dIterator<T> & operator-=(const difference_type &rhs) {
			assert(rhs > 0);

			difference_type diff = rhs;
			while (diff >= numCols) {
				iterator -= entireRowIncrement;
				row--;
				diff -= numCols;
			}
			for (; diff > 0; diff--) {
				--(*this);
			}
			return *this;
        }
    
        difference_type operator-(const Matrix2dIterator<T>& rhs) const {
			difference_type dist = serialLoc() - rhs.serialLoc();
            return dist;
        }

		bool operator==(const Matrix2dIterator<T>& rhs) const { return (row == rhs.row) && (col == rhs.col); }
		bool operator!=(const Matrix2dIterator<T>& rhs) const { return (row != rhs.row) || (col != rhs.col); }
		bool operator<(const Matrix2dIterator<T>& rhs) const { return serialLoc() < rhs.serialLoc(); }
		bool operator>(const Matrix2dIterator<T>& rhs) const { return serialLoc() > rhs.serialLoc(); }
		bool operator<=(const Matrix2dIterator<T>& rhs) const { return serialLoc() <= rhs.serialLoc(); }
		bool operator>=(const Matrix2dIterator<T>& rhs) const { return serialLoc() >= rhs.serialLoc(); }
    
        T& operator[](unsigned index) {
			Matrix2dIterator<T> tempIt(*this);
			tempIt += index;
			return *tempIt;
		}
        const T& operator[](unsigned index) const {
			Matrix2dIterator<T> tempIt(*this);
			tempIt += index;
			return *tempIt;
		}
};

template <class T>
Matrix2dIterator<T> operator+(Matrix2dIterator<T> it, const typename Matrix2dIterator<T>::difference_type n) {
    it += n;
    return it;
}

template <class T>
Matrix2dIterator<T> operator+(typename Matrix2dIterator<T>::difference_type n, const Matrix2dIterator<T>& it) {
    Matrix2dIterator<T> localIt = it;
    localIt += n;
    return localIt;
}

template <class T>
Matrix2dIterator<T> operator-(Matrix2dIterator<T> it, const typename Matrix2dIterator<T>::difference_type n) {
    it -= n;
    return it;
}

  
}


#endif /* Matrix2dIterator_h */
