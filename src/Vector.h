//
//  Matrix.cpp
//  MatrixDSP
//
//  Created by Jim Clay on 9/1/18.
//  Copyright © 2018 Jim Clay. All rights reserved.
//

//#include <stdio.h>
#include <vector>
#include <initializer_list>
#include <cmath>

namespace MatrixDSP {
 
template <class T>
class Vector {
    protected:
        std::shared_ptr< std::vector<T> > scratchBuf;
    
        void copyToScratchBuf(std::unique_ptr< std::vector<T> > from);

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
    Vector<T>(uint32_t len = 0, bool rowVec = false, std::shared_ptr< std::vector<T> > scratch = nullptr);
    
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
    Vector<T>(std::vector<T> *data, bool rowVec = false, std::shared_ptr< std::vector<T> > scratch = nullptr);
    
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
    Vector<T>(U *data, uint32_t dataLen, bool rowVec = false, std::shared_ptr< std::vector<T> > scratch = nullptr);
    
    Vector<T>(std::initializer_list<T> initVals, bool rowVec = false, std::shared_ptr< std::vector<T> > scratch = nullptr);
    
    /**
     * \brief Copy constructor.
     */
    Vector<T>(const Vector<T>& other) {*this = other;}
    
    /**
     * \brief Virtual destructor.
     */
    virtual ~Vector() = default;

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
    const T& operator[](unsigned index) const {return vec[index];};
    
    /**
     * \brief Assignment operator.
     */
    Vector<T>& operator=(const Vector<T>& rhs);
    
    /**
     * \brief Unary minus (negation) operator.
     */
    Vector<T> & operator-();
    
    /**
     * \brief Add Buffer/Assignment operator.
     */
    Vector<T> & operator+=(const Vector<T> &rhs);
    
    /**
     * \brief Add Scalar/Assignment operator.
     */
    Vector<T> & operator+=(const T &rhs);
    
    /**
     * \brief Subtract Buffer/Assignment operator.
     */
    Vector<T> & operator-=(const Vector<T> &rhs);
    
    /**
     * \brief Subtract Scalar/Assignment operator.
     */
    Vector<T> & operator-=(const T &rhs);
    
    /**
     * \brief Multiply Buffer/Assignment operator.
     */
    Vector<T> & operator*=(const Vector<T> &rhs);
    
    /**
     * \brief Multiply Scalar/Assignment operator.
     */
    Vector<T> & operator*=(const T &rhs);

    /**
     * \brief Divide Buffer/Assignment operator.
     */
    Vector<T> & operator/=(const Vector<T> &rhs);
    
    /**
     * \brief Divide Scalar/Assignment operator.
     */
    Vector<T> & operator/=(const T &rhs);
    
    /*****************************************************************************************
                                            Methods
    *****************************************************************************************/
    /**
     * \brief Returns the size of \ref vec.
     */
    const unsigned size() const {return (const unsigned) vec.size();};
    
    /**
     * \brief Finds the first instance of "val" in \ref vec.
     *
     * \param val The value to look for in \ref vec.
     * \return Index of first instance of "val".  If there aren't any elements equal to "val"
     *      it returns -1.
     */
    const int find(const T val) const;
    
    /**
     * \brief Returns the sum of all the elements in \ref vec.
     */
    T sum() const;

    /**
     * \brief Sets each element of \ref buf equal to its value to the power of "exponent".
     *
     * \param exponent Exponent to use.
     * \return Reference to "this".
     */
    Vector<T> & pow(const T exponent);
    
    /**
     * \brief Returns the mean (average) of the data in \ref buf.
     */
    const T mean() const;
    
    /**
     * \brief Returns the variance of the data in \ref buf.
     */
    const double var() const;
    
    /**
     * \brief Returns the standard deviation of the data in \ref buf.
     */
    const double stdDev() const {return std::sqrt(this->var());}
    
    /**
     * \brief Returns the median element of \ref buf.
     */
    const T median();
    
    /**
     * \brief Returns the maximum element in \ref buf.
     *
     * \param maxLoc If it isn't equal to NULL the index of the maximum element
     *      will be returned via this pointer.  If more than one element is equal
     *      to the maximum value the index of the first will be returned.
     *      Defaults to NULL.
     */
    const T max(unsigned *maxLoc = NULL) const;
    
    /**
     * \brief Returns the minimum element in \ref buf.
     *
     * \param minLoc If it isn't equal to NULL the index of the minimum element
     *      will be returned via this pointer.  If more than one element is equal
     *      to the minimum value the index of the first will be returned.
     *      Defaults to NULL.
     */
    const T min(unsigned *minLoc = NULL) const;
    
    /**
     * \brief Sets the upper and lower limit of the values in \ref buf.
     *
     * \param val Limiting value for the data in \ref buf.  Any values that
     *      are greater than "val" are made equal to "val", and
     *      any that are less than -val are made equal to -val.
     * \return Reference to "this".
     */
    Vector<T> & saturate(T val);

    /**
     * \brief Does a "ceil" operation on \ref vec.
     * \return Reference to "this".
     */
    Vector<T> & ceil(void);

