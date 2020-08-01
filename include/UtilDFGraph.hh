#ifndef UTIL_DF_GRAPH_HH
#define UTIL_DF_GRAPH_HH

#include <cstdlib>
#include <vector> 

#include "TString.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TGraphPolar.h"
#include "TLegend.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"

namespace util_df { 

   namespace Graph {

      // ROOT only has the first four, so we add all of them here. 
      enum lineStyle{
	 kSolidLine           = 1,
	 kDashLine            = 2,
	 kDotLine             = 3,
	 kShortDashDotLine    = 4,
	 kLongDashDotLine     = 5,
	 kDashTripleDotLine   = 6,
	 kLongDashLine        = 7,
	 kDashDoubleDotLine   = 8,
	 KLongLongDashLine    = 9,
	 kLongLongDashDotLine = 10
      };

      TGraph *GetTGraph(std::vector<double>,std::vector<double>);
      TGraphErrors *GetTGraphErrors(std::vector<double> x,std::vector<double> y,std::vector<double> ey);
      TGraphErrors *GetTGraphErrors(std::vector<double> x,std::vector<double> ex,std::vector<double> y,std::vector<double> ey);
      TGraphAsymmErrors *GetTGraphAsymmErrors(std::vector<double> x,std::vector<double> y,std::vector<double> eyh);
      TGraphAsymmErrors *GetTGraphAsymmErrors(std::vector<double> x,std::vector<double> y,std::vector<double> eyl,std::vector<double> eyh);

      TGraph *GetTGraphDifference(const int NPTS,TGraph *g1,TGraph *g2); 

      void SetGraphParameters(TGraph *g,int Marker,int Color,int width = 1);
      void SetGraphParameters(TGraphErrors *g,int Marker,int Color,int width = 1);
      void SetGraphParameters(TGraphAsymmErrors *g,int Marker,int Color,int width = 1);
      void SetGraphLabels(TGraph *g,TString Title,TString xAxisTitle,TString yAxisTitle);
      void SetGraphLabels(TGraphErrors *g,TString Title,TString xAxisTitle,TString yAxisTitle);
      void SetGraphLabels(TGraphAsymmErrors *g,TString Title,TString xAxisTitle,TString yAxisTitle);
      void SetGraphLabels(TMultiGraph *g,TString Title,TString xAxisTitle,TString yAxisTitle);
      void SetGraphLabelSizes(TGraph *g,double xSize,double ySize,double offset=0.5);
      void SetGraphLabelSizes(TGraphErrors *g,double xSize,double ySize,double offset=0.5);
      void SetGraphLabelSizes(TGraphAsymmErrors *g,double xSize,double ySize,double offset=0.5);
      void SetGraphLabelSizes(TMultiGraph *g,double xSize,double ySize,double offset=0.5);
      void UseTimeDisplay(TGraph *g);
      void UseTimeDisplay(TGraphErrors *g);
      void UseTimeDisplay(TGraphAsymmErrors *g);
      void UseTimeDisplay(TMultiGraph *g);

   } // ::graph 

} // ::util_df

#endif 
