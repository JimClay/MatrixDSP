//
//  Matrix.cpp
//  MatrixDSP
//
//  Created by Jim Clay on 9/1/18.
//  Copyright © 2018 Jim Clay. All rights reserved.
//

#ifndef __MATRIX_DSP_COMPLEX_VECTOR__
#define __MATRIX_DSP_COMPLEX_VECTOR__

#include <complex>
#include <cassert>
#include "Vector.h"
#include "FftSetupManager.h"
#include <iostream>
#include <iomanip>

namespace MatrixDSP {
 
template <class T>
class ComplexVector : public Vector< std::complex<T> > {
    private:
    
    static FftSetupManager<T, typename std::vector<T>::iterator, typename std::vector< std::complex<T> >::iterator >& GetFftSetupManager()
    {
        static FftSetupManager<T, typename std::vector<T>::iterator, typename std::vector< std::complex<T> >::iterator > managerInstance;
        return managerInstance;
    }

    public:
    
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
    ComplexVector<T>(unsigned len = 0, bool rowVec = false, std::shared_ptr< std::vector< std::complex<T> > > scratch = nullptr) :
            Vector< std::complex<T> >(len, rowVec, scratch) {}
    
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
    ComplexVector<T>(std::vector< std::complex<T> > *data, bool rowVec = false, std::shared_ptr< std::vector< std::complex<T> > > scratch = nullptr) :
            Vector< std::complex<T> >(data, rowVec, scratch) {}
    
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
    ComplexVector<T>(std::complex<U> *data, uint32_t dataLen, bool rowVec = false, std::shared_ptr< std::vector< std::complex<T> > > scratch = nullptr) :
            Vector< std::complex<T> >(data, dataLen, rowVec, scratch) {}
    
    ComplexVector<T>(std::initializer_list< std::complex<T> > initVals, bool rowVec = false, std::shared_ptr< std::vector< std::complex<T> > > scratch = nullptr) : Vector< std::complex<T> >(initVals, rowVec, scratch) {}
    
    /**
     * \brief Copy constructor.
     */
    ComplexVector<T>(const ComplexVector<T>& other) {*this = other;}
    
    /**
     * \brief Copy constructor.
     */
    ComplexVector<T>(const Vector< std::complex<T> >& other) {
        this->vec = other.vec;
        this->rowVector = other.rowVector;
        this->scratchBuf = other.getScratchBuf();
    }
    
    /**
     * \brief Virtual destructor.
     */
    virtual ~ComplexVector() = default;

    /*****************************************************************************************
                                            Methods
    *****************************************************************************************/
    const std::complex<T> median() {assert(false); return std::complex<T>(0, 0);}
    
    /**
     * \brief Returns the element in \ref vec with the largest absolute value.
     *
     * \param maxLoc If it isn't equal to nullptr the index of the maximum element
     *      will be returned via this pointer.  If more than one element is equal
     *      to the maximum value the index of the first will be returned.
     *      Defaults to nullptr.
     */
    const std::complex<T> max(unsigned *maxLoc = nullptr) const {
        assert(this->size() > 0);
        
        T maxVal = std::abs(this->vec[0]);
        std::complex<T> maxElement = this->vec[0];
        unsigned maxIndex = 0;
        
        for (unsigned index=1; index<this->size(); index++) {
            T absVal = std::abs(this->vec[index]);
            if (maxVal < absVal) {
                maxVal = absVal;
                maxElement = this->vec[index];
                maxIndex = index;
            }
        }
        if (maxLoc != nullptr) {
            *maxLoc = maxIndex;
        }
        return maxElement;
    }
    
