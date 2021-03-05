#ifndef UTIL_DF_ENERGY_LOSS
#define UTIL_DF_ENERGY_LOSS

// useful energy loss functions

#include <cstdlib>
#include <math.h>  
#include <cmath> 

#include "Material.hh"
#include "UtilDFConstants.hh" 

namespace util_df { 
   namespace EnergyLoss { 
      double GetRadiationLength(double A,double Z);
      double GetStoppingPower_e(material_t mat,double E); 
      double GetStoppingPower_e(int mat,double A,double Z,double rho,double E,double M,double z=1); 
      double GetDelta(int mat,double bg); 
   }
}

#endif 
