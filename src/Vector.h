//
//  Matrix.cpp
//  MatrixDSP
//
//  Created by Jim Clay on 9/1/18.
//  Copyright © 2018 Jim Clay. All rights reserved.
//

#ifndef __MATRIX_DSP_VECTOR__
#define __MATRIX_DSP_VECTOR__

//#include <stdio.h>
#include <vector>
#include <memory>
#include <initializer_list>
#include <cmath>
#include <cassert>

namespace MatrixDSP {
 
template <class T>
class Vector {

protected:
    std::shared_ptr< std::vector<T> > scratchBuf;
    
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

public:
    std::vector<T> vec;
    bool rowVector;
    
    /*****************************************************************************************
                                        Constructors
    *****************************************************************************************/
    /**
     * \brief Basic constructor.
     *
     * Just sets the size of \ref vec and the pointer to the scratch buffer, if one is provided.
     * \param len Length of \ref vec.
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     */
    Vector<T>(uint32_t len = 0, bool rowVec = false, std::shared_ptr< std::vector<T> > scratch = nullptr) {
        vec.resize(len);
        rowVector = rowVec;
        initializeScratchBuf(scratch);
    }
    
    /**
     * \brief Vector constructor.
     *
     * Sets vec equal to the input "data" parameter and sets the pointer to the scratch buffer,
     *      if one is provided.
     * \param data Vector that \ref vec will be set equal to.
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     */
    Vector<T>(std::vector<T> *data, bool rowVec = false, std::shared_ptr< std::vector<T> > scratch = nullptr) {
        vec = *data;
        rowVector = rowVec;
        initializeScratchBuf(scratch);
    }
    
    /**
     * \brief Array constructor.
     *
     * Sets vec equal to the input "data" array and sets the pointer to the scratch buffer,
     *      if one is provided.
     * \param data Array that \ref vec will be set equal to.
     * \param dataLen Length of "data".
     * \param scratch Pointer to a scratch buffer.  The scratch buffer can be shared by multiple
     *      objects (in fact, I recommend it), but if there are multiple threads then it should
     *      be shared only by objects that are accessed by a single thread.  Objects in other
     *      threads should have a separate scratch buffer.  If no scratch buffer is provided
     *      then one will be created in methods that require one and destroyed when the method
     *      returns.
     */
    template <class U>
        Vector<T>(U *data, uint32_t dataLen, bool rowVec = false, std::shared_ptr< std::vector<T> > scratch = nullptr) {
        vec.resize(dataLen);
        for (uint32_t index=0; index<dataLen; index++) {
            vec[index] = (T) data[index];
        }
        rowVector = rowVec;
        initializeScratchBuf(scratch);
    }
    
    Vector<T>(std::initializer_list<T> initVals, bool rowVec = false, std::shared_ptr< std::vector<T> > scratch = nullptr) : vec(initVals) {
        rowVector = rowVec;
        initializeScratchBuf(scratch);
    }
    
    /**
     * \brief Copy constructor.
     */
    Vector<T>(const Vector<T>& other) {*this = other;}
    
    /**
     * \brief Virtual destructor.
     */
    virtual ~Vector() = default;
    
    std::shared_ptr< std::vector<T> > getScratchBuf(void) const {return scratchBuf;}

    /*****************************************************************************************
                                            Operators
    *****************************************************************************************/
    /**
     * \brief Index assignment operator.
     */
    T& operator[](unsigned index) {return vec[index];};
    
    /**
     * \brief Index operator.
     */
    const T& operator[](unsigned index) const {return vec[index];}
    
    T& operator()(unsigned index) {return vec[index];}

    const T& operator()(unsigned index) const {return vec[index];}
    
