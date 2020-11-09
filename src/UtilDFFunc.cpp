#include "UtilDFFunc.hh"
//______________________________________________________________________________
namespace util_df {
   int SplitString_whiteSpace(const std::string myStr,std::vector<std::string> &out){
      std::istringstream buffer(myStr);
      std::copy(std::istream_iterator<std::string>(buffer), 
	    std::istream_iterator<std::string>(),
	    std::back_inserter(out));
      return 0;
   }
   //______________________________________________________________________________
   int SplitString(const char delim,const std::string myStr,std::vector<std::string> &out){
      // split a string by a delimiter
      std::stringstream ss(myStr);
      std::vector<std::string> result;

      while( ss.good() ){
	 std::string substr;
	 std::getline(ss,substr,delim);
	 out.push_back(substr);
      }
      return 0;
   }
   //______________________________________________________________________________
   int MakeClass(const char *path,const char *className,const char *treeName){
      // create a class using TTree::MakeClass
      TFile *f = new TFile(path); 
      TTree *myTree; 
      f->GetObject(treeName,myTree);
      myTree->MakeClass(className);
      f->Close();
      return 0; 
   }
   //______________________________________________________________________________
   std::string GetStringTimeStampFromUTC(unsigned long unix_time){
      time_t     utime = unix_time;
      struct tm  ts;
      char       buf[100];
      // Format time as "ddd yyyy-mm-dd hh:mm:ss zzz"
      ts = *localtime(&utime);
      strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
      std::string timeStamp = buf;
      return timeStamp;
   }
   //______________________________________________________________________________
   unsigned long int GetUTCTimeStampFromString(std::string timeStamp,bool isDST){
      // takes a time stamp string and converts to UTC integer
      // returns the UTC time in SECONDS
      // note the format of the timestamp (ddd yyyy-mm-dd hh:mm::ss zzz)  
      char dayOfWeek[5],timeZone[5];  
      int yy,mm,dd,hour,min,sec;
      std::sscanf(timeStamp.c_str(),"%s %04d-%02d-%02d %02d:%02d:%02d %s",
                  dayOfWeek,&yy,&mm,&dd,&hour,&min,&sec,timeZone);
      struct tm timeinfo = {0};
      timeinfo.tm_year = yy-1900;  // years since 1900 
      timeinfo.tm_mon  = mm-1;     // months since january (0--11)  
      timeinfo.tm_mday = dd;
      timeinfo.tm_hour = hour;
      timeinfo.tm_min  = min;
      timeinfo.tm_sec  = sec;
      int corr = 0;
      // FIXME: there's got to be a better way to do this... 
      // int isDST = timeinfo.tm_isdst; 
      if(isDST) corr = 3600; // daylight savings time, subtract 1 hour  
      time_t timeSinceEpoch = mktime(&timeinfo) - corr;
      return timeSinceEpoch;    
   }
   //______________________________________________________________________________
   int MakeDirectory(const char *path){
      int rc=0;
      struct stat SB;

      const int SIZE = 200;
      char *dir_path = new char[SIZE];

      sprintf(dir_path,"%s",path);

      // check to see if the directory exists
      if( (stat(dir_path,&SB)==0)&&(S_ISDIR(SB.st_mode)) ){
	 // the directory exists!  Do nothing.  
	 // You can also check for other file types using other S_IS* macros:
	 // S_ISDIR — directory
	 // S_ISREG — regular file
	 // S_ISCHR — character device
	 // S_ISBLK — block device
	 // S_ISFIFO — FIFO
	 // S_ISLNK — symbolic link
	 // S_ISSOCK — socket
      }else{
	 rc = mkdir(dir_path,0700);
      }

      if(rc!=0) std::cout << "[util_df::MakeDirectory]: Cannot make the directory: " << path << std::endl;

      delete[] dir_path;

      return rc;
   }

}
