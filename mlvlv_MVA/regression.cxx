#include "TrainRegression_bdtg.cxx"
#include "ApplyRegression.cxx"
#include "PlotRegression.cxx"
#include "Overtrain.cxx"
//#include "substr.C"

#include <cstdlib>
#include <iostream> 
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

//#include "TMVARegGui.C"

#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Config.h"
#include "TMVA/TMVAGui.h"

using namespace TMVA;

#include <vector>
#include "TStopwatch.h"
#include "TMVA/Reader.h"

#define ptbins 200
#define etabins 100
#define phibins 100
#define mbins 200
#define devbins 50

// NTrees = 800
// Shrinkage = 0.13
// Fraction = 0.85
// MaxDepth = 3

void regression(int Opt) {
	//TString subname = TrainRegression_bdtg("800", "0.13", "0.85", "3", Opt);
	TString subname = "89";
	ApplyRegression("BDTG", subname, Opt);
	PlotRegression("", subname);
	Overtrain("", subname);
}

/*
void regression(TString NTrees) {
	TString subname;
	subname = TrainRegression_bdtg(NTrees, "0.13", "0.85", "3", 0);
	ApplyRegression("BDTG", subname, 0);
	PlotRegression("NT", subname);
}
*/

/*
void regression(TString Shrinkage) {
	TString subname;
	subname = TrainRegression_bdtg("800", Shrinkage, "0.6", "3", 1);
	ApplyRegression("BDTG", subname, 1);
	PlotRegression("SK", subname);
}
*/

/*
void regression(TString Fraction) {
	TString subname;
	subname = TrainRegression_bdtg("800", "0.13", Fraction, "3", 2);
	ApplyRegression("BDTG", subname, 2);
	PlotRegression("F", subname);
}
*/

/*
void regression(TString MaxDepth) {
	TString subname;
	subname = TrainRegression_bdtg("1700", "0.13", "0.85", MaxDepth, 3);
	ApplyRegression("BDTG", subname, 3);
	PlotRegression("MD", subname);
}
*/