    /**
     * \brief Does a "floor" operation on \ref vec.
     * \return Reference to "this".
     */
    Vector<T> & floor(void);

    /**
     * \brief Does a "round" operation on \ref vec.
     * \return Reference to "this".
     */
    Vector<T> & round(void);

    /**
     * \brief Changes the elements of \ref vec to their absolute value.
     *
     * \return Reference to "this".
     */
    Vector<T> & abs();
    
    /**
     * \brief Sets each element of \ref vec to e^(element).
     *
     * \return Reference to "this".
     */
    Vector<T> & exp();
    
    /**
     * \brief Sets each element of \ref vec to the natural log of the element.
     *
     * \return Reference to "this".
     */
    Vector<T> & log();
    
    /**
     * \brief Sets each element of \ref vec to the base 10 log of the element.
     *
     * \return Reference to "this".
     */
    Vector<T> & log10();

    /**
     * \brief Circular rotation.
     *
     * \param numToShift Number of positions to shift in the circular rotation.  numToShift
     *      can be positive or negative.  If you visualize the 0 index value at the left and
     *      the end of the array at the right, positive numToShift values shift the array to
     *      the left, and negative values shift it to the right.
     * \return Reference to "this".
     */
    Vector<T> & vectorRotate(int numToShift);
    
    /**
     * \brief Reverses the order of the elements in \ref vec.
     *
     * \return Reference to "this".
     */
    Vector<T> & reverse();

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
    Vector<T> & upsample(int rate, int phase = 0);
    
    /**
     * \brief Removes rate-1 samples out of every rate samples.
     *
     * \param rate Indicates how many samples should be removed.
     * \param phase Tells the method which sample should be the first to be kept.  Valid values
     *      are 0 to "rate"-1.  Defaults to 0.
     * \return Reference to "this".
     */
    Vector<T> & downsample(int rate, int phase = 0);
    
    /**
     * \brief Replaces \ref vec with the cumulative sum of the samples in \ref vec.
     *
     * \param initialVal Initializing value for the cumulative sum.  Defaults to zero.
     * \return Reference to "this".
     */
    Vector<T> & cumsum(T initialVal = 0);
    
    /**
     * \brief Replaces \ref vec with the difference between successive samples in vec.
     *
     * The resulting \ref vec is one element shorter than it was previously.
     * \return Reference to "this".
     */
    Vector<T> & diff();
    
    /**
     * \brief Replaces \ref vec with the difference between successive samples in vec.
     *
     * \param previousVal The last value in the sample stream before the current contents
     *      of \ref vec.  previousVal allows the resulting vec to be the same size as the
     *      previous vec.
     * \return Reference to "this".
     */
    Vector<T> & diff(T & previousVal);
    
    /**
     * \brief Generates a real tone.
     *
     * \param freq The tone frequency.
     * \param sampleFreq The sample frequency.  Defaults to 1 Hz.
     * \param phase The tone's starting phase, in radians.  Defaults to 0.
     * \param numSamples The number of samples to generate.  "0" indicates to generate
     *      this->size() samples.  Defaults to 0.
     * \return The next phase if the tone were to continue.
     */
    T tone(T freq, T sampleFreq = 1.0, T phase = 0.0, unsigned numSamples = 0);
    
