// test some algorithms 

#include "MovingAverage.h" 

#include "TRandom3.h"

int algoTest(){

   gRandom->SetSeed(0);

   const int NPTS = 100;

   int period = 5; 
   gm2fieldUtil::Algorithm::MovingAverage<double> *movAvg = new gm2fieldUtil::Algorithm::MovingAverage<double>(period);

   double min = 0, max = 100; 
   double avg = 0,value=0; 
   for(int i=0;i<NPTS;i++){
      value = min + (max-min)*gRandom->Rndm(); 
      avg = movAvg->GetUpdatedAverage(value);
      std::cout << Form("i = %02d, value = %.3lf, avg (last %d) = %.3lf",i,value,period,avg) << std::endl; 
   }

   delete movAvg;

   return 0; 

}
