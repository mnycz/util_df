#ifndef UTIL_DF_MATERIAL_HH
#define UTIL_DF_MATERIAL_HH

// material struct to make energy loss calcs easier to manage
#include <cstdlib>
#include <string>  

#include "UtilDFConstants.hh"

namespace util_df {
   typedef struct material {
      std::string name;         // name of material
      double A;                 // molecular mass (g/mol) 
      double Z;                 // mass number (number of protons) 
      double rho;               // density (g/cm^3) 
      double length;            // length or thickness of material (cm) 
      double radLength;         // radiation length (g/cm^2) 
      int ID;                   // material ID (for density corrections) 
      // constructor 
      material(): 
	 name("NONE"),A(0),Z(0),rho(0),length(0),radLength(0),ID(-1) 
      {} 
   } material_t; 
}

#endif 
