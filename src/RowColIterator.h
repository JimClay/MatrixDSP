//
//  RowColIterator.h
//  MatrixDSP
//
//  Created by Jim Clay on 9/6/18.
//

#ifndef RowColIterator_h
#define RowColIterator_h

#include <vector>
#include <cassert>

namespace MatrixDSP {

template<typename T>
class RowColIterator {
    private:
        typename std::vector<T>::iterator iterator;
        int increment;
    
    public:
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::random_access_iterator_tag iterator_category;
    
        RowColIterator();

        RowColIterator(typename std::vector<T>::iterator iterator, int inc = 1) : iterator(iterator), increment(inc) { }
    
        RowColIterator(typename std::vector<T> &vec, unsigned numRows, unsigned numCols, bool row, int rowColNum, bool end = false) {
            iterator = vec.begin();
            int numElements;
            if (row) {
                iterator += rowColNum * numCols;
                increment = 1;
                numElements = numCols;
            }
            else {
                iterator += rowColNum;
                increment = numCols;
                numElements = numRows;
            }
            
            if (end) {
                iterator += numElements * increment;
            }
        }

        RowColIterator(const RowColIterator<T> &iterator) : iterator(iterator.iterator), increment(iterator.increment) { }

        RowColIterator<T> &operator=(const RowColIterator<T> &iterator) {
            this->iterator = iterator.iterator;
            this->increment = iterator.increment;
            return *this;
        }

        T &operator*() const {
            return *iterator;
        }

        T *operator->() const {
            return &(*iterator);
        }

        RowColIterator<T> &operator++() {
            iterator += increment;
            return *this;
        }

        RowColIterator<T> operator++(int) {
            RowColIterator<T>  result(*this);  // get a copy for return so this can be used unaltered in the expression
            // Now implement the current object.
            (*this) += increment;
            // Returned the saved copy.
            return result;
        }
    
        RowColIterator<T> &operator--() {
            iterator -= increment;
            return *this;
        }

        RowColIterator<T> operator--(int) {
            RowColIterator<T>  result(*this);  // get a copy for return so this can be used unaltered in the expression
            // Now implement the current object.
            (*this) -= increment;
            // Returned the saved copy.
            return result;
        }
    
        RowColIterator<T> & operator+=(const difference_type &rhs) {
            iterator += rhs * increment;
            return *this;
        }

        RowColIterator<T> & operator-=(const difference_type &rhs) {
            iterator -= rhs * increment;
            return *this;
        }
    
        difference_type operator-(const RowColIterator<T>& rhs) const {
            auto dist = std::distance(rhs.iterator, iterator);
            return dist / increment;
        }

        bool operator==(const RowColIterator<T>& rhs) const {return *iterator == *rhs.iterator;}
        bool operator!=(const RowColIterator<T>& rhs) const {return *iterator != *rhs.iterator;}
        bool operator<(const RowColIterator<T>& rhs) const {return *iterator < *rhs.iterator;}
        bool operator>(const RowColIterator<T>& rhs) const {return *iterator > *rhs.iterator;}
        bool operator<=(const RowColIterator<T>& rhs) const {return *iterator <= *rhs.iterator;}
        bool operator>=(const RowColIterator<T>& rhs) const {return *iterator >= *rhs.iterator;}
    
        T& operator[](unsigned index) {return *(iterator + index * increment);}
        const T& operator[](unsigned index) const {return *(iterator + index * increment);}
};

template <class T>
RowColIterator<T> operator+(RowColIterator<T> it, const typename RowColIterator<T>::difference_type n) {
    it += n;
    return it;
}

template <class T>
RowColIterator<T> operator+(typename RowColIterator<T>::difference_type n, const RowColIterator<T>& it) {
    RowColIterator<T> localIt = it;
    localIt += n;
    return localIt;
}

template <class T>
RowColIterator<T> operator-(RowColIterator<T> it, const typename RowColIterator<T>::difference_type n) {
    it -= n;
    return it;
}


  
}


#endif /* RowColIterator_h */
