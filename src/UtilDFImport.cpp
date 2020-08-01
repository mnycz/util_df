#include "UtilDFImport.hh"
//______________________________________________________________________________
namespace util_df{
   namespace Import{
      //______________________________________________________________________________
      int GetRunList(std::vector<int> &Run){
	
	 std::string runStr;
	 std::cout << "Enter run numbers separated by a space: ";
	 std::getline(std::cin,runStr);

	 // parse the string 
	 std::istringstream in(runStr);
	 std::vector<std::string> token = std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>());

	 // check what we got 
	 int arg=0;
	 const int N = token.size();
	 if(N==0){
	    std::cout << "Error!  No runs found!" << std::endl;
	    return 1;
	 }

	 // fill the run vector 
	 for(int i=0;i<N;i++){
	    arg = std::atoi( token[i].c_str() );
	    Run.push_back(arg);
	 }

	 return 0;
      }
      //______________________________________________________________________________
      int ImportJSON(std::string inpath,json &jObj){
	 std::ifstream infile;
	 infile.open(inpath);
	 if( infile.fail() ){ 
	    std::cout << "[util_df::Import::ImportJSON]: Cannot open the file: " << inpath << std::endl;
	    return 1;
	 }else{
	    infile >> jObj;
	 }
         return 0; 
      }

   } //::Import
} //::util_df
