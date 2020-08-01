#ifndef UTIL_DF_FUNC_HH
#define UTIL_DF_FUNC_HH

// miscellaneous functions that are helpful

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <sstream>
#include <iterator> 
#include <sys/stat.h> 
#include <dirent.h>

namespace util_df{
   std::string GetStringTimeStampFromUTC(unsigned long unix_time); 
   unsigned long int GetUTCTimeStampFromString(std::string timeStamp,bool isDST=false);
   int MakeDirectory(const char *path); 
   int SplitString(const char delim,const std::string myStr,std::vector<std::string> &out); 
} // ::util_df

#endif 