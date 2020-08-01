#ifndef UTIL_DF_BLINDER_HH
#define UTIL_DF_BLINDER_HH 

#include <cstdlib>
#include <iostream>
#include <string>

#include "TRandom3.h"

#include "UtilDFConstants.hh"
#include "UtilDFFunc.hh"
#include "UtilDFImport.hh"
#include "UtilDFExport.hh"

// a class for blinding field data

namespace util_df { 

   class Blinder {

      private:
	 std::string fBlindPath;          // path to the blind value (built in the constructor)  
	 std::string fLabel;              // a label to store the blind value 

	 int fBlindUnits;                 // units of the scale input by the user  

	 double fBlindMagnitude;          // the scale of the blind 
	 std::vector<double> fBlindValue; // blind value; index 0 in Hz, index 1 in user's units  

	 TRandom3 *fRand;                 // a random number generator for the blind 

	 int ReadData();                  // read in the blinding (if it exists) 
         int WriteData();                 // print the blinding data to file  
	 int GenerateBlinding();          // generate a random number at +/- fBlindMagnitude 

      public:
	 Blinder(std::string label="UNKNOWN",double mag=1.,int units=Constants::ppm);
	 ~Blinder();

	 void SetBlindingScale(double val,int units=Constants::Hz) { fBlindMagnitude = val; fBlindUnits = units; }

	 int UpdateBlinding()   { int rc = GenerateBlinding(); return rc; }
         int GetBlindingUnits() { return fBlindUnits; } 

	 double GetBlinding(int type=1,int units=Constants::Hz);  // type = 1: first value, type = 2, second value

   };

} // ::util_df 

#endif
