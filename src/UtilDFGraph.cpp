#include "UtilDFGraph.hh"
//______________________________________________________________________________
namespace util_df{
   namespace Graph{
      //______________________________________________________________________________
      TGraph *GetTGraph(std::vector<double> x,std::vector<double> y){
	 const int N = x.size();
	 TGraph *g = new TGraph(N,&x[0],&y[0]);
	 return g;
      }
      //______________________________________________________________________________
      TGraphErrors *GetTGraphErrors(std::vector<double> x,std::vector<double> y,std::vector<double> ey){
	 const int N = x.size();
	 std::vector<double> ex;
	 for(int i=0;i<N;i++) ex.push_back(0);
	 TGraphErrors *g = new TGraphErrors(N,&x[0],&y[0],&ex[0],&ey[0]);
	 return g;
      }
      //______________________________________________________________________________
      TGraphErrors *GetTGraphErrors(std::vector<double> x,std::vector<double> ex,std::vector<double> y,std::vector<double> ey){
	 const int N = x.size();
	 TGraphErrors *g = new TGraphErrors(N,&x[0],&y[0],&ex[0],&ey[0]);
	 return g;
      }
      //______________________________________________________________________________
      TGraphAsymmErrors *GetTGraphAsymmErrors(std::vector<double> x,std::vector<double> y,std::vector<double> eyh){
	 const int N = x.size();
	 std::vector<double> exl,exh,eyl;
	 for(int i=0;i<N;i++){
	    exl.push_back(0);
	    exh.push_back(0);
	    eyl.push_back(0);
	 }
	 TGraphAsymmErrors *g = new TGraphAsymmErrors(N,&x[0],&y[0],&exl[0],&exh[0],&eyl[0],&eyh[0]);
	 return g;
      }
      //______________________________________________________________________________
      TGraphAsymmErrors *GetTGraphAsymmErrors(std::vector<double> x,std::vector<double> y,std::vector<double> eyl,std::vector<double> eyh){
	 const int N = x.size();
	 std::vector<double> exl,exh;
	 for(int i=0;i<N;i++){
	    exl.push_back(0);
	    exh.push_back(0);
	 }
	 TGraphAsymmErrors *g = new TGraphAsymmErrors(N,&x[0],&y[0],&exl[0],&exh[0],&eyl[0],&eyh[0]);
	 return g;
      }
      //______________________________________________________________________________
      TGraph *GetTGraphDifference(const int NPTS,TGraph *g1,TGraph *g2){
	 // compute difference of two TGraphs  
         // find the min and max values 
	 const int N1 = g1->GetN();
	 const int N2 = g2->GetN();
	 double *x1 = g1->GetX();
	 double *x2 = g2->GetX();
         // scan the first graph 
	 double min1=5E+9,max1=-5E+9;
	 double min2=5E+9,max2=-5E+9;
	 for(int i=0;i<N1;i++){
	    if(x1[i]<min1) min1 = x1[i];
	    if(x1[i]>max1) max1 = x1[i];
	 }
         // scan the second graph 
	 for(int i=0;i<N2;i++){
	    if(x2[i]<min2) min2 = x2[i];
	    if(x2[i]>max2) max2 = x2[i];
	 }
         // get the range right if we have mismatched ranges 
	 double min = min1;
	 double max = max1;
	 if(min2>min1) min = min2;
	 if(max2>max1) max = max1;
         // evaluate at equally-spaced invervals  
	 double step = (max-min)/( (double)NPTS );
	 std::vector<double> X,Y;
	 double ix=0,iy=0;
	 for(int i=0;i<NPTS;i++){
	    ix   = min + ( (double)i )*step;
	    iy = g2->Eval(ix) - g1->Eval(ix);
	    X.push_back(ix);
	    Y.push_back(iy);
	 }
	 // get the graph
	 TGraph *g = GetTGraph(X,Y);
	 return g;
      }
      //______________________________________________________________________________
      void SetParameters(TGraph *g,int marker,int color,double mSize,int width){
	 g->SetMarkerStyle(marker);
	 g->SetMarkerColor(color);
         g->SetMarkerSize(mSize);
	 g->SetLineColor(color);
	 g->SetLineWidth(width);
      }
      //______________________________________________________________________________
      void SetParameters(TGraphErrors *g,int marker,int color,double mSize,int width){
	 g->SetMarkerStyle(marker);
	 g->SetMarkerColor(color);
         g->SetMarkerSize(mSize);
	 g->SetLineColor(color);
	 g->SetLineWidth(width);
      }
      //______________________________________________________________________________
      void SetParameters(TGraphAsymmErrors *g,int marker,int color,double mSize,int width){
	 g->SetMarkerStyle(marker);
	 g->SetMarkerColor(color);
         g->SetMarkerSize(mSize);
	 g->SetLineColor(color);
	 g->SetLineWidth(width);
      }
      //______________________________________________________________________________
      void SetLabels(TGraph *g,TString Title,TString xAxisTitle,TString yAxisTitle){
	 g->SetTitle(Title);
	 g->GetXaxis()->SetTitle(xAxisTitle);
	 g->GetXaxis()->CenterTitle();
	 g->GetYaxis()->SetTitle(yAxisTitle);
	 g->GetYaxis()->CenterTitle();
      }
      //______________________________________________________________________________
      void SetLabels(TGraphErrors *g,TString Title,TString xAxisTitle,TString yAxisTitle){
	 g->SetTitle(Title);
	 g->GetXaxis()->SetTitle(xAxisTitle);
	 g->GetXaxis()->CenterTitle();
	 g->GetYaxis()->SetTitle(yAxisTitle);
	 g->GetYaxis()->CenterTitle();
      }
      //______________________________________________________________________________
      void SetLabels(TGraphAsymmErrors *g,TString Title,TString xAxisTitle,TString yAxisTitle){
	 g->SetTitle(Title);
	 g->GetXaxis()->SetTitle(xAxisTitle);
	 g->GetXaxis()->CenterTitle();
	 g->GetYaxis()->SetTitle(yAxisTitle);
	 g->GetYaxis()->CenterTitle();
      }
      //______________________________________________________________________________
      void SetLabels(TMultiGraph *g,TString Title,TString xAxisTitle,TString yAxisTitle){
	 g->SetTitle(Title);
	 g->GetXaxis()->SetTitle(xAxisTitle);
	 g->GetXaxis()->CenterTitle();
	 g->GetYaxis()->SetTitle(yAxisTitle);
	 g->GetYaxis()->CenterTitle();
      }
      //______________________________________________________________________________
      void SetLabelSizes(TGraph *g,double xSize,double ySize,double offset){
	 g->GetXaxis()->SetTitleSize(xSize);
	 g->GetXaxis()->SetLabelSize(xSize);
	 g->GetYaxis()->SetTitleSize(ySize);
	 g->GetYaxis()->SetLabelSize(ySize);
	 g->GetYaxis()->SetTitleOffset(offset);
      }
      //______________________________________________________________________________
      void SetLabelSizes(TGraphErrors *g,double xSize,double ySize,double offset){
	 g->GetXaxis()->SetTitleSize(xSize);
	 g->GetXaxis()->SetLabelSize(xSize);
	 g->GetYaxis()->SetTitleSize(ySize);
	 g->GetYaxis()->SetLabelSize(ySize);
	 g->GetYaxis()->SetTitleOffset(offset);
      }
      //______________________________________________________________________________
      void SetLabelSizes(TGraphAsymmErrors *g,double xSize,double ySize,double offset){
	 g->GetXaxis()->SetTitleSize(xSize);
	 g->GetXaxis()->SetLabelSize(xSize);
	 g->GetYaxis()->SetTitleSize(ySize);
	 g->GetYaxis()->SetLabelSize(ySize);
	 g->GetYaxis()->SetTitleOffset(offset);
      }
      //______________________________________________________________________________
      void SetLabelSizes(TMultiGraph *g,double xSize,double ySize,double offset){
	 g->GetXaxis()->SetTitleSize(xSize);
	 g->GetXaxis()->SetLabelSize(xSize);
	 g->GetYaxis()->SetTitleSize(ySize);
	 g->GetYaxis()->SetLabelSize(ySize);
	 g->GetYaxis()->SetTitleOffset(offset);
      }
      //______________________________________________________________________________
      void UseTimeDisplay(TGraph *g){
	 g->GetXaxis()->SetTimeDisplay(1);
	 g->GetXaxis()->SetTimeFormat("#splitline{%m-%d-%y}{%H:%M:%S}");
	 g->GetXaxis()->SetLabelOffset(0.03);
	 g->GetXaxis()->SetTimeOffset(0);
      }
      //______________________________________________________________________________
      void UseTimeDisplay(TGraphErrors *g){
	 g->GetXaxis()->SetTimeDisplay(1);
	 g->GetXaxis()->SetTimeFormat("#splitline{%m-%d-%y}{%H:%M:%S}");
	 g->GetXaxis()->SetLabelOffset(0.03);
	 g->GetXaxis()->SetTimeOffset(0);
      }
      //______________________________________________________________________________
      void UseTimeDisplay(TGraphAsymmErrors *g){
	 g->GetXaxis()->SetTimeDisplay(1);
	 g->GetXaxis()->SetTimeFormat("#splitline{%m-%d-%y}{%H:%M:%S}");
	 g->GetXaxis()->SetLabelOffset(0.03);
	 g->GetXaxis()->SetTimeOffset(0);
      }
      //______________________________________________________________________________
      void UseTimeDisplay(TMultiGraph *g){
	 g->GetXaxis()->SetTimeDisplay(1);
	 g->GetXaxis()->SetTimeFormat("#splitline{%m-%d-%y}{%H:%M:%S}");
	 g->GetXaxis()->SetLabelOffset(0.03);
	 g->GetXaxis()->SetTimeOffset(0);
      }
   } // :: Graph 
} // :: util_df
