// automatically load things to ROOT here 
{ 
 TString libPATH   = Form("%s",std::getenv("GM2FIELDUTILHOME") );
 TString libNAME   = "libgm2fieldUtil.so";
 TString incl_cmd  = Form(".include %s/lib",libPATH.Data());
 TString incl_cmd2 = Form(".include %s/include",libPATH.Data());
 TString load_cmd  = Form(".L %s/lib/%s",libPATH.Data(),libNAME.Data());
 gROOT->ProcessLine(incl_cmd);
 gROOT->ProcessLine(incl_cmd2);
 gROOT->ProcessLine(load_cmd);
 //The following lines enables you to use the fieldsignal libarry. If you want to use it, uncomment the following line.
 /*
 TString incl_cmd3 = Form(".include %s/include",std::getenv("GM2FIELDSIGNALLIB"));
 TString load_cmd2  = Form(".L %s/lib/%s",std::getenv("GM2FIELDSIGNALLIB"),"libfid.so");
 gROOT->ProcessLine(incl_cmd3);
 gROOT->ProcessLine(load_cmd2);
 */
}
