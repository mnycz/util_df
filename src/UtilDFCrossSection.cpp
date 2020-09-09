#include "UtilDFCrossSection.hh"
//______________________________________________________________________________
namespace util_df { 
   namespace CrossSection {
      //______________________________________________________________________________
      double GetLuminosity(double I,double rho,double x,double A,bool isNucleon){
	 // I   = beam current (amps) 
	 // rho = density (g/cm^3) 
	 // x   = target thickness (cm) 
	 // A   = mass number of target (number of nucleons = Z + N) 
	 double Wfact = 1.0;
	 if(isNucleon) Wfact = A;                      // convert from N_atoms => N_nucleons in target  
	 double np = I/TGeant4Unit::e_SI;              // number of incident particles, (num e-)/sec
	 double nd = (rho*x/A)*TGeant4Unit::Avogadro;  // target number density, [g/cm^3][cm][atoms/mole] = [atoms/cm^2]
	 double L  = Wfact*np*nd;                      // luminosity, [(atoms or nucl)*s^-1*cm^-2] 
	 return L;
      }
   }
}
