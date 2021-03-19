#ifndef UTIL_DF_FOURIER_TRANSFORM_HH
#define UTIL_DF_FOURIER_TRANSFORM_HH

// A class for computing a simple fourier transform of data 

#include <cstdlib>
#include <iostream> 
#include <cmath>

// #include "TH1F.h"

#include "UtilDFConstants.hh" 

namespace util_df {

   class FourierTransform{

      private:
	 int fVerbosity;
	 double fZeroPaddingTime;                                      // time used to zero-pad data  
	 double fSampleFreq;                                           // sampling frequency (Hz) 
	 double *fComplex;                                             // complex array used in computing the FFT 

	 void ClearArray(); 
	 void four1(int isign,int nn,double data[]); 

	 int GetNFFT(int N); 
         int GetNextPowerOfTwo(int N);

      public: 
	 FourierTransform(int verbosity=0,double sampleFreq=0,double padTime=0);
	 ~FourierTransform(); 

         void SetVerbosity(int v)           { fVerbosity       = v; } 
	 void SetSampleFrequency(double f)  { fSampleFreq      = f; } 
	 void SetZeroPaddingTime(double t)  { fZeroPaddingTime = t; } 

	 int Transform(int N,double *f,double *F);                     // N = size of f; f = input (time domain), F = output (freq domain); returns number of FFT points  
	 void InverseTransform(int N,double *F,double *f);             // N = size of f; F = input (freq domain), f = output (time domain) 
   
         // TH1F *GetHistogram(const char *hName,const char *title,int N,double F[]); 

   };

} //::util_df

#endif 