    /**
     * \brief Modulates the data with a real sinusoid.
     *
     * \param freq The modulating tone frequency.
     * \param sampleFreq The sample frequency of the data.  Defaults to 1 Hz.
     * \param phase The modulating tone's starting phase, in radians.  Defaults to 0.
     * \return The next phase if the tone were to continue.
     */
    T modulate(T freq, T sampleFreq = 1.0, T phase = 0.0);
};

template <class T>
Vector<T>::Vector(uint32_t len, bool rowVec, std::shared_ptr< std::vector<T> > scratch)
{
    vec.resize(len);
    rowVector = rowVec;
    scratchBuf = scratch;
}

template <class T>
Vector<T>::Vector(std::vector<T> *data, bool rowVec, std::shared_ptr< std::vector<T> > scratch)
{
    vec = *data;
    rowVector = rowVec;
    scratchBuf = scratch;
}

template <class T>
template <class U>
Vector<T>::Vector(U *data, uint32_t dataLen, bool rowVec, std::shared_ptr< std::vector<T> > scratch)
{
    vec.resize(dataLen);
    for (uint32_t index=0; index<dataLen; index++) {
        vec[index] = (T) data[index];
    }
    rowVector = rowVec;
    scratchBuf = scratch;
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> initVals, bool rowVec, std::shared_ptr< std::vector<T> > scratch) : vec(initVals)
{
    rowVector = rowVec;
    scratchBuf = scratch;
}

template <class T>
Vector<T> & Vector<T>::operator-()
{
    for (T element : vec) {
        element = -element;
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::operator=(const Vector<T>& rhs)
{
    vec.resize(rhs.size());
    for (unsigned index=0; index<vec.size(); index++) {
        vec[index] = rhs[index];
    }
    rowVector = rhs.rowVector;
    scratchBuf = rhs.scratchBuf;
    return *this;
}

template <class T>
Vector<T> & Vector<T>::operator+=(const Vector<T> &rhs)
{
    assert(vec.size() == rhs.size());
    
    for (unsigned index=0; index<vec.size(); index++) {
        vec[index] += rhs[index];
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::operator+=(const T &rhs)
{
    for (unsigned index=0; index<vec.size(); index++) {
        vec[index] += rhs;
    }
    return *this;
}

template <class T>
inline Vector<T> operator+(Vector<T> lhs, const Vector<T>& rhs)
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

template <class T>
Vector<T> & Vector<T>::operator-=(const Vector<T> &rhs)
{
    assert(vec.size() == rhs.size());
    
    for (unsigned index=0; index<vec.size(); index++) {
        vec[index] -= rhs[index];
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::operator-=(const T &rhs)
{
    for (T element : vec) {
        element -= rhs;
    }
    return *this;
}

template <class T>
inline Vector<T> operator-(Vector<T> lhs, const Vector<T>& rhs)
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

template <class T>
Vector<T> & Vector<T>::operator*=(const Vector<T> &rhs)
{
    assert(vec.size() == rhs.size());
    
    for (unsigned index=0; index<vec.size(); index++) {
        vec[index] *= rhs[index];
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::operator*=(const T &rhs)
{
    for (T element : vec) {
        element *= rhs;
    }
    return *this;
}

template <class T>
inline Vector<T> operator*(Vector<T> lhs, const Vector<T>& rhs)
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

template <class T>
Vector<T> & Vector<T>::operator/=(const Vector<T> &rhs)
{
    assert(vec.size() == rhs.size());
    
    for (unsigned index=0; index<vec.size(); index++) {
        vec[index] /= rhs[index];
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::operator/=(const T &rhs)
{
    for (T element : vec) {
        element /= rhs;
    }
    return *this;
}

template <class T>
inline Vector<T> operator/(Vector<T> lhs, const Vector<T>& rhs)
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
const int Vector<T>::find(const T val) const
{
    for (int index=0; index<vec.size(); index++) {
        if (vec[index] == val) {
            return index;
        }
    }
    return -1;
}

template <class T>
T Vector<T>::sum() const
{
    T vecSum = 0;
    for (T element : vec) {
        vecSum += element;
    }
    return vecSum;
}

template <class T>
Vector<T> & pow(const T exponent);

template <class T>
const T Vector<T>::mean() const
{
    return sum() / size();
}

template <class T>
const double Vector<T>::var() const
{
    T squaredSum = 0;
    for (T element : vec) {
        squaredSum += element * element;
    }
    T vecMean = mean();
    return squaredSum / size() - vecMean * vecMean;
}

template <class T>
void Vector<T>::copyToScratchBuf(std::unique_ptr< std::vector<T> > from)
{
    scratchBuf.resize(from.size());
    for (unsigned index=0; index<from.size(); index++) {
        scratchBuf[index] = from[index];
    }
}

template <class T>
const T Vector<T>::median()
{
    assert(vec.size() > 0);
    
    copyToScratchBuf(vec);
    std::sort(scratchBuf.begin(), scratchBuf.end());
    if (this->size() & 1) {
        // Odd number of samples
        return scratchBuf[this->size()/2];
    }
    else {
        // Even number of samples.  Average the two in the middle.
        unsigned topHalfIndex = this->size()/2;
        return (scratchBuf[topHalfIndex] + scratchBuf[topHalfIndex-1]) / ((T) 2);
    }
}

template <class T>
const T Vector<T>::max(unsigned *maxLoc) const
{
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

template <class T>
const T Vector<T>::min(unsigned *minLoc) const
{
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

template <class T>
Vector<T> & Vector<T>::saturate(T val)
{
    for (T element : vec) {
        element = std::min(element, val);
        element = std::max(element, -val);
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::ceil(void)
{
    for (T element : vec) {
        element = std::ceil(element);
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::floor(void)
{
    for (T element : vec) {
        element = std::floor(element);
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::round(void)
{
    for (T element : vec) {
        element = std::round(element);
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::abs()
{
    for (T element : vec) {
        element = std::abs(element);
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::exp()
{
    for (T element : vec) {
        element = std::exp(element);
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::log()
{
    for (T element : vec) {
        element = std::log(element);
    }
    return *this;
}

template <class T>
Vector<T> & Vector<T>::log10()
{
    for (T element : vec) {
        element = std::log10(element);
    }
    return *this;
}

template <class T>
Vector<T> & vectorRotate(int numToShift);

template <class T>
Vector<T> & reverse();

template <class T>
Vector<T> & upsample(int rate, int phase = 0);

template <class T>
Vector<T> & downsample(int rate, int phase = 0);

template <class T>
Vector<T> & cumsum(T initialVal = 0);

template <class T>
Vector<T> & diff();

template <class T>
Vector<T> & diff(T & previousVal);

template <class T>
T tone(T freq, T sampleFreq = 1.0, T phase = 0.0, unsigned numSamples = 0);

template <class T>
T modulate(T freq, T sampleFreq = 1.0, T phase = 0.0);

}

