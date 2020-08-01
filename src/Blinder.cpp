#include "Blinder.hh"
namespace util_df { 
   //______________________________________________________________________________
   Blinder::Blinder(std::string label,double mag,int units){
      std::string PREFIX = "NONE";  
      fLabel             = label;   
      fBlindPath         = PREFIX + "/" + fLabel + ".bin"; 
      // make the output directory if necessary 
      int rc = MakeDirectory( PREFIX.c_str() );
      // set blinding scale details   
      fBlindMagnitude = mag; 
      fBlindUnits     = units; 
      // initalize any pointers 
      fRand = new TRandom3(0);  // seed of zero ensures randomness
   }
   //______________________________________________________________________________
   Blinder::~Blinder(){
      fBlindValue.clear();
      delete fRand;
   }
   //______________________________________________________________________________
   int Blinder::ReadData(){
      // read in the blinded value from a file  
      std::vector<double> x;
      int rc = Import::ImportData1_bin<double>(fBlindPath.c_str(),x); 
      if(rc!=0) return rc;  // read failed; return   

      // zeroth index are the units the user chose 
      fBlindUnits = (int)x[0]; 

      int N = x.size();
      if(N!=5){
	 // should be getting two pairs of values ordered as (Hz,units)  
	 // if not, print a warning  
	 std::cout << "[Blinder::ReadData]: WARNING! Something looks wrong!";
	 rc = 1;
      }else{
	 // clear and fill the blindValue vector; start at index 1 
	 // since the zeroth index is the units the user chose 
	 fBlindValue.clear();
	 for(int i=1;i<N;i++) fBlindValue.push_back(x[i]);
	 rc = 0;
      }

      return rc;  
   }
   //______________________________________________________________________________
   int Blinder::WriteData(){
      // fill a vector to write to file 
      std::vector<double> x; 
      x.push_back( (double)fBlindUnits ); 
      const int N = fBlindValue.size();
      for(int i=0;i<N;i++) x.push_back(fBlindValue[i]); 
      // now write to file
      int rc = Export::PrintData1_bin<double>(fBlindPath.c_str(),x);
      return rc;
   }
   //______________________________________________________________________________
   int Blinder::GenerateBlinding(){
      // here we generate the blind value using our TRandom3 object
      // and the blind scale set by the user 
      double sf=0;
      if(fBlindUnits==Constants::Hz){
	 sf = 1.;
      }else if(fBlindUnits==Constants::kHz){
	 sf = 1E+3;
      }else if(fBlindUnits==Constants::ppm){
	 sf = 61.79; 
      }else if(fBlindUnits==Constants::ppb){
	 sf = 0.06179; 
      }else{
	 std::cout << "[Blinder::GenerateBlinding]: WARNING! Invalid units, defaulting to Hz." << std::endl;
	 sf = 1.;  
      }

      // compute range for blind in HERTZ first  
      // use a uniform flat distribution set on +/- BlindMagnitude
      // calulate two pairs of blind values in the ordering (Hz,units) 
      double range   = sf*fBlindMagnitude; 
      double r1      = fRand->Rndm();
      double val1_Hz = (-1.)*range + 2.*range*r1;
      double r2      = fRand->Rndm();
      double val2_Hz = (-1.)*range + 2.*range*r2;

      // now compute the blind in the units that the user gave 
      // in case they want to do things in ppm, ppb...  
      double val1_units = val1_Hz/sf;
      double val2_units = val2_Hz/sf;

      // be sure the vector is empty 
      fBlindValue.clear();
      // fill the vector with the blind values 
      fBlindValue.push_back(val1_Hz); 
      fBlindValue.push_back(val1_units);
      fBlindValue.push_back(val2_Hz); 
      fBlindValue.push_back(val2_units);

      int rc = WriteData();  

      return rc; 
   }
   //______________________________________________________________________________
   double Blinder::GetBlinding(int type,int units){
      // try to read blind in from the (pre-generated) file  
      int rc = ReadData();
      if(rc!=0){
	 // no file found, generate a blind value 
	 rc = GenerateBlinding();
      }   

      int index=-1; 
      if(type==1){
	 // user wants the first blind value
	 if(units==Constants::Hz){
	    // the user wants the value in Hz
	    index = 0;
	 }else{
	    // the user wants the value in their units  
	    index = 1;
	 }
      }else if(type==2){
	 // user wants the second blind value
	 if(units==Constants::Hz){
	    // the user wants the value in Hz
	    index = 2;
	 }else{
	    // the user wants the value in their units  
	    index = 3;
	 }
      }else{
	 std::cout << "[Blinder::GetBlinding]: Invalid type " << type << "! Defaulting to the first type." << std::endl;
	 if(units==Constants::Hz){
	    // the user wants the value in Hz
	    index = 0;
	 }else{
	    // the user wants the value in their units  
	    index = 1;
	 }
      }

      double blind = fBlindValue[index];

      return blind; 
   }

} // ::util_df
