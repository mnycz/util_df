#include "UtilDFEnergyLoss.hh"
//______________________________________________________________________________
namespace util_df {
   namespace EnergyLoss { 
      //______________________________________________________________________________
      double GetRadiationLength(double A,double Z){
	 // radiation length in g/cm^2 
         double T0 = 1433.; 
         double T1 = A/( Z*(Z+1.)*(11.319 - log(Z) ) ); 
	 double X0 = T0*T1;
	 return X0;
      }
      //______________________________________________________________________________
      double GetStoppingPower_e(material_t mat,double E){
         // Bethe-Bloch equation for electrons (Eq 32.24 in PDG book)  
         // N.B.: Energies in MeV, density in g/cm^2 
         double M    = Constants::electron_mass*1E+3; // in MeV
	 double z    = -1;  // sign of e- charge
	 double dEdx = GetStoppingPower_e(mat.ID,mat.A,mat.Z,mat.rho,E,M,z); 
	 return dEdx;  // in MeV/g/cm^2  
      }
      //______________________________________________________________________________
      double GetStoppingPower_e(int mat,double A,double Z,double rho,double E,double M,double z){
         // Bethe-Bloch equation for electrons (Eq 32.24 in PDG book)  
         // inputs:
         // - mat => material index (see GetDelta function)  
         // - A => atomic number (g/mol)
         // - Z => number of protons 
         // - E => energy of incident particle (MeV)   
         // - M => incident particle mass (MeV)
         // - z => incident particle charge (+/- 1)
         // output: 
	 // - stopping power in MeV/g/cm^2 
	 double K = 0.307075;  // MeV mol^-1 cm^2 
         // double I     = (15.*Z)*1E-6;      // FIXME THIS IS AN ESTIMATE FOR Z < 10! NB: eV scale => ~1E-6 MeV! 
         // if(Z>12){
	 //    // for aluminum
	 //    I = (13.*Z)*1E-6;
	 // }
         double I     = 28.816*sqrt( rho*Z/A )*1e-6; // MeV
         // double me    = 0.511;   // in MeV
         double beta_sq = 1. - M*M/(E*E);
         double beta  = sqrt(beta_sq); 
         double gamma = 1./sqrt(1.-beta_sq); 
         double delta = GetDelta(mat,beta*gamma);
         // Max energy transfer in single collision 
         double Tmax  = M*(gamma-1.)/2.; ;
         double sf    = 0.5*K*(Z/A)*( 1./(beta_sq) );
         // first term
         double num   = 2.*M*beta_sq*gamma*gamma*Tmax; 
         double den   = I*I; 
         double T1    = log(num/den);
         // second term
         double T2    = 1. - beta_sq; 
         // third term 
         double T3    = (-1.)*log(2)*(2.*gamma - 1.)/(gamma*gamma);
         // fourth term  
         double T4    = (1./8.)*pow((gamma-1.)/gamma,2.);
         // fifth term
         double T5    = (-1.)*delta; 
         double dEdx  = sf*(T1+T2+T3+T4+T5); 
	 return dEdx; 
      }
      //______________________________________________________________________________
      double GetDelta(int mat,double bg){
         // input: beta*gamma, material
	 // FIXME: replace with a file read!
         // Reference: Atomic Data and Nuclear Data Tables 30, 261 (1984)  
         bool conductor = false;
	 double C_bar=0,a=0,x0=0,x1=0,k=0,delta0=0; 
         if(mat==Constants::kHelium){
	    // He 
	    C_bar = 11.1393;
            a     = 0.13443;
            x0    = 2.2017;
            x1    = 3.6122;
	    k     = 5.8347;
	    delta0 = 0;
	    conductor = false;
         }else if(mat==Constants::kAluminum){
	    // Al 
	    C_bar = 4.2395;
            a     = 0.0824;
            x0    = 0.1708;
            x1    = 3.0127;
	    k     = 3.6345;
	    delta0 = 0.12;
	    conductor = true;
         }else if(mat==Constants::kCopper){
	    // Cu 
	    C_bar = 4.4190;
            a     = 0.14339;
            x0    = -0.0254;
            x1    = 3.2792; 
	    k     = 2.9044;
	    delta0 = 0.08;
	    conductor = true;
         }else if(mat==Constants::kGlass){
	    // Glass 
	    C_bar = 4.2834;
            a     = 0.1537;
            x0    = 0.2000;
            x1    = 3.0000;
	    k     = 3.0000;
	    delta0 = 0.;
	    conductor = false;
         }else if(mat==Constants::kTungsten){
	    // tungsten
	    C_bar = 5.405;
            a     = 0.15509;
            x0    = 0.2167;
            x1    = 3.4960;
	    k     = 2.8447;
	    delta0 = 0.14;
	    conductor = true;
         } 
         double x = log10(bg); 
         double delta=0;
         if(x>=x1)              delta = 2.*log(10)*x - C_bar;
         if(x>=x0 && x<x1)      delta = 2.*log(10)*x - C_bar + a*pow(x1-x,k); 
         if(x<x0 && !conductor) delta = 0; 
         if(x<x0 && conductor)  delta = delta0*pow(10.,2.*(x-x0));
         return delta; 
      }
   }
}
