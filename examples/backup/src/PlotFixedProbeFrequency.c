#include <iostream>

//project includes                                                                                
#include "RootTreeStructs.h"
#include "gm2fieldConstants.h"
#include "gm2fieldGraph.h"
#include "gm2fieldMath.h"
#include "gm2fieldRootHelper.h"
#include "gm2fieldImport.h"

int PlotFixedProbeFrequency(){

  int run;
  std::cout << "Enter run number: ";
  std::cin >> run;

  int probe;
  std::cout << "Enter fixed probe number: ";
  std::cin >> probe;

  int method = gm2fieldUtil::Constants::kPhaseDerivative;

  //Get the data                                                      
  std::vector<gm2field::fixedProbeFrequency_t> freq;
  int rc = gm2fieldUtil::RootHelper::GetFPFrequencies(run, freq);
  if(rc != 0){
    std::cout << "No data. Exiting." << std::endl;
    return 1;
  }

  TGraph *g = gm2fieldUtil::Graph::GetTGraph(probe,method,"GpsTimeStamp","Frequency",freq); //Takes probe number, frequency method, x axis string, y axis string, vector of data
  gm2fieldUtil::Graph::SetGraphParameters(g, 20, kBlack); //Takes graph, marker style, marker color
  gm2fieldUtil::Graph::SetGraphLabels(g,"Fixed Probe Frequency","","Freq. (Hz)"); //takes graph, then title, x, y strings
  gm2fieldUtil::Graph::SetGraphLabelSizes(g,0.03,0.03,1.5); //Takes graph, x and y label sizes, label offset
  gm2fieldUtil::Graph::UseTimeDisplay(g);
  g->Draw("ap");
  
  return 0;
  
}
