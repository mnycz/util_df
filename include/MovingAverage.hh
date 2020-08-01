#ifndef UTIL_DF_MOVING_AVERAGE_HH 
#define UTIL_DF_MOVING_AVERAGE_HH

// calculate a moving average on data
#include <cstdlib>
#include <vector>  

namespace util_df {
   namespace algorithm { 

      template <class T> 
	 class MovingAverage{

	    private: 
	       int fPeriod;
	       std::vector<T> fData;

	    public: 
	       MovingAverage<T>(int p=1){ fPeriod = p; }
	       ~MovingAverage(){ ClearData(); } 

	       void ClearData()            { fData.clear();  }
	       void SetPeriod(int p)       { fPeriod = p;    }

               int GetPeriod()       const { return fPeriod; }  

	       T GetUpdatedAverage(T nextVal){
		  fData.push_back(nextVal);
		  int size = fData.size();

		  T avg=0;
                  T sum=0;
		  for(int i=0;i<size;i++) sum += fData[i];
		  if(size>=fPeriod){
		     // hit our limit of entries, get the average  
		     avg = sum/( (T)fPeriod );
		     fData.erase( fData.begin() );   // pop off the first (oldest) value in the vector 
		  }else{
		     // should return something even if we don't have the right number of events 
		     avg = sum/( (T)size );
		  }
		  return avg;
	       }
	 }; 

   } //::algorithm   
} //::util_df 

#endif 
