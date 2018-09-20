//
//  FftSetupManager.h
//  MatrixDSP
//
//  Created by Jim Clay on 9/19/18.
//

#ifndef FftSetupManager_h
#define FftSetupManager_h

#include <map>
#include "kissfft.h"

template <class T, class RealIterator, class ComplexIterator>
class FftSetupManager {
    private:
    std::map<int, kissfft<T, RealIterator, ComplexIterator> * > fftSetups;
    
    int genKey(int fftLen, bool inverseFft) {return fftLen * 2 + (int) inverseFft;}
    
    public:
    FftSetupManager<T>() {}
    
    ~FftSetupManager() {
        cleanUp();
    }
    
    kissfft<T, RealIterator, ComplexIterator> * getFftSetup(int fftLen, bool inverseFft = false) {
        int key = genKey(fftLen, inverseFft);
        
        auto setupPtr = fftSetups.find(key);
        if (setupPtr != fftSetups.end()) {
            return setupPtr->second;
        }
        
        kissfft<T, RealIterator, ComplexIterator> *fftSetup = new kissfft<T, RealIterator, ComplexIterator>(fftLen, inverseFft);
        fftSetups[key] = fftSetup;
        return fftSetup;
    }
    
    void removeFftSetup(int fftLen, bool inverseFft = false) {
        auto setupPtr = fftSetups.find(genKey(fftLen, inverseFft));
        if (setupPtr == fftSetups.end()) {
            return;
        }
        delete setupPtr->second;
        fftSetups.erase(setupPtr);
    }
    
    void cleanUp() {
        auto it = fftSetups.begin();
        while(it != fftSetups.end()) {
            delete it->second;
            it = fftSetups.erase(it);
        }
    }
};


#endif /* FftSetupManager_h */
