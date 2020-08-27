#include "UtilDFEnergyLoss.hh"
//______________________________________________________________________________
namespace util_df {
   namespace EnergyLoss { 
      double GetRadiationLength(double A,double Z){
	 // radiation length in g/cm^2 
         double T0 = 1433.; 
         double T1 = A/( Z*(Z+1.)*(11.319 - log(Z) ) ); 
	 double X0 = T0*T1;
	 return X0;
      }
   }
}
