#ifndef UTIL_DF_CONSTANTS_HH
#define UTIL_DF_CONSTANTS_HH

// constants and enumerated types 

namespace util_df {
 
   namespace Constants {

      enum freqType{
	 Hz  = 0,
	 kHz = 1,
	 MHz = 2,
	 GHz = 3,
         ppm = 4,
	 ppb = 5 
      }; 

      enum statsType {
	 kBesselsCorrectionDisabled = 0,
	 kBesselsCorrectionEnabled  = 1 
      }; 

   } //::constants 

} //::util_df

#endif 
