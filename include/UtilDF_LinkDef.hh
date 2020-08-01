#ifdef __CLING__

// general utility namespace 
#pragma link C++ namespace util_df+; 
// classes 
#pragma link C++ class TemperatureSensor+; 
#pragma link C++ class MovingAverage+; 
#pragma link C++ class Blinder+;
#pragma link C++ class CSVManager+;  
// sub-namespaces  
#pragma link C++ namespace util_df::Math+;
#pragma link C++ namespace util_df::Graph+;
#pragma link C++ namespace util_df::Import+; 
#pragma link C++ namespace util_df::Export+; 
#pragma link C++ namespace util_df::Algorithm+;

// we need to explicitly define which data types we want for the templated functions 
// binary read 
#pragma link C++ function util_df::Import::ImportData1_bin<int>+; 
#pragma link C++ function util_df::Import::ImportData1_bin<double>+; 
#pragma link C++ function util_df::Import::ImportData1_bin<unsigned int>+; 
#pragma link C++ function util_df::Import::ImportData1_bin<unsigned long>+; 
#pragma link C++ function util_df::Import::ImportData1_bin<unsigned long long>+; 
#pragma link C++ function util_df::Import::ImportData1_bin<signed int>+; 
#pragma link C++ function util_df::Import::ImportData1_bin<signed long>+; 
#pragma link C++ function util_df::Import::ImportData1_bin<signed long long>+; 
// binary write 
#pragma link C++ function util_df::Export::PrintData1_bin<int>+; 
#pragma link C++ function util_df::Export::PrintData1_bin<double>+; 
#pragma link C++ function util_df::Export::PrintData1_bin<unsigned int>+; 
#pragma link C++ function util_df::Export::PrintData1_bin<unsigned long>+; 
#pragma link C++ function util_df::Export::PrintData1_bin<unsigned long long>+; 
#pragma link C++ function util_df::Export::PrintData1_bin<signed int>+; 
#pragma link C++ function util_df::Export::PrintData1_bin<signed long>+; 
#pragma link C++ function util_df::Export::PrintData1_bin<signed long long>+; 
// reverse vectors 
#pragma link C++ function util_df::Algorithm::ReverseVector<int>+;
#pragma link C++ function util_df::Algorithm::ReverseVector<double>+;
#pragma link C++ function util_df::Algorithm::ReverseVector<unsigned int>+;
#pragma link C++ function util_df::Algorithm::ReverseVector<unsigned long>+;
#pragma link C++ function util_df::Algorithm::ReverseVector<unsigned long long>+;
#pragma link C++ function util_df::Algorithm::ReverseVector<signed int>+;
#pragma link C++ function util_df::Algorithm::ReverseVector<signed long>+;
#pragma link C++ function util_df::Algorithm::ReverseVector<signed long long>+;
// binary search 
#pragma link C++ function util_df::Algorithm::BinarySearch<int>+;
#pragma link C++ function util_df::Algorithm::BinarySearch<double>+;
#pragma link C++ function util_df::Algorithm::BinarySearch<unsigned int>+;
#pragma link C++ function util_df::Algorithm::BinarySearch<unsigned long>+;
#pragma link C++ function util_df::Algorithm::BinarySearch<unsigned long long>+;
#pragma link C++ function util_df::Algorithm::BinarySearch<signed int>+;
#pragma link C++ function util_df::Algorithm::BinarySearch<signed long>+;
#pragma link C++ function util_df::Algorithm::BinarySearch<signed long long>+;
// import funcs -- 1 column 
#pragma link C++ function util_df::Import::Import1<int>+;
#pragma link C++ function util_df::Import::Import1<double>+;
#pragma link C++ function util_df::Import::Import1<unsigned int>+;
#pragma link C++ function util_df::Import::Import1<unsigned long>+;
#pragma link C++ function util_df::Import::Import1<unsigned long long>+;
#pragma link C++ function util_df::Import::Import1<signed int>+;
#pragma link C++ function util_df::Import::Import1<signed long>+;
#pragma link C++ function util_df::Import::Import1<signed long long>+;
// 2 columns -- add what you need here...  
#pragma link C++ function util_df::Import::Import2<int,int>+;
#pragma link C++ function util_df::Import::Import2<int,double>+;
#pragma link C++ function util_df::Import::Import2<double,int>+;
#pragma link C++ function util_df::Import::Import2<double,double>+;
// mean
#pragma link C++ function util_df::Math::GetMean<int>+;  
#pragma link C++ function util_df::Math::GetMean<double>+;  
#pragma link C++ function util_df::Math::GetMean<unsigned int>+;  
#pragma link C++ function util_df::Math::GetMean<unsigned long>+;  
#pragma link C++ function util_df::Math::GetMean<unsigned long long>+;  
#pragma link C++ function util_df::Math::GetMean<unsigned long long>+; 
#pragma link C++ function util_df::Math::GetMean<signed int>+;  
#pragma link C++ function util_df::Math::GetMean<signed long>+;  
#pragma link C++ function util_df::Math::GetMean<signed long long>+;  
#pragma link C++ function util_df::Math::GetMean<signed long long>+; 
// weighted mean
#pragma link C++ function util_df::Math::GetWeightedMean<int>+;  
#pragma link C++ function util_df::Math::GetWeightedMean<double>+;  
#pragma link C++ function util_df::Math::GetWeightedMean<unsigned int>+;  
#pragma link C++ function util_df::Math::GetWeightedMean<unsigned long>+;  
#pragma link C++ function util_df::Math::GetWeightedMean<unsigned long long>+;  
#pragma link C++ function util_df::Math::GetWeightedMean<unsigned long long>+; 
#pragma link C++ function util_df::Math::GetWeightedMean<signed int>+;  
#pragma link C++ function util_df::Math::GetWeightedMean<signed long>+;  
#pragma link C++ function util_df::Math::GetWeightedMean<signed long long>+;  
#pragma link C++ function util_df::Math::GetWeightedMean<signed long long>+; 
// stdev  
#pragma link C++ function util_df::Math::GetStandardDeviation<int>+;  
#pragma link C++ function util_df::Math::GetStandardDeviation<double>+;  
#pragma link C++ function util_df::Math::GetStandardDeviation<unsigned int>+;  
#pragma link C++ function util_df::Math::GetStandardDeviation<unsigned long>+;  
#pragma link C++ function util_df::Math::GetStandardDeviation<unsigned long long>+;  
#pragma link C++ function util_df::Math::GetStandardDeviation<signed int>+;  
#pragma link C++ function util_df::Math::GetStandardDeviation<signed long>+;  
#pragma link C++ function util_df::Math::GetStandardDeviation<signed long long>+; 
// std err of the mean    
#pragma link C++ function util_df::Math::GetStandardErrorOfTheMean<int>+;  
#pragma link C++ function util_df::Math::GetStandardErrorOfTheMean<double>+;  
#pragma link C++ function util_df::Math::GetStandardErrorOfTheMean<unsigned int>+;  
#pragma link C++ function util_df::Math::GetStandardErrorOfTheMean<unsigned long>+;  
#pragma link C++ function util_df::Math::GetStandardErrorOfTheMean<unsigned long long>+;  
#pragma link C++ function util_df::Math::GetStandardErrorOfTheMean<signed int>+;  
#pragma link C++ function util_df::Math::GetStandardErrorOfTheMean<signed long>+;  
#pragma link C++ function util_df::Math::GetStandardErrorOfTheMean<signed long long>+; 
// variance 
#pragma link C++ function util_df::Math::GetVariance<int>+;  
#pragma link C++ function util_df::Math::GetVariance<double>+;  
#pragma link C++ function util_df::Math::GetVariance<unsigned int>+;  
#pragma link C++ function util_df::Math::GetVariance<unsigned long>+;  
#pragma link C++ function util_df::Math::GetVariance<unsigned long long>+;  
#pragma link C++ function util_df::Math::GetVariance<signed int>+;  
#pragma link C++ function util_df::Math::GetVariance<signed long>+;  
#pragma link C++ function util_df::Math::GetVariance<signed long long>+; 
// covariance 
#pragma link C++ function util_df::Math::GetCovariance<int>+;  
#pragma link C++ function util_df::Math::GetCovariance<double>+;  
#pragma link C++ function util_df::Math::GetCovariance<unsigned int>+;  
#pragma link C++ function util_df::Math::GetCovariance<unsigned long>+;  
#pragma link C++ function util_df::Math::GetCovariance<unsigned long long>+;  
#pragma link C++ function util_df::Math::GetCovariance<signed int>+;  
#pragma link C++ function util_df::Math::GetCovariance<signed long>+;  
#pragma link C++ function util_df::Math::GetCovariance<signed long long>+; 
// RMS  
#pragma link C++ function util_df::Math::GetRMS<int>+;  
#pragma link C++ function util_df::Math::GetRMS<double>+;  
#pragma link C++ function util_df::Math::GetRMS<unsigned int>+;  
#pragma link C++ function util_df::Math::GetRMS<unsigned long>+;  
#pragma link C++ function util_df::Math::GetRMS<unsigned long long>+;  
#pragma link C++ function util_df::Math::GetRMS<signed int>+;  
#pragma link C++ function util_df::Math::GetRMS<signed long>+;  
#pragma link C++ function util_df::Math::GetRMS<signed long long>+; 

#endif 