    /**
     * \brief Returns the element in \ref vec with the smallest absolute value.
     *
     * \param minLoc If it isn't equal to nullptr the index of the minimum element
     *      will be returned via this pointer.  If more than one element is equal
     *      to the minimum value the index of the first will be returned.
     *      Defaults to nullptr.
     */
    const std::complex<T> min(unsigned *minLoc = nullptr) const {
        assert(this->size() > 0);
        
        T minVal = std::abs(this->vec[0]);
        std::complex<T> minElement = this->vec[0];
        unsigned minIndex = 0;
        
        for (unsigned index=1; index<this->size(); index++) {
            T absVal = std::abs(this->vec[index]);
            if (minVal > absVal) {
                minVal = absVal;
                minElement = this->vec[index];
                minIndex = index;
            }
        }
        if (minLoc != nullptr) {
            *minLoc = minIndex;
        }
        return minElement;
    }
    
    /**
     * \brief Sets the upper and lower limit of the values in \ref buf.
     *
     * \param val Limiting value for the data in \ref buf.  Any values that
     *      are greater than "val" are made equal to "val", and
     *      any that are less than -val are made equal to -val.
     * \return Reference to "this".
     */
    ComplexVector<T> & saturate(std::complex<T> val) {
        assert(val.real() >= 0);
        assert(val.imag() >= 0);
        
        for (unsigned index=0; index<this->size(); index++) {
            this->vec[index].real(std::min(this->vec[index].real(), val.real()));
            this->vec[index].real(std::max(this->vec[index].real(), -val.real()));
            this->vec[index].imag(std::min(this->vec[index].imag(), val.imag()));
            this->vec[index].imag(std::max(this->vec[index].imag(), -val.imag()));
        }
        return *this;
    }

    /**
     * \brief Does a "ceil" operation on \ref vec.
     * \return Reference to "this".
     */
    ComplexVector<T> & ceil(void) {
        for (unsigned index=0; index<this->size(); index++) {
            this->vec[index].real(std::ceil(this->vec[index].real()));
            this->vec[index].imag(std::ceil(this->vec[index].imag()));
        }
        return *this;
    }

    /**
     * \brief Does a "floor" operation on \ref vec.
     * \return Reference to "this".
     */
    ComplexVector<T> & floor(void) {
        for (unsigned index=0; index<this->size(); index++) {
            this->vec[index].real(std::floor(this->vec[index].real()));
            this->vec[index].imag(std::floor(this->vec[index].imag()));
        }
        return *this;
    }

    /**
     * \brief Does a "round" operation on \ref vec.
     * \return Reference to "this".
     */
    ComplexVector<T> & round(void) {
        for (unsigned index=0; index<this->size(); index++) {
            this->vec[index].real(std::round(this->vec[index].real()));
            this->vec[index].imag(std::round(this->vec[index].imag()));
        }
        return *this;
    }

    /**
     * \brief Generates a complex tone.
     *
     * \param freq The tone frequency.
     * \param sampleFreq The sample frequency.  Defaults to 1 Hz.
     * \param phase The tone's starting phase, in radians.  Defaults to 0.
     * \param numSamples The number of samples to generate.  "0" indicates to generate
     *      this->size() samples.  Defaults to 0.
     * \return The next phase if the tone were to continue.
     */
    T tone(T freq, T sampleFreq = 1.0, T phase = 0.0, unsigned numSamples = 0) {
        assert(sampleFreq > 0.0);
    
        if (numSamples && numSamples != this->size()) {
            this->resize(numSamples);
        }
    
        T phaseInc = (freq / sampleFreq) * 2 * M_PI;
        for (unsigned i=0; i<this->size(); i++) {
            this->vec[i].real(std::cos(phase));
            this->vec[i].imag(std::sin(phase));
            phase += phaseInc;
        }
        return phase;
    }
    
