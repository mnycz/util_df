// Test the UtilDF library 

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

#include "CSVManager.hh"
#include "UtilDFGraph.hh"

int Test(){

   util_df::CSVManager *myCSV = new util_df::CSVManager(); 
   myCSV->ReadFile("data.csv",true); 

   std::vector<std::string> header;
   myCSV->GetHeader(header); 
   std::string xAxisLabel = header[0]; 
   std::string yAxisLabel = header[1]; 

   std::vector<double> x,y;
   myCSV->GetColumn_byName<double>(xAxisLabel,x); 
   myCSV->GetColumn_byName<double>(yAxisLabel,y); 
   
   TGraph *g = util_df::Graph::GetTGraph(x,y); 
   util_df::Graph::SetGraphParameters(g,20,kBlue);

   TCanvas *c1 = new TCanvas("c1","Data",500,500);

   c1->cd();
   g->Draw("ap");
   util_df::Graph::SetGraphLabels(g,"Test Data",xAxisLabel,yAxisLabel);
   g->Draw("ap");
   c1->Update();

   delete myCSV;
   return 0;
}
