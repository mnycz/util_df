#ifndef UTIL_DF_CROSS_SECTION_HH
#define UTIL_DF_CROSS_SECTION_HH

// useful cross section functions

#include <cstdlib>
#include <iostream>

#include "TGeant4SystemOfUnits.h"
#include "TGeant4PhysicalConstants.h"

namespace util_df {
   namespace CrossSection {
      double GetLuminosity(double I,double rho,double x,double A,bool isNucleon=true);
   } // ::CrossSection
} // ::util_df 

#endif
