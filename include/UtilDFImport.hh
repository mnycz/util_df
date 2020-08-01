#ifndef UTIL_DF_IMPORT_HH
#define UTIL_DF_IMPORT_HH

// miscellaneous import functions (csv and tsv)  

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <sstream>
#include <iterator>  

#include "TFile.h"
#include "TTree.h"

#include "json.hh"

#include "rootData.hh"
#include "UtilDFAlgorithm.hh"

using json = nlohmann::json; 

namespace util_df{
   namespace Import{
      // templated functions
      //______________________________________________________________________________
      template <typename T>
	 int ImportData1_bin(const char *inpath,std::vector<T> &x,bool isDebug=false){
	    // read a binary file into a vector of ints, doubles, unsigned ints (all except for strings!) 
	    std::ifstream infile;
	    infile.open(inpath,std::ios::in | std::ios::binary | std::ios::ate);

	    std::streampos size;
	    char *memblock = new char[200];

	    if( infile.fail() ){
	       if(isDebug) std::cout << "[util_df::Import::ImportData1_bin]: Cannot open the file: " << inpath << std::endl;
	       return 1;
	    }else{
	       if( infile.is_open() ){
		  delete[] memblock;
		  size = infile.tellg();
		  memblock = new char[size];
		  infile.seekg(0,std::ios::beg);
		  infile.read(memblock,size);
		  infile.close();
	       }
	    }

	    T *arr = new T[size];
	    memcpy(arr,(T *)memblock,size);

            int NBYTES=0;
	    if( std::is_integral<T>::value ){
	       // type is integer or boolean 
	       NBYTES = 2;
	    }else{
	       // type is a double or float 
	       NBYTES = 8;
	    }

	    const int NN = size/NBYTES;
	    for(int i=0;i<NN;i++) x.push_back( arr[i] );

	    delete[] memblock;
	    delete[] arr;

	    return 0;
	 }
      // generalized csv input 
      //______________________________________________________________________________
      template <typename T>
	 int ImportData1(std::string inpath,std::string delim,std::vector<T> &x){
	    // simple function to import a 1D vector
	    // file format doesn't necessarily matter, but let's do this for consistency  
	    if( delim.compare("csv")!=0 && delim.compare("tsv")!=0 ) {
	       std::cout << "[util_df::Import::ImportData1]: Invalid file type " << delim << std::endl;
	       return 1;
	    }
	    // open the file and read in data 
	    T ix;
	    std::ifstream infile;
	    infile.open(inpath.c_str());
	    if( infile.fail() ){
	       std::cout << "[util_df::Import::ImportData1]: Cannot open the file: " << inpath << std::endl;
	       return 1;
	    }else{
	       while( !infile.eof() ){
		  infile >> ix;
		  x.push_back(ix);
	       }
	       infile.close();
	       x.pop_back();
	    }
	    return 0;
	 }
      //______________________________________________________________________________
      template <typename T1,typename T2>
	 int ImportData2(std::string inpath,std::string delim,std::vector<T1> &x1,std::vector<T2> &x2){
	    // check file type 
	    int isCSV=0;
	    if( delim.compare("csv")==0 ) isCSV = 1;

	    if( delim.compare("csv")!=0 && delim.compare("tsv")!=0 ) {
	       std::cout << "[util_df::Import::ImportData2]: Invalid file type " << delim << std::endl;
	       return 1;
	    }
	    // open file and read in data 
	    int rc=0;
	    std::string sx1,sx2;
	    T1 ix1;
	    T2 ix2;
	    std::ifstream infile;
	    infile.open(inpath.c_str());
	    if( infile.fail() ){
	       std::cout << "[util_df::Import::ImportData2]: Cannot open the file: " << inpath << std::endl;
	       return 1;
	    }else{
	       while( !infile.eof() ){
		  if(isCSV){
		     std::getline(infile,sx1,',');
		     std::getline(infile,sx2);
		     rc = Algorithm::Convert<T1>(sx1,ix1);
		     rc = Algorithm::Convert<T2>(sx2,ix2);
		     // FIXME: how to handle strings??
		     x1.push_back(ix1);
		     x2.push_back(ix2);
		  }else{
		     infile >> ix1 >> ix2;
		     x1.push_back(ix1);
		     x2.push_back(ix2);
		  }
	       }
	       infile.close();
	       x1.pop_back();
	       x2.pop_back();
	    }
	    return rc;
	 }
      //______________________________________________________________________________                          
      template <typename T1,typename T2,typename T3>
	int ImportData3(std::string inpath,std::string delim,std::vector<T1> &x1,std::vector<T2> &x2, std::vector<T3> &x3){
	// check file type                                                                                      
	int isCSV=0;
	if( delim.compare("csv")==0 ) isCSV = 1;

	if( delim.compare("csv")!=0 && delim.compare("tsv")!=0 ) {
	  std::cout << "[util_df::Import::ImportData3]: Invalid file type " << delim << std::endl;
	  return 1;
	}
	// open file and read in data                                                                           
	int rc=0;
	std::string sx1,sx2,sx3;
	T1 ix1;
	T2 ix2;
	T3 ix3;
	std::ifstream infile;
	infile.open(inpath.c_str());
	if( infile.fail() ){
	  std::cout << "[util_df::Import::ImportData3]: Cannot open the file: " << inpath << std::endl;
	  return 1;
	}else{
	  while( !infile.eof() ){
	    if(isCSV){
	      std::getline(infile,sx1,',');
	      std::getline(infile,sx2,',');
	      std::getline(infile,sx3);
	      rc = Algorithm::Convert<T1>(sx1,ix1);
	      rc = Algorithm::Convert<T2>(sx2,ix2);
	      rc = Algorithm::Convert<T3>(sx3,ix3);
	      // FIXME: how to handle strings??                                                              
	      x1.push_back(ix1);
	      x2.push_back(ix2);
	      x3.push_back(ix3);
	    }else{
	      infile >> ix1 >> ix2 >> ix3;
	      x1.push_back(ix1);
	      x2.push_back(ix2);
	      x3.push_back(ix3);
	    }
	  }
	  infile.close();
	  x1.pop_back();
	  x2.pop_back();
	  x3.pop_back();
	}
	return rc;
      }
      //______________________________________________________________________________
      template <typename T>
	 int ImportROOTFile(rootData_t rfData,std::vector<T> &v){
	    // load data from a ROOT file

	    // create the ROOT file 
	    TFile *myFile = NULL;
	    myFile = new TFile(rfData.fileName);

	    ULong64_t bytesRead = myFile->GetBytesRead();
	    if(bytesRead==0){
	       std::cout << "Error: No bytes read from file: " << rfData.fileName << "." << std::endl;
	       return 1;
	    }

	    // need a struct to fill our vector 
	    T x;

	    // create a TTree 
	    TTree *myTree = (TTree *)myFile->Get(rfData.treeName);
	    myTree->SetBranchAddress(rfData.branchName,&x);

	    // fill the tree
	    int size = myTree->GetEntries();
	    for(int i=0;i<size;i++){
	       myTree->GetEntry(i);
	       v.push_back(x);
	    }

	    delete myTree;
	    delete myFile;

	    return 0;
	 }
      //_______________________________________________________________________________
      // non-templated functions 
      int GetRunList(std::vector<int> &Run); 
      int ImportJSON(std::string inpath,json &jObj);

   } // ::import
} // ::util_df

#endif 
