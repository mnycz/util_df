#include "UtilDFHistogram.hh"
//______________________________________________________________________________
namespace util_df {
   namespace Histogram { 
      //______________________________________________________________________________
      double GetSum(TH1F *h,double min,double max){
	 // Compute sum of counts in a histogram between min and max
	 // first find bin numbers corresponding to our range 
	 int bmin = h->FindBin(min);
	 int bmax = h->FindBin(max);
	 // now accumulate counts for bins between min and max
	 double sum=0;
	 for(int i=bmin;i<=bmax;i++) sum += h->GetBinContent(i);
	 return sum;
      }
      //______________________________________________________________________________
      double GetIntegral(TH1F *h,double min,double max){
	 // Compute area under the curve of a histogram between min and max
	 // first find bin numbers corresponding to our range 
	 int bmin = h->FindBin(min);
	 int bmax = h->FindBin(max);
	 // now accumulate counts for bins between min and max
	 double cnt=0,bw=0,sum=0;
	 for(int i=bmin;i<=bmax;i++){
	    bw   = h->GetBinWidth(i);
	    cnt  = h->GetBinContent(i);
	    sum += bw*cnt;
	 }
	 return sum;
      }
      //______________________________________________________________________________
      double GetSum2D_rect(TH2F *h,double xmin,double xmax,double ymin,double ymax){
	 // Compute sum of counts in a rectangular region defined by 
	 // (xmin < x < xmax) and (ymin < y < ymax)   
	 // loop over all bins, check against cut  
	 int NX = h->GetNbinsX();
	 int NY = h->GetNbinsY();
	 double sum=0,bc=0;
	 double X=0,Y=0,R=0;
	 for(int i=0;i<NX;i++){
	    for(int j=0;j<NY;j++){
	       bc = h->GetBinContent(i,j);
	       X  = h->GetXaxis()->GetBinCenter(i);
	       Y  = h->GetYaxis()->GetBinCenter(j);
	       if( (X>xmin&&X<xmax) && (Y>ymin&&Y<ymax) ){
		  // std::cout << Form("x = %.3lf (bx = %03d), y = %.3lf (by = %03d), r = %.3lf, bc = %.3E",X,i,Y,j,R,bc) << std::endl;  
		  sum += bc;
	       }
	    }
	 }
	 return sum;
      }
      //______________________________________________________________________________
      double GetSum2D_circ(TH2F *h,double R,double XC,double YC){
	 // Compute sum of counts in a circle defined by radius R, center (XC,YC)  
	 // use a circular cut defined by these boundaries
	 // loop over all bins, check against cut  
	 int NX = h->GetNbinsX();
	 int NY = h->GetNbinsY();
	 double sum=0,bc=0;
	 double x=0,y=0,r=0;
	 for(int i=0;i<NX;i++){
	    for(int j=0;j<NY;j++){
	       bc = h->GetBinContent(i,j);
	       x  = h->GetXaxis()->GetBinCenter(i);
	       y  = h->GetYaxis()->GetBinCenter(j);
	       r  = TMath::Sqrt( (x-XC)*(x-XC) + (y-YC)*(y-YC) ); // account for the chosen center (xc,yc) 
	       if(r<R){
		  // std::cout << Form("X = %.3lf, Y = %.3lf, R = %.3lf, r = %.3lf, xc = %.3lf, yc = %.3lf, bc = %.3lf",
		  //                   X,Y,R,r,xc,yc,bc) << std::endl; 
		  sum += bc;
	       }
	    }
	 }
	 return sum;
      }
      //______________________________________________________________________________
      double GetIntegral2D(TH2F *h,double xmin,double xmax,double ymin,double ymax){
	 // Compute area under the curve of a histogram between min and max
	 // first find bin numbers corresponding to our range 
	 int bmin = h->FindBin(xmin,ymin);
	 int bmax = h->FindBin(xmax,ymax);
	 // now accumulate counts for bins between min and max
	 double cnt=0,bw=0,sum=0;
	 for(int i=bmin;i<=bmax;i++){
	    bw   = h->GetBinWidth(i);
	    cnt  = h->GetBinContent(i);
	    sum += bw*cnt;
	 }
	 return sum;
      }
      //______________________________________________________________________________
      void SetLabels(TH1F *h,TString Title,TString xAxisTitle,TString yAxisTitle){
	 h->SetTitle(Title); 
	 h->GetXaxis()->SetTitle(xAxisTitle); 
	 h->GetXaxis()->CenterTitle(); 
	 h->GetYaxis()->SetTitle(yAxisTitle); 
	 h->GetYaxis()->CenterTitle(); 
      }
      //______________________________________________________________________________
      void SetLabels(TH2F *h,TString Title,TString xAxisTitle,TString yAxisTitle){
	 h->SetTitle(Title); 
	 h->GetXaxis()->SetTitle(xAxisTitle); 
	 h->GetXaxis()->CenterTitle(); 
	 h->GetYaxis()->SetTitle(yAxisTitle); 
	 h->GetYaxis()->CenterTitle(); 
      }
      //______________________________________________________________________________
      void SetParameters(TH1F *h,int color,int mStyle,double mSize){
	 h->SetMarkerColor(color); 
	 h->SetLineColor(color);
         h->SetMarkerStyle(mStyle);  
         h->SetMarkerSize(mSize);  
      }
      //______________________________________________________________________________
      void SetParameters(TH2F *h,int color,int mStyle,double mSize){
	 h->SetMarkerColor(color); 
	 h->SetLineColor(color);
         h->SetMarkerStyle(mStyle);  
         h->SetMarkerSize(mSize);  
      }
   } // ::Histogram
} // ::util_df
