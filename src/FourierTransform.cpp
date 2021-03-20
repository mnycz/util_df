#include "FourierTransform.hh"
namespace util_df {
   //______________________________________________________________________________
   FourierTransform::FourierTransform(double sampleFreq,double padTime,int verbosity){
      fSampleFreq      = sampleFreq; 
      fZeroPaddingTime = padTime; 
      fVerbosity       = verbosity; 
      const int N      = util_df::Constants::FTSIZE; 
      fComplex         = new double[N];
      ClearArray();  
   }
   //______________________________________________________________________________
   FourierTransform::~FourierTransform(){
      delete[] fComplex; 
   }
   //______________________________________________________________________________
   void FourierTransform::ClearArray(){
      const int N = util_df::Constants::FTSIZE; 
      for(int i=0;i<N;i++) fComplex[i] = 0;
   }
   //______________________________________________________________________________
   int FourierTransform::GetNFFT(int N){
      int NZP  = (int)( fSampleFreq*fZeroPaddingTime );  // number of points for zero-padding
      int NPTS = N + NZP;
      int NFFT = GetNextPowerOfTwo(NPTS);                // closest power of 2 for optimization  
      return NFFT;
   }
   //______________________________________________________________________________
   int FourierTransform::GetNextPowerOfTwo(int N){
      double arg1 = log( (double)N )/log(2.);
      double arg2 = ceil(arg1);
      double NFT  = pow(2.,arg2);
      int NFFT    = (int)NFT;
      return NFFT;
   }
   //______________________________________________________________________________
   int FourierTransform::Transform(int N,double *f,double *F){

      // N = number of input data points
      // f = input data  [f(t)] 
      // F = output data [F(w)]
      // returns the number of FFT data points, NFFT 

      int NFFT = GetNFFT(N);    // number of FFT data points 

      const int NN = util_df::Constants::FTSIZE;

      if(fVerbosity>0){
	 std::cout << "[FourierTransform]: N = " << N << ", NFFT = " << NFFT << std::endl;
      } 

      if(NN<NFFT){
	 std::cout << "[FourierTransform]: ERROR! "   << std::endl;
	 std::cout << "                    NFFT   = " << NFFT << std::endl;
	 std::cout << "                    FTSIZE = " << NN   << std::endl;
	 return -1;
      }

      // fill complex array
      for(int i=0;i<N;i++){
	 fComplex[2*i+1] = f[i];  // real part
	 fComplex[2*i+2] = 0;     // imaginary part 
      }
      // zero-padding: fill with zeroes after that 
      for(int i=N;i<NFFT;i++){
	 fComplex[2*i+1] = 0;      // real part
	 fComplex[2*i+2] = 0;      // imaginary part 
      }

      if(fVerbosity>0) std::cout << "[FourierTransform]: Computing FFT..." << std::endl;
      for(int i=0;i<NFFT;i++){
	 F[2*i+1] = fComplex[2*i+1];
	 F[2*i+2] = fComplex[2*i+2];
      }
      four1(1,NFFT,F);
      // normalization (converts to voltage) 
      // for this, we need:
      // F(w) = F( f(t) )*dt; dt = time step size 
      // F(w) *= 1/(dt*NFFT) = F( f(t) )/NFFT 
      double sf = 1./( (double)NFFT );   
      for(int i=0;i<NFFT;i++){
	 F[2*i+1] *= sf;
	 F[2*i+2] *= sf;
      }

      // // check Parseval's theorem 
      // double sum1=0,sum2=0;
      // for(int i=0;i<NFFT;i++) sum1 += pow(fComplex[2*i+1],2) + pow(fComplex[2*i+2],2); 
      // for(int i=0;i<NFFT;i++) sum2 += pow(F[2*i+1],2) + pow(F[2*i+2],2);              

      // double pct = 100.*fabs(sum1-sum2)/(sum1+sum2);

      // if(pct>1){
      //    printf("[FourierTransform]: ERROR! Parseval's Theorem not satisfied!" << std::endl;
      //    printf("                       time domain sum: %.7lf \t freq. domain sum: %.7lf \n",sum1,sum2);
      // }

      if(fVerbosity>0) std::cout << "[FourierTransform]: Done." << std::endl;

      return NFFT; 

   }
   //______________________________________________________________________________
   void FourierTransform::InverseTransform(int N,double *F,double *f){

      // N = number of points in f 
      // F = input data  [F(w)] 
      // f = output data [f(t)]

      int NFFT = GetNFFT(N);    // number of FFT data points 

      ClearArray(); 

      // fill complex array
      std::cout << "[FourierTransform]: Computing inverse FFT..." << std::endl;
      for(int i=0;i<NFFT;i++){
	 fComplex[2*i+1] = F[2*i+1];
	 fComplex[2*i+2] = F[2*i+2];
      }
      four1(-1,NFFT,fComplex);
      // fill output array f with the real part of fComplex  
      for(int i=0;i<N;i++){
	 f[i] = fComplex[2*i+1];  
      }
      std::cout << "[FourierTransform]: Done." << std::endl;

   }
   // //______________________________________________________________________________
   // TH1F FourierTransform::*GetHistogram(const char *hName,const char *title,int NFFT,double F[]){
   //    int Bin    = NFFT;
   //    double Min = 0;
   //    double Max = fSampleFreq;
   //    TH1F *h = new TH1F(hName,title,Bin,Min,Max);
   //    double sf = 1.;
   //    double re=0,im=0,mag=0;
   //    for(int i=1;i<=NFFT;i++){
   //       re   = F[2*i+1];
   //       im   = F[2*i+2];
   //       mag  = sf*sqrt(re*re + im*im);
   //       h->SetBinContent(i+1,mag);
   //    }
   //    return h;
   // }
   //______________________________________________________________________________
   void FourierTransform::four1(int isign,int nn,double data[]){

      double PI    = acos(-1);
      double TWOPI = 2.*PI;

      int n, mmax, m, j, istep, i;
      double wtemp, wr, wpr, wpi, wi, theta;
      double tempr, tempi;

      n = nn << 1;

      j = 1;

      for(int i=1;i<n;i+=2){
	 if (j > i){
	    tempr = data[j];   data[j]   = data[i];   data[i]   = tempr;
	    tempr = data[j+1]; data[j+1] = data[i+1]; data[i+1] = tempr;
	 }
	 m = n >> 1;
	 while (m >= 2 && j > m) {
	    j -= m;
	    m >>= 1;
	 }
	 j += m;
      }

      mmax = 2;

      while (n > mmax){
	 istep = 2*mmax;
	 theta = TWOPI/(isign*mmax);
	 wtemp = sin(0.5*theta);
	 wpr   = -2.0*wtemp*wtemp;
	 wpi   = sin(theta);
	 wr    = 1.0;
	 wi    = 0.0;
	 for(m=1;m<mmax;m+=2) {
	    for(i = m;i<=n;i+=istep) {
	       j          = i + mmax;
	       tempr      = wr*data[j]   - wi*data[j+1];
	       tempi      = wr*data[j+1] + wi*data[j];
	       data[j]    = data[i]   - tempr;
	       data[j+1]  = data[i+1] - tempi;
	       data[i]   += tempr;
	       data[i+1] += tempi;
	    }
	    wr = (wtemp = wr)*wpr - wi*wpi + wr;
	    wi = wi*wpr + wtemp*wpi + wi;
	 }
	 mmax = istep;
      }

   }
}
