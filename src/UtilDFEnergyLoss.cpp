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
      //___________________________________________________________________________________
      double GetIon_Loss_Landau(material_t mat,const double E,bool isRndm){
	 // simplified version using the material data struct
         return GetIon_Loss_Landau(mat.ID,mat.A,mat.Z,mat.rho,mat.length,E,isRndm); 
      }
      //___________________________________________________________________________________
      double GetIon_Loss_Landau(int mat,const double A,const double Z,const double rho,
                                const double x,double E,bool isRndm){
	 // Ionization loss as described for detectors of moderate thickness
	 // Follows a highly-skewed Landau distribution.  PDG Eqn 32.11
         // input
         // - mat = material ID (see GetDelta for ID code)
         // - A   = molecular mass [g/mol] 
         // - Z   = atomic number 
         // - rho = material density [g/cm^3] 
         // - x   = material thickness [g/cm^2]
         // - E   = incident particle energy [MeV] 
         // output 
         // - (differential) energy loss in MeV 
	 double K       = 0.307075;  // MeV mol^-1 cm^2 
         double I       = 28.816*sqrt( rho*Z/A )*1e-6;   // MeV
         double M       = Constants::electron_mass*1E+3; // in MeV  
         double beta_sq = 1. - M*M/(E*E);
         double beta    = sqrt(beta_sq); 
         double gamma   = 1./sqrt(1.-beta_sq); 
         double delta   = GetDelta(mat,beta*gamma);
         double j       = 0.200;
         double xi      = (K/2.)*(Z/A)*(x/beta_sq); 
         // term 1 
         double num_1   = 2.*M*beta_sq*gamma*gamma; 
         double den_1   = I; 
         double T1      = log(num_1/den_1); 
         // term 2 
         double num_2   = xi; 
         double den_2   = I; 
         double T2      = log(num_2/den_2); 
         // term 3 
         double T3      = j; 
         // term 4 
         double T4      = (-1.)*beta_sq; 
         // term 5      
         double T5      = (-1.)*delta;
         // put it together 
         double res     = xi*(T1+T2+T3+T4+T5);
	 // To randomize, throw as Landau(res,xi) => xi is the width
         TRandom3 *myRand = new TRandom3(0); // random seed 
	 double res_rand=0; 
         if(isRndm){
	    res_rand = myRand->Landau(res,xi);
	    res      = res_rand;
         }
	 delete myRand; 
	 return res; 
      } 
      //___________________________________________________________________________________
      double GetBremss_Loss_Inexact_rndm(const double E,const double bt){
	 // Inexact form for Bremsstrahlung energy loss
         double r  = ((double)rand()/RAND_MAX); 
         double dE = E*pow(r,1./bt);
	 return dE; 
      }
      //___________________________________________________________________________________
      double GetBremss_Loss_Inexact_pdf(const double dE,const double E,const double bt){
	 // Inexact form for Bremsstrahlung energy loss
         double x = dE/E;
         double f = bt*pow(x,bt-1.);
	 return f; 
      }
      //___________________________________________________________________________________
      double GetBremss_Loss_Exact_pdf(const double dE,const double E,const double bt){
	 // Exact form for Bremsstrahlung energy loss (probability density function) 
         // input: E = incident particle energy; bt = b*t, b = kinematic constant, t = material thickness (#X0)  
         double x = dE/E; 
	 double f = (bt/E)*(1. + 0.5772*bt)*pow(x,bt-1.)*(1. - x + (3./4.)*x*x); 
	 return f; 
      }
      //___________________________________________________________________________________
      double GetBremss_Loss_Exact_rndm(const double E,const double bt){
	 // Exact form for Bremsstrahlung energy loss
         // - input: E = incident particle energy; bt = b*t, b = kinematic constant, t = material thickness (#X0) 
         // - output: energy loss in units equivalent to E's units   
	 // Description 
         // - uses the accept/reject method to sample the real distribution 
	 // - exact function:      f(x) = (bt/E)*(1 + 0.5772*bt)*x^{bt-1}*(1 - x + (3/4)*x*x), x = (Delta E)/E 
	 // - test function:       g(x) = bt*x^{bt-1}                                                                 
	 // - comparison function: h(x) = f(x)/g(x)
	 // - maximum of h:        c    = (1/E)*(1 + 0.5772*bt)*(7/4); factor of 7/4 arises from looking at h(x) for x = 1 
	 // - MC function:         H(x) = h(x)/c = 1 - x + (3/4)*x*x 
	 // For more details, see functions (below):
	 // - bremss_getRndmNumG, bremss_getH 
	 // - Approximate time accumulated due to do-while loop: ~1.751E-04 sec

	 double X=0,U=0,H=0;
	 do{
	    X = bremss_getRndmNumG(bt);     // random variable X according to g(x) on [0,1]  
            U = ((double)rand()/RAND_MAX);  // random variable according to uniform distribution on [0,1] 
	    H = bremss_getH(X);
	 }while(U>H);

	 // we found the random variable X, distributed according to the exact function 
	 // on 0 < X < 1.  Now, since it's equal to (Delta E)/E, we multiply by the 
	 // energy E
	 double result = E*X;
	 return result;
      }
      //___________________________________________________________________________________
      double bremss_getRndmNumG(const double bt){
	 // random number distributed according to the test function
	 // g(x) = bt*x^{bt-1} 
         double r = ((double)rand()/RAND_MAX); 
	 double f = pow(r,1./bt);
	 return f;
      }
      //___________________________________________________________________________________
      double bremss_getH(const double x){
	 // ratio of exact function to test function, scaled by the maximum value 
         // maximum occurs for x = 1 => factor of 4/7 shows up here 
	 double h = (1. - x + (3./4.)*x*x)*(4./7.);
	 // double h = (1. - x + (3./4.)*x*x);
	 return h;
      }
      //___________________________________________________________________________________
      double bremss_geth(const double x,const double E,const double bt){
         // h(x,E,bt) = f(x,E,bt)/g(x) 
         double h = (1./E)*(1. + 0.5772*bt)*(1. - x + (3./4.)*x*x);
	 return h;
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
         double beta_sq = 1. - M*M/(E*E);
         double beta  = sqrt(beta_sq); 
         double gamma = 1./sqrt(1.-beta_sq); 
         double delta = GetDelta(mat,beta*gamma);
         // Max energy transfer in single collision 
         double Tmax  = M*(gamma-1.)/2.; 
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
