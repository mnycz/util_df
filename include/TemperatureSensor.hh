#ifndef TEMPERATURE_SENSOR_H 
#define TEMPERATURE_SENSOR_H

// a class for a temperature sensor  

#include <cstdlib>
#include <vector> 
#include <string>

#include "TSpline.h"

#include "UtilDFFunc.hh"
#include "UtilDFMath.hh"
#include "UtilDFGraph.hh"
#include "UtilDFAlgorithm.hh"
#include "UtilDFImport.hh"

namespace util_df{
      //______________________________________________________________________________
      class TemperatureSensor{
	 private:
	    bool fDataLoaded;
	    std::string fName,fPrefix;
	    std::vector<double> fT,fR;
	    int LoadData();

	 public:
	    TemperatureSensor(std::string sensorName="UNKNOWN");
	    ~TemperatureSensor();

	    void ClearData();
	    void SetName(std::string name)     { fName   = name; }
	    void SetDataPath(std::string path) { fPrefix = path; }

	    std::string GetName()        const { return fName;   }
	    double GetTemperature(double r);
	    double GetTemperature_splineFit(double r);

      };
} //::util_df

#endif  