    /**
     * \brief Modulates the data with a complex tone.
     *
     * \param freq The modulating tone frequency.
     * \param sampleFreq The sample frequency of the data.  Defaults to 1 Hz.
     * \param phase The modulating tone's starting phase, in radians.  Defaults to 0.
     * \return The next phase if the tone were to continue.
     */
    T modulate(T freq, T sampleFreq = 1.0, T phase = 0.0) {
        assert(sampleFreq > 0.0);
    
        T phaseInc = (freq / sampleFreq) * 2 * M_PI;
        for (unsigned i=0; i<this->size(); i++) {
            this->vec[i] *= std::complex<T>(std::cos(phase), std::sin(phase));
            phase += phaseInc;
        }
        return phase;
    }
    
    ComplexVector<T> & fft(MatrixDSP::Vector<T> &input, bool inverseFft = false) {
        assert(input.size() > 1);
        
        this->resize(input.size());
        auto *fftSetup = GetFftSetupManager().getFftSetup(input.size(), inverseFft);
        fftSetup->transform(input.vec.begin(), this->vec.begin());
        return *this;
    }
    
    ComplexVector<T> & fft(MatrixDSP::ComplexVector<T> &input, bool inverseFft = false) {
        assert(input.size() > 1);
        
        this->resize(input.size());
        auto *fftSetup = GetFftSetupManager().getFftSetup(input.size(), inverseFft);
        fftSetup->transform(input.vec.begin(), this->vec.begin());
        return *this;
    }
    
    void print() {
        std::string divider;
        if (this->rowVector) {
            divider = ", ";
        }
        else {
            divider = "\n";
        }
        std::cout << std::setw(8) << std::setprecision(4) << this->vec[0].real() << this->vec[0].imag() << "i";
        for (unsigned index=1; index<this->size(); index++) {
            std::cout << divider << std::setw(8) << std::setprecision(4) << this->vec[index].real() << this->vec[index].imag() << "i";
        }
        std::cout << std::endl;
    }
};

template <class T>
ComplexVector<T> operator<(ComplexVector<T> lhs, const std::complex<T> & rhs) {
	T rhsSquareVal = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
	for (unsigned index = 0; index < lhs.size(); index++) {
		T lhsSquareVal = lhs[index].real() * lhs[index].real() + lhs[index].imag() * lhs[index].imag();
		lhs[index] = (std::complex<T>)(lhsSquareVal < rhsSquareVal);
	}
	return lhs;
}

template <class T>
ComplexVector<T> operator<=(ComplexVector<T> lhs, const std::complex<T> & rhs) {
	T rhsSquareVal = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
	for (unsigned index = 0; index < lhs.size(); index++) {
		T lhsSquareVal = lhs[index].real() * lhs[index].real() + lhs[index].imag() * lhs[index].imag();
		lhs[index] = (std::complex<T>)(lhsSquareVal <= rhsSquareVal);
	}
	return lhs;
}

template <class T>
ComplexVector<T> operator>(ComplexVector<T> lhs, const std::complex<T> & rhs) {
	T rhsSquareVal = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
	for (unsigned index = 0; index < lhs.size(); index++) {
		T lhsSquareVal = lhs[index].real() * lhs[index].real() + lhs[index].imag() * lhs[index].imag();
		lhs[index] = (std::complex<T>)(lhsSquareVal > rhsSquareVal);
	}
	return lhs;
}

template <class T>
ComplexVector<T> operator>=(ComplexVector<T> lhs, const std::complex<T> & rhs) {
	T rhsSquareVal = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
	for (unsigned index = 0; index < lhs.size(); index++) {
		T lhsSquareVal = lhs[index].real() * lhs[index].real() + lhs[index].imag() * lhs[index].imag();
		lhs[index] = (std::complex<T>)(lhsSquareVal >= rhsSquareVal);
	}
	return lhs;
}

template <class T>
ComplexVector<T> & fft(Vector<T> &input, ComplexVector<T> &output, bool inverseFft = false) {
    return output.fft(input, inverseFft);
}

template <class T>
ComplexVector<T> & fft(ComplexVector<T> &input, ComplexVector<T> &output, bool inverseFft = false) {
    return output.fft(input, inverseFft);
}

}

#endif

