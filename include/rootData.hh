#ifndef UTIL_DF_ROOTDATA_HH
#define UTIL_DF_ROOTDATA_HH

// a useful data struct for containing 
// strings that describe a custom ROOT file 

#include "TString.h"

namespace util_df { 
   typedef struct rootData { 
      TString fileName;          // name of file; includes full path!
      TString treeName;          // name of the ROOT tree 
      TString branchName;        // name of the ROOT branch 
      TString leafStructure;     // structure of the leaves of the branch 
   } rootData_t; 
} //::util_df

#endif 
