// test out reading a JSON file 

#include <cstdlib>
#include <iostream> 
#include <fstream> 

#include "gm2fieldImport.h"

int JSON(){

   std::string PREFIX = "/home/rosofsky/gm2fieldrootana/JsonFiles"; 
   char path[500]; 
   sprintf(path,"%s/fixed-probe-azi-positions.json",PREFIX.c_str());
   std::string inpath = path; 

   json fxprPos;

   int rc = gm2fieldUtil::Import::ImportJSON(inpath,fxprPos);
   if(rc!=0) return 1; 

   char probeIndex[10];

   const int N = fxprPos.size();
   std::cout << "Found " << N << " entries" << std::endl;
   for(int i=0;i<N;i++){
      sprintf(probeIndex,"%d",i);
      std::cout << Form("probe %d, angle = %.3lf deg",i,(double)fxprPos[probeIndex]) << std::endl;
   } 

   return 0;

}

