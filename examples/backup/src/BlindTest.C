// test out the blinder class

#include <cstdlib>
#include <iostream>
#include <fstream>

#include "Blinder.h"

int BlindTest(){

   int blindUnits  = gm2fieldUtil::Constants::ppb;
   double blindMag = 100.;

   TString unitStr = "Hz";
   if(blindUnits==gm2fieldUtil::Constants::ppm) unitStr = "ppm";
   if(blindUnits==gm2fieldUtil::Constants::ppb) unitStr = "ppb";

   gm2fieldUtil::Blinder *tomShelby = new gm2fieldUtil::Blinder("tom",blindMag,blindUnits);
   // tomShelby->UpdateBlinding(); 

   double blindVal1_Hz    = tomShelby->GetBlinding(1);
   double blindVal1_units = tomShelby->GetBlinding(1,blindUnits);
   double blindVal2_Hz    = tomShelby->GetBlinding(2);
   double blindVal2_units = tomShelby->GetBlinding(2,blindUnits);

   std::cout << Form("The first blind value is:  %.5lf Hz (%.5lf %s)",blindVal1_Hz,blindVal1_units,unitStr.Data()) << std::endl;
   std::cout << Form("The second blind value is: %.5lf Hz (%.5lf %s)",blindVal2_Hz,blindVal2_units,unitStr.Data()) << std::endl;

   delete tomShelby;

   return 0;
}
