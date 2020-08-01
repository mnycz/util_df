#ifndef GM2_FIELD_EXPORT_H
#define GM2_FIELD_EXPORT_H

// miscellaneous export functions

#include <cstdlib> 
#include <iostream>
#include <fstream>
#include <vector>  

#include "TFile.h"
#include "TTree.h"

#include "rootData.hh"

namespace util_df {
   namespace Export {
      // templated functions 
      //______________________________________________________________________________
      template <typename T>
	 int PrintData1_bin(const char *outpath,std::vector<T> x,bool isDebug=false){
            // print a vector of ints, doubles, floats, unsigned ints, etc (except for strings!)
            // to a binary file 
	    std::ofstream outfile;
	    outfile.open(outpath,std::ios::out|std::ios::binary);

	    if( outfile.fail() ){
	       if(isDebug) std::cout << "Cannot open the file: " << outpath << std::endl;
	       return 1;
	    }else{
	       outfile.write( (char *)(&x[0]),x.size()*sizeof(T) );
	       outfile.close();
	    }
	    return 0;
	 }
      //______________________________________________________________________________
      template <typename T>
	 int PrintToROOTFile(rootData_t rfData,std::vector<T> v){
	    // write data to a ROOT file

	    // create the ROOT file 
	    TFile *myFile = new TFile(rfData.fileName,"RECREATE");

	    // create a TTree 
	    TTree *myTree = new TTree(rfData.treeName,rfData.treeName);
	    myTree->Branch(rfData.branchName,&v[0],rfData.leafStructure);

	    // fill the tree
	    int size = v.size();
	    for(int i=0;i<size;i++){
	       myTree->SetBranchAddress(rfData.branchName,&v[i]);
	       myTree->Fill();
	       myFile->Write();
	    }

	    // close the file 
	    myFile->Close();
	    return 0;
	 }
      //______________________________________________________________________________
   } // ::Export 
} // ::util_df

#endif 
