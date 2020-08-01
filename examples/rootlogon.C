{
 // UtilDF 
 TString utilPath = Form("/your/install/path");
 TString incl_cmd = Form(".include %s/include",utilPath.Data());
 TString load_cmd = Form(".L %s/lib/libutil_df.so",utilPath.Data());
 gROOT->ProcessLine(incl_cmd);
 gROOT->ProcessLine(load_cmd);
}
