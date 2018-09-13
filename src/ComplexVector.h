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
#include "Vector.h"

namespace MatrixDSP {
 
template <class T>
class ComplexVector : public Vector< std::complex<T> > {
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
    
};

}

#endif