    /**
     * \brief Assignment operator.
     */
    Vector<T>& operator=(const Vector<T>& rhs) {
        vec.resize(rhs.size());
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] = rhs[index];
        }
        rowVector = rhs.rowVector;
        scratchBuf = rhs.scratchBuf;
        return *this;
    }
    
    /**
     * \brief Unary minus (negation) operator.
     */
    Vector<T> & operator-() {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] = -vec[index];
        }
        return *this;
    }
    
    /**
     * \brief Add Buffer/Assignment operator.
     */
    template <class U>
    Vector<T> & operator+=(const Vector<U> &rhs) {
        assert(vec.size() == rhs.size());
        
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] += rhs[index];
        }
        return *this;
    }
    
    /**
     * \brief Add Scalar/Assignment operator.
     */
    Vector<T> & operator+=(const T &rhs) {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] += rhs;
        }
        return *this;
    }
    
    /**
     * \brief Subtract Buffer/Assignment operator.
     */
    template <class U>
    Vector<T> & operator-=(const Vector<U> &rhs) {
        assert(vec.size() == rhs.size());
        
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] -= rhs[index];
        }
        return *this;
    }
    
    /**
     * \brief Subtract Scalar/Assignment operator.
     */
    Vector<T> & operator-=(const T &rhs) {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] -= rhs;
        }
        return *this;
    }
    
    /**
     * \brief Multiply Buffer/Assignment operator.
     */
    template <class U>
    Vector<T> & operator*=(const Vector<U> &rhs) {
        assert(vec.size() == rhs.size());
        
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] *= rhs[index];
        }
        return *this;
    }
    
    /**
     * \brief Multiply Scalar/Assignment operator.
     */
    Vector<T> & operator*=(const T &rhs) {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] *= rhs;
        }
        return *this;
    }

    /**
     * \brief Divide Buffer/Assignment operator.
     */
    template <class U>
    Vector<T> & operator/=(const Vector<U> &rhs) {
        assert(vec.size() == rhs.size());
        
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] /= rhs[index];
        }
        return *this;
    }
    
    /**
     * \brief Divide Scalar/Assignment operator.
     */
    Vector<T> & operator/=(const T &rhs) {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] /= rhs;
        }
        return *this;
    }
    
    /*****************************************************************************************
                                            Methods
    *****************************************************************************************/
    /**
     * \brief Returns the size of \ref vec.
     */
    const unsigned size() const {return (const unsigned) vec.size();};
    
	auto begin() { return vec.begin(); }
	auto end() { return vec.end(); }

    std::vector<unsigned> find() const {
		std::vector<unsigned> list(0);
        for (unsigned index=0; index<vec.size(); index++) {
            if (std::abs(vec[index])) {
				list.push_back(index);
            }
        }
        return list;
    }
    
    /**
     * \brief Returns the sum of all the elements in \ref vec.
     */
    T sum() const {
        T vecSum = 0;
        for (T element : vec) {
            vecSum += element;
        }
        return vecSum;
    }

    /**
     * \brief Sets each element of \ref buf equal to its value to the power of "exponent".
     *
     * \param exponent Exponent to use.
     * \return Reference to "this".
     */
    Vector<T> & pow(const T exponent) {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] = std::pow(vec[index], exponent);
        }
        return *this;
    }
    
    /**
     * \brief Returns the mean (average) of the data in \ref buf.
     */
    const T mean() const {
        return sum() / ((T) size());
    }
    
    /**
     * \brief Returns the variance of the data in \ref buf.
     */
    const T var(const bool subset = true) const {
        T squaredSum = 0;
        T vecMean = mean();
        unsigned normalizer = size();
        if (subset) {
            normalizer--;
        }
        
        for (T element : vec) {
            T val = element - vecMean;
            squaredSum += val * val;
        }
        return squaredSum / ((T) normalizer);
    }
    
    /**
     * \brief Returns the standard deviation of the data in \ref buf.
     */
    const T stdDev(const bool subset = true) const {return std::sqrt(this->var(subset));}
    
    /**
     * \brief Returns the median element of \ref buf.
     */
    const T median() {
        assert(vec.size() > 0);
        
        copyToScratchBuf(vec);
        std::sort(scratchBuf->begin(), scratchBuf->end());
        if (this->size() & 1) {
            // Odd number of samples
            return (*scratchBuf)[size()/2];
        }
        else {
            // Even number of samples.  Average the two in the middle.
            unsigned topHalfIndex = size()/2;
            return ((*scratchBuf)[topHalfIndex] + (*scratchBuf)[topHalfIndex-1]) / ((T) 2);
        }
    }
    
    /**
     * \brief Returns the maximum element in \ref buf.
     *
     * \param maxLoc If it isn't equal to nullptr the index of the maximum element
     *      will be returned via this pointer.  If more than one element is equal
     *      to the maximum value the index of the first will be returned.
     *      Defaults to nullptr.
     */
    const T max(unsigned *maxLoc = nullptr) const {
        assert(vec.size() > 0);
        
        T maxVal = vec[0];
        unsigned maxIndex = 0;
        
        for (unsigned index=1; index<vec.size(); index++) {
            if (maxVal < vec[index]) {
                maxVal = vec[index];
                maxIndex = index;
            }
        }
        if (maxLoc != nullptr) {
            *maxLoc = maxIndex;
        }
        return maxVal;
    }
    
    /**
     * \brief Returns the minimum element in \ref buf.
     *
     * \param minLoc If it isn't equal to nullptr the index of the minimum element
     *      will be returned via this pointer.  If more than one element is equal
     *      to the minimum value the index of the first will be returned.
     *      Defaults to nullptr.
     */
    const T min(unsigned *minLoc = nullptr) const {
        assert(vec.size() > 0);
        
        T minVal = vec[0];
        unsigned minIndex = 0;
        
        for (unsigned index=1; index<vec.size(); index++) {
            if (minVal > vec[index]) {
                minVal = vec[index];
                minIndex = index;
            }
        }
        if (minLoc != nullptr) {
            *minLoc = minIndex;
        }
        return minVal;
    }
    
    /**
     * \brief Sets the upper and lower limit of the values in \ref buf.
     *
     * \param val Limiting value for the data in \ref buf.  Any values that
     *      are greater than "val" are made equal to "val", and
     *      any that are less than -val are made equal to -val.
     * \return Reference to "this".
     */
    Vector<T> & saturate(T val) {
        assert(val >= 0);
        
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] = std::min(vec[index], val);
            vec[index] = std::max(vec[index], -val);
        }
        return *this;
    }

    /**
     * \brief Does a "ceil" operation on \ref vec.
     * \return Reference to "this".
     */
    Vector<T> & ceil(void) {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] = std::ceil(vec[index]);
        }
        return *this;
    }

    /**
     * \brief Does a "floor" operation on \ref vec.
     * \return Reference to "this".
     */
    Vector<T> & floor(void) {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] = std::floor(vec[index]);
        }
        return *this;
    }

    /**
     * \brief Does a "round" operation on \ref vec.
     * \return Reference to "this".
     */
    Vector<T> & round(void) {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] = std::round(vec[index]);
        }
        return *this;
    }

    /**
     * \brief Changes the elements of \ref vec to their absolute value.
     *
     * \return Reference to "this".
     */
    Vector<T> & abs() {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] = std::abs(vec[index]);
        }
        return *this;
    }
    
    /**
     * \brief Sets each element of \ref vec to e^(element).
     *
     * \return Reference to "this".
     */
    Vector<T> & exp() {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] = std::exp(vec[index]);
        }
        return *this;
    }
    
    /**
     * \brief Sets each element of \ref vec to the natural log of the element.
     *
     * \return Reference to "this".
     */
    Vector<T> & log() {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] = std::log(vec[index]);
        }
        return *this;
    }
    
    /**
     * \brief Sets each element of \ref vec to the base 10 log of the element.
     *
     * \return Reference to "this".
     */
    Vector<T> & log10() {
        for (unsigned index=0; index<vec.size(); index++) {
            vec[index] = std::log10(vec[index]);
        }
        return *this;
    }

    /**
     * \brief Circular rotation.
     *
     * \param numToShift Number of positions to shift in the circular rotation.  numToShift
     *      can be positive or negative.  If you visualize the 0 index value at the left and
     *      the end of the array at the right, positive numToShift values shift the array to
     *      the left, and negative values shift it to the right.
     * \return Reference to "this".
     */
    Vector<T> & vectorRotate(int numToShift) {
        if (vec.size() <= 1) {
            return *this;
        }
        while (numToShift >= (int) vec.size()) {
            numToShift -= (int) vec.size();
        }
        while (numToShift < 0) {
            numToShift += (int) vec.size();
        }
        
        std::rotate(vec.begin(), vec.begin() + numToShift, vec.end());
        return *this;
    }
    
    /**
     * \brief Reverses the order of the elements in \ref vec.
     *
     * \return Reference to "this".
     */
    Vector<T> & reverse() {
        std::reverse(vec.begin(), vec.end());
        return *this;
    }

    /**
     * \brief Sets the length of \ref vec to "len".
     *
     * \param len The new length for \ref vec.  If len is longer than vec's current size, the
     *      new elements will be set to "val".  If len is less than vec's current size the extra
     *      elements will be cut off and the other elements will remain the same.
     * \param val The value to set any new elements to.  Defaults to 0.
     * \return Reference to "this".
     */
    Vector<T> & resize(unsigned len, T val = (T) 0) {this->vec.resize(len, val); return *this;}
    
    /**
     * \brief Lengthens \ref vec by "len" elements.
     *
     * \param len The number of elements to add to \ref vec.
     * \param val The value to set the new elements to.  Defaults to 0.
     * \return Reference to "this".
     */
    Vector<T> & pad(unsigned len, T val = (T) 0) {this->vec.resize(this->size()+len, val); return *this;}
    
    /**
     * \brief Inserts rate-1 zeros between samples.
     *
     * \param rate Indicates how many zeros should be inserted between samples.
     * \param phase Indicates how many of the zeros should be before the samples (as opposed to
     *      after).  Valid values are 0 to "rate"-1.  Defaults to 0.
     * \return Reference to "this".
     */
    Vector<T> & upsample(int rate, int phase = 0) {
        assert(rate > 0);
        assert(phase >= 0 && phase < rate);
        
        if (rate == 1)
            return *this;

        int originalSize = vec.size();
        vec.resize(originalSize*rate);
        int from, to;
        for (from = originalSize - 1, to = vec.size() - (rate - phase); to > 0; from--, to -= rate) {
            vec[to] = vec[from];
            vec[from] = 0;
        }
        return *this;
    }

    /**
     * \brief Removes rate-1 samples out of every rate samples.
     *
     * \param rate Indicates how many samples should be removed.
     * \param phase Tells the method which sample should be the first to be kept.  Valid values
     *      are 0 to "rate"-1.  Defaults to 0.
     * \return Reference to "this".
     */
    Vector<T> & downsample(int rate, int phase = 0) {
        assert(rate > 0);
        assert(phase >= 0 && phase < rate);
        if (rate == 1)
            return *this;

        int newSize = vec.size() / rate;
        int from, to;
        for (from = phase, to = 0; to < newSize; from += rate, to++) {
            vec[to] = vec[from];
        }
        vec.resize(newSize);
        return *this;
    }
    
    /**
     * \brief Replaces \ref vec with the cumulative sum of the samples in \ref vec.
     *
     * \param initialVal Initializing value for the cumulative sum.  Defaults to zero.
     * \return Reference to "this".
     */
    Vector<T> & cumsum(T initialVal = 0) {
        T sum = initialVal;
        for (unsigned i=0; i<vec.size(); i++) {
            sum += vec[i];
            vec[i] = sum;
        }
        return *this;
    }
    
    /**
     * \brief Replaces \ref vec with the difference between successive samples in vec.
     *
     * \param previousVal The last value in the sample stream before the current contents
     *      of \ref vec.  previousVal allows the resulting vec to be the same size as the
     *      previous vec.  Defaults to nullptr.
     * \return Reference to "this".
     */
    Vector<T> & diff(T *previousVal = nullptr) {
        if (previousVal == nullptr) {
            assert(size() > 1);
            for (unsigned i=0; i<(size()-1); i++) {
                vec[i] = vec[i + 1] - vec[i];
            }
            resize(size()-1);
        }
        else {
            assert(this->size() > 0);
            T nextPreviousVal = vec[size()-1];
            for (unsigned i=size()-1; i>0; i--) {
                vec[i] = vec[i] - vec[i - 1];
            }
            vec[0] = vec[0] - *previousVal;
            *previousVal = nextPreviousVal;
        }
        return *this;
    }
    
    /**
     * \brief Generates a real sinusoid.
     *
     * \param freq The tone frequency.
     * \param sampleFreq The sample frequency.  Defaults to 1 Hz.
     * \param phase The tone's starting phase, in radians.  Defaults to 0.
     * \param numSamples The number of samples to generate.  "0" indicates to generate
     *      this->size() samples.  Defaults to 0.
     * \return The next phase if the tone were to continue.
     */
    T sin(T freq, T sampleFreq = 1.0, T phase = 0.0, unsigned numSamples = 0) {
        assert(sampleFreq > 0.0);
        
        if (numSamples && numSamples != size()) {
            this->resize(numSamples);
        }
        
        T phaseInc = (freq / sampleFreq) * 2 * M_PI;
        for (unsigned i=0; i<size(); i++) {
            vec[i] = std::sin(phase);
            phase += phaseInc;
        }
        return phase;
    }
    
    /**
     * \brief Generates a real cosinusoid.
     *
     * \param freq The tone frequency.
     * \param sampleFreq The sample frequency.  Defaults to 1 Hz.
     * \param phase The tone's starting phase, in radians.  Defaults to 0.
     * \param numSamples The number of samples to generate.  "0" indicates to generate
     *      this->size() samples.  Defaults to 0.
     * \return The next phase if the tone were to continue.
     */
    T cos(T freq, T sampleFreq = 1.0, T phase = 0.0, unsigned numSamples = 0) {
        T sinPhase = this->sin(freq, sampleFreq, phase + ((T) M_PI / 2), numSamples);
        return sinPhase - ((T) M_PI / 2);
    }
    
    /**
     * \brief Modulates the data with a real sinusoid.
     *
     * \param freq The modulating tone frequency.
     * \param sampleFreq The sample frequency of the data.  Defaults to 1 Hz.
     * \param phase The modulating tone's starting phase, in radians.  Defaults to 0.
     * \return The next phase if the tone were to continue.
     */
    T modulate(T freq, T sampleFreq = 1.0, T phase = 0.0) {
        assert(sampleFreq > 0.0);
        
        T phaseInc = (freq / sampleFreq) * 2 * M_PI;
        for (unsigned i=0; i<size(); i++) {
            vec[i] *= std::sin(phase);
            phase += phaseInc;
        }
        return phase;
    }
};


