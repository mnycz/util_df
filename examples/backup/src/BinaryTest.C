// test out writing and reading from a binary file

#include <cstdlib>
#include <vector>
#include <string> 

#include "gm2fieldImport.h"
#include "gm2fieldExport.h"

int BinaryTest(){

   std::vector<double> x,y;

   const int N = 10;
   for(int i=0;i<N;i++) x.push_back( (double)(i+1) );

   std::string outpath = "test-out.bin";
   int rc = gm2fieldUtil::Export::PrintData1_bin<double>(outpath.c_str(),x);

   rc = gm2fieldUtil::Import::ImportData1_bin<double>(outpath.c_str(),y);

   std::cout << "vector comparison: " << std::endl;
   for(int i=0;i<N;i++) std::cout << Form("i = %d, printed = %.3lf, read = %.3lf",i,x[i],y[i]) << std::endl;

   return 0;
}
