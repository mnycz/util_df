#ifndef UTIL_DF_ENERGY_LOSS
#define UTIL_DF_ENERGY_LOSS

// useful energy loss functions

#include <cstdlib>
#include <math.h>  
#include <cmath> 

#include "Material.hh"
#include "UtilDFConstants.hh" 

#include "TRandom3.h"

namespace util_df { 
   namespace EnergyLoss { 
      double GetRadiationLength(double A,double Z);
      double GetIon_Loss_Landau(material_t mat,const double E,bool isRndm=false); 
      double GetIon_Loss_Landau(int mat,const double A,const double Z,const double rho,const double x,double E,bool isRndm=false); 
      double GetBremss_Loss_Inexact_rndm(const double E,const double bt); 
      double GetBremss_Loss_Inexact_pdf(const double dE,const double E,const double bt); 
      double GetBremss_Loss_Exact_pdf(const double dE,const double E,const double bt); 
      double GetBremss_Loss_Exact_rndm(const double E,const double bt);
      double bremss_getRndmNumG(const double bt); 
      double bremss_getH(const double x); 
      double bremss_geth(const double x,const double E,const double bt); 
      double GetStoppingPower_e(material_t mat,double E); 
      double GetStoppingPower_e(int mat,double A,double Z,double rho,double E,double M,double z=1); 
      double GetDelta(int mat,double bg); 
   }
}

#endif 