template <class T, class U>
inline Vector<T> operator+(Vector<T> lhs, const Vector<U>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
inline Vector<T> operator+(Vector<T> lhs, const T& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T, class U>
inline Vector<T> operator-(Vector<T> lhs, const Vector<U>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T>
inline Vector<T> operator-(Vector<T> lhs, const T& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T, class U>
inline Vector<T> operator*(Vector<T> lhs, const Vector<U>& rhs)
{
    lhs *= rhs;
    return lhs;
}

template <class T>
inline Vector<T> operator*(Vector<T> lhs, const T& rhs)
{
    lhs *= rhs;
    return lhs;
}

template <class T, class U>
inline Vector<T> operator/(Vector<T> lhs, const Vector<U>& rhs)
{
    lhs /= rhs;
    return lhs;
}

template <class T>
inline Vector<T> operator/(Vector<T> lhs, const T& rhs)
{
    lhs /= rhs;
    return lhs;
}

template <class T>
inline Vector<T> operator==(Vector<T> lhs, const T& rhs) {
	for (unsigned index = 0; index < lhs.size(); index++) {
		lhs[index] = (T)(lhs[index] == rhs);
	}
	return lhs;
}

template <class T>
inline Vector<T> operator!=(Vector<T> lhs, const T& rhs) {
	for (unsigned index = 0; index < lhs.size(); index++) {
		lhs[index] = (T)(lhs[index] != rhs);
	}
	return lhs;
}

template <class T>
Vector<T> operator<(Vector<T> lhs, const T& rhs) {
	for (unsigned index = 0; index < lhs.size(); index++) {
		lhs[index] = (T)(lhs[index] < rhs);
	}
	return lhs;
}

template <class T>
Vector<T> operator<=(Vector<T> lhs, const T& rhs) {
	for (unsigned index = 0; index < lhs.size(); index++) {
		lhs[index] = (T)(lhs[index] <= rhs);
	}
	return lhs;
}

template <class T>
Vector<T> operator>(Vector<T> lhs, const T& rhs) {
	for (unsigned index = 0; index < lhs.size(); index++) {
		lhs[index] = (T)(lhs[index] > rhs);
	}
	return lhs;
}

template <class T>
Vector<T> operator>=(Vector<T> lhs, const T& rhs) {
	for (unsigned index = 0; index < lhs.size(); index++) {
		lhs[index] = (T)(lhs[index] >= rhs);
	}
	return lhs;
}

template <class T>
const unsigned size(Vector<T> &vec) {return vec.size();};

template <class T>
const unsigned length(Vector<T> &vec) {return vec.size();};

/**
 * \brief Finds the first instance of "val" in \ref vec.
 *
 * \param val The value to look for in \ref vec.
 * \return Index of first instance of "val".  If there aren't any elements equal to "val"
 *      it returns -1.
 */
template <class T>
std::vector<unsigned> find(Vector<T> &vec) {return vec.find();}

/**
 * \brief Returns the sum of all the elements in \ref vec.
 */
template <class T>
T sum(Vector<T> &vec) {return vec.sum();}

/**
 * \brief Sets each element of \ref buf equal to its value to the power of "exponent".
 *
 * \param exponent Exponent to use.
 * \return Reference to "this".
 */
template <class T>
Vector<T> & pow(Vector<T> &vec, const T exponent) {return vec.pow(exponent);}

/**
 * \brief Returns the mean (average) of the data in \ref buf.
 */
template <class T>
const T mean(Vector<T> &vec) {return vec.mean();}

/**
 * \brief Returns the variance of the data in \ref buf.
 */
template <class T>
const T var(Vector<T> &vec, const bool subset = true) {return vec.var(subset);}

/**
 * \brief Returns the standard deviation of the data in \ref buf.
 */
template <class T>
const T stdDev(Vector<T> &vec, const bool subset = true) {return vec.stdDev(subset);}

/**
 * \brief Returns the median element of \ref buf.
 */
template <class T>
const T median(Vector<T> &vec) {return vec.median();}

/**
 * \brief Returns the maximum element in \ref buf.
 *
 * \param maxLoc If it isn't equal to nullptr the index of the maximum element
 *      will be returned via this pointer.  If more than one element is equal
 *      to the maximum value the index of the first will be returned.
 *      Defaults to nullptr.
 */
template <class T>
const T max(Vector<T> &vec, unsigned *maxLoc = nullptr) {return vec.max(maxLoc);}

/**
 * \brief Returns the minimum element in \ref buf.
 *
 * \param minLoc If it isn't equal to nullptr the index of the minimum element
 *      will be returned via this pointer.  If more than one element is equal
 *      to the minimum value the index of the first will be returned.
 *      Defaults to nullptr.
 */
template <class T>
const T min(Vector<T> &vec, unsigned *minLoc = nullptr) {return vec.min(minLoc);}

/**
 * \brief Sets the upper and lower limit of the values in \ref buf.
 *
 * \param val Limiting value for the data in \ref buf.  Any values that
 *      are greater than "val" are made equal to "val", and
 *      any that are less than -val are made equal to -val.
 * \return Reference to "this".
 */
template <class T>
Vector<T> & saturate(Vector<T> &vec, T val) {return vec.saturate(val);}

/**
 * \brief Does a "ceil" operation on \ref vec.
 * \return Reference to "this".
 */
template <class T>
Vector<T> & ceil(Vector<T> &vec) {return vec.ceil();}

/**
 * \brief Does a "floor" operation on \ref vec.
 * \return Reference to "this".
 */
template <class T>
Vector<T> & floor(Vector<T> &vec) {return vec.floor();}

/**
 * \brief Does a "round" operation on \ref vec.
 * \return Reference to "this".
 */
template <class T>
Vector<T> & round(Vector<T> &vec) {return vec.round();}

/**
 * \brief Changes the elements of \ref vec to their absolute value.
 *
 * \return Reference to "this".
 */
template <class T>
Vector<T> & abs(Vector<T> &vec) {return vec.abs();}

/**
 * \brief Sets each element of \ref vec to e^(element).
 *
 * \return Reference to "this".
 */
template <class T>
Vector<T> & exp(Vector<T> &vec) {return vec.exp();}

/**
 * \brief Sets each element of \ref vec to the natural log of the element.
 *
 * \return Reference to "this".
 */
template <class T>
Vector<T> & log(Vector<T> &vec) {return vec.log();}

/**
 * \brief Sets each element of \ref vec to the base 10 log of the element.
 *
 * \return Reference to "this".
 */
template <class T>
Vector<T> & log10(Vector<T> &vec) {return vec.log10();}

/**
 * \brief Circular rotation.
 *
 * \param numToShift Number of positions to shift in the circular rotation.  numToShift
 *      can be positive or negative.  If you visualize the 0 index value at the left and
 *      the end of the array at the right, positive numToShift values shift the array to
 *      the left, and negative values shift it to the right.
 * \return Reference to "this".
 */
template <class T>
Vector<T> & vectorRotate(Vector<T> &vec, int numToShift) {return vec.vectorRotate(numToShift);}

/**
 * \brief Reverses the order of the elements in \ref vec.
 *
 * \return Reference to "this".
 */
template <class T>
Vector<T> & reverse(Vector<T> &vec) {return vec.reverse();}

template <class T>
Vector<T> & fliplr(Vector<T> &vec) {
    if (vec.rowVector) {
        return vec.reverse();
    }
    return vec;
}

template <class T>
Vector<T> & flipud(Vector<T> &vec) {
    if (vec.rowVector == false) {
        return vec.reverse();
    }
    return vec;
}

/**
 * \brief Sets the length of \ref vec to "len".
 *
 * \param len The new length for \ref vec.  If len is longer than vec's current size, the
 *      new elements will be set to "val".  If len is less than vec's current size the extra
 *      elements will be cut off and the other elements will remain the same.
 * \param val The value to set any new elements to.  Defaults to 0.
 * \return Reference to "this".
 */
template <class T>
Vector<T> & resize(Vector<T> &vec, unsigned len, T val = (T) 0) {return vec.resize(len, val);}

/**
 * \brief Lengthens \ref vec by "len" elements.
 *
 * \param len The number of elements to add to \ref vec.
 * \param val The value to set the new elements to.  Defaults to 0.
 * \return Reference to "this".
 */
template <class T>
Vector<T> & pad(Vector<T> &vec, unsigned len, T val = (T) 0) {return vec.pad(len, val);}

/**
 * \brief Inserts rate-1 zeros between samples.
 *
 * \param rate Indicates how many zeros should be inserted between samples.
 * \param phase Indicates how many of the zeros should be before the samples (as opposed to
 *      after).  Valid values are 0 to "rate"-1.  Defaults to 0.
 * \return Reference to "this".
 */
template <class T>
Vector<T> & upsample(Vector<T> &vec, int rate, int phase = 0) {return vec.upsample(rate, phase);}

/**
 * \brief Removes rate-1 samples out of every rate samples.
 *
 * \param rate Indicates how many samples should be removed.
 * \param phase Tells the method which sample should be the first to be kept.  Valid values
 *      are 0 to "rate"-1.  Defaults to 0.
 * \return Reference to "this".
 */
template <class T>
Vector<T> & downsample(Vector<T> &vec, int rate, int phase = 0) {return vec.downsample(rate, phase);}

/**
 * \brief Replaces \ref vec with the cumulative sum of the samples in \ref vec.
 *
 * \param initialVal Initializing value for the cumulative sum.  Defaults to zero.
 * \return Reference to "this".
 */
template <class T>
Vector<T> & cumsum(Vector<T> &vec, T initialVal = 0) {return vec.cumsum(initialVal);}

/**
 * \brief Replaces \ref vec with the difference between successive samples in vec.
 *
 * \param previousVal The last value in the sample stream before the current contents
 *      of \ref vec.  previousVal allows the resulting vec to be the same size as the
 *      previous vec.  Defaults to nullptr.
 * \return Reference to "this".
 */
template <class T>
Vector<T> & diff(Vector<T> &vec, T *previousVal = nullptr) {return vec.diff(previousVal);}

/**
 * \brief Generates a real sinusoid.
 *
 * \param freq The tone frequency.
 * \param sampleFreq The sample frequency.  Defaults to 1 Hz.
 * \param phase The tone's starting phase, in radians.  Defaults to 0.
 * \param numSamples The number of samples to generate.  "0" indicates to generate
 *      this->size() samples.  Defaults to 0.
 * \return The next phase if the tone were to continue.
 */
template <class T>
T sin(Vector<T> &vec, T freq, T sampleFreq = 1.0, T phase = 0.0, unsigned numSamples = 0) {return vec.sin(freq, sampleFreq, phase, numSamples);}

/**
 * \brief Generates a real cosinusoid.
 *
 * \param freq The tone frequency.
 * \param sampleFreq The sample frequency.  Defaults to 1 Hz.
 * \param phase The tone's starting phase, in radians.  Defaults to 0.
 * \param numSamples The number of samples to generate.  "0" indicates to generate
 *      this->size() samples.  Defaults to 0.
 * \return The next phase if the tone were to continue.
 */
template <class T>
T cos(Vector<T> &vec, T freq, T sampleFreq = 1.0, T phase = 0.0, unsigned numSamples = 0) {return vec.cos(freq, sampleFreq, phase, numSamples);}

/**
 * \brief Modulates the data with a real sinusoid.
 *
 * \param freq The modulating tone frequency.
 * \param sampleFreq The sample frequency of the data.  Defaults to 1 Hz.
 * \param phase The modulating tone's starting phase, in radians.  Defaults to 0.
 * \return The next phase if the tone were to continue.
 */
template <class T>
T modulate(Vector<T> &vec, T freq, T sampleFreq = 1.0, T phase = 0.0) {return vec.modulate(freq, sampleFreq, phase);}
    
}

#endif

