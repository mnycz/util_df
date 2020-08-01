#include <iostream>

//project includes                                                                                
#include "RootTreeStructs.h"
#include "gm2fieldConstants.h"
#include "gm2fieldGraph.h"
#include "gm2fieldMath.h"
#include "gm2fieldRootHelper.h"
#include "gm2fieldImport.h"

int PlotPSFBCurrent(){

  vector<int> runs;
  gm2fieldUtil::Import::GetRunList(runs);
  int numRuns = runs.size();

  int method = gm2fieldUtil::Constants::kPhaseDerivative;

  //Get the data                                                      
  std::vector<gm2field::psFeedback_t> psfb;
  int rc;
  for(int i=0;i<numRuns;i++){
    rc = gm2fieldUtil::RootHelper::GetPSFeedbackData(runs[i], psfb);
    if(rc != 0){
      std::cout << "No data. Exiting." << std::endl;
      return 1;
    }
  }

  TGraph *g = gm2fieldUtil::Graph::GetTGraph("GpsTimeStamp","current",psfb);
  gm2fieldUtil::Graph::SetGraphParameters(g, 20, kBlack); 
  gm2fieldUtil::Graph::SetGraphLabels(g,"PS Feedback Current","","Current (mA)");
  gm2fieldUtil::Graph::SetGraphLabelSizes(g,0.03,0.03,1.5); 
  gm2fieldUtil::Graph::UseTimeDisplay(g);
  g->Draw("ap");
  
  return 0;
  
}
