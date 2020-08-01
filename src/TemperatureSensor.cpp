#include "TemperatureSensor.hh"
//______________________________________________________________________________
namespace util_df{
   //______________________________________________________________________________
   TemperatureSensor::TemperatureSensor(std::string sensorName){
      fName       = sensorName;
      fPrefix     = "./input/";
      ClearData();
   }
   //______________________________________________________________________________
   TemperatureSensor::~TemperatureSensor(){
      ClearData();
   }
   //______________________________________________________________________________
   void TemperatureSensor::ClearData(){
      fDataLoaded = false;
      fR.clear();
      fT.clear();
   }
   //______________________________________________________________________________
   int TemperatureSensor::LoadData(){
      std::string fileType = "csv";
      std::string inpath   = fPrefix + "/" + fName + "." + fileType;
      int rc = Import::ImportData2<double,double>(inpath,fileType,fT,fR);
      if(rc==0){
	 if(fName.compare("USP17464")==0){
	    // this data set is backwards from the PT1000 data  
	    Algorithm::ReverseVector<double>(fT);
	    Algorithm::ReverseVector<double>(fR);
	 }
	 fDataLoaded = true;
      }
      return rc;
   }
   //______________________________________________________________________________
   double TemperatureSensor::GetTemperature(double resistance){
      // get temperature 
      int rc=0;
      if(!fDataLoaded) rc = LoadData();
      if(rc!=0){
	 std::cout << "[TemperatureSensor]: No data!" << std::endl;
	 return -100;
      }
      int lo=0,hi=0;
      Algorithm::BinarySearch<double>(fR,resistance,lo,hi);
      // linear interpolation on (R_ref,T_ref) to find T
      double temp = Math::LinearInterpolation(resistance,fR[lo],fT[lo],fR[hi],fT[hi]);
      return temp;
   }
   //______________________________________________________________________________
   double TemperatureSensor::GetTemperature_splineFit(double resistance){
      // get temperature using a spline fit to the data  
      int rc=0;
      if(!fDataLoaded) rc = LoadData();
      if(rc!=0){
	 std::cout << "[TemperatureSensor]: No data!" << std::endl;
	 return -100;
      }
      int lo=0,hi=0;
      Algorithm::BinarySearch<double>(fR,resistance,lo,hi);
      // determine data points to fit
      const int N = fR.size();
      int step  = 10;
      int start = lo - step; 
      int stop  = hi + step;
      // bounds check  
      if(start<0) start = 0;
      if(stop>N) stop   = N-1;
      // accumulate data 
      std::vector<double> x,y;
      for(int i=start;i<stop;i++){
	 x.push_back(fR[i]); 
	 y.push_back(fT[i]); 
      }
      // create spline fit
      TGraph *g    = Graph::GetTGraph(x,y);
      TSpline3 *gs = new TSpline3("gs",g); 
      // linear interpolation on (R_ref,T_ref) to find T
      double temp = gs->Eval(resistance);
      delete gs; 
      delete g; 
      return temp;
   }
} //::util_df
