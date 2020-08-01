#include <iostream>

//project includes                                                                                
#include "RootTreeStructs.h"
#include "gm2fieldConstants.h"
#include "gm2fieldGraph.h"
#include "gm2fieldMath.h"
#include "gm2fieldRootHelper.h"
#include "gm2fieldImport.h"

int GetStats(int multipole,int method,std::vector<gm2field::trolleyFieldMultipole_t> data,double &mean,double &stdev); 

int PlotTrolleyMultipoles(){

  int run;
  std::cout << "Enter run number: ";
  std::cin >> run;

  string multipole;
  std::cout << "Which multipole? (Dipole, NormQuad, SkewQuad, NormSext, SkewSext, NormOctu, SkewOctu, NormDecu, SkewDecu) ";
  std::cin >> multipole;

  int mp=-1; 
  if( multipole.compare("Dipole")==0   ) mp = gm2fieldUtil::Constants::kDipole;  
  if( multipole.compare("NormQuad")==0 ) mp = gm2fieldUtil::Constants::kNormQuad;  
  if( multipole.compare("SkewQuad")==0 ) mp = gm2fieldUtil::Constants::kSkewQuad;  
  if( multipole.compare("NormSext")==0 ) mp = gm2fieldUtil::Constants::kNormSext;  
  if( multipole.compare("SkewSext")==0 ) mp = gm2fieldUtil::Constants::kSkewSext;  
  if( multipole.compare("NormOctu")==0 ) mp = gm2fieldUtil::Constants::kNormOctu;  
  if( multipole.compare("SkewOctu")==0 ) mp = gm2fieldUtil::Constants::kSkewOctu;  
  if( multipole.compare("NormDecu")==0 ) mp = gm2fieldUtil::Constants::kNormDecu;  
  if( multipole.compare("SkewDecu")==0 ) mp = gm2fieldUtil::Constants::kSkewDecu;  

  gm2fieldUtil::Graph::aziUnits  = gm2fieldUtil::Constants::Degrees; //Want plots to be in degrees
  gm2fieldUtil::Graph::freqUnits = gm2fieldUtil::Constants::ppm; 
  int method = gm2fieldUtil::Constants::kPhaseDerivative;

  //Get the data                                                      
  std::vector<gm2field::trolleyPosition_t> pos;
  std::vector<gm2field::trolleyFieldMultipole_t> mult;

  int rc;

  rc = gm2fieldUtil::RootHelper::GetTrolleyPosition(run, pos);
  if(rc != 0){
    std::cout << "No data. Exiting." << std::endl;
    return 1;
  }

  rc = gm2fieldUtil::RootHelper::GetTrolleyMultipoles(run, mult);
  if(rc != 0){
    std::cout << "No data. Exiting." << std::endl;
    return 1;
  }

  std::string units; 
  double mean=0,stdev=0;
  rc = GetStats(mp,method,mult,mean,stdev);

  std::cout << Form("multipole: %s, mean = %.3lf Hz, stdev = %3lf Hz",multipole.c_str(),mean,stdev); 

  TGraph *g = gm2fieldUtil::Graph::GetTGraph(method, "Phi",multipole.c_str(),pos,mult); //Takes method, x and y axis strings, position data, multipole data
  gm2fieldUtil::Graph::SetGraphParameters(g, 20, kBlack); //Takes graph, marker style, marker color
  g->SetMarkerSize(0.8); 
  std::string graphTitle = "Trolley " + multipole;
  std::string yTitle = multipole + " (ppm)";
  gm2fieldUtil::Graph::SetGraphLabels(g,graphTitle.c_str(),"Azimuthal Location (deg.)",yTitle.c_str()); //takes graph, then title, x, y strings
  gm2fieldUtil::Graph::SetGraphLabelSizes(g,0.035,0.035,1.25); //Takes graph, x and y label sizes, label offset
  g->Draw("ap");
  
  return 0;
  
}
//______________________________________________________________________________
int GetStats(int multipole,int method,std::vector<gm2field::trolleyFieldMultipole_t> data,double &mean,double &stdev){
   const int N = data.size();
   std::vector<double> x; 
   for(int i=0;i<N;i++){
      x.push_back( data[i].Multipole[multipole][method] );
   }
   mean  = gm2fieldUtil::Math::GetMean<double>(x); 
   stdev = gm2fieldUtil::Math::GetStandardDeviation<double>(x);
   return 0;
}
