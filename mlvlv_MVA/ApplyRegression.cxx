// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TMVA Regression for Energy scale estimation
//
// To launch:  r00t ApplyRegression.cxx\(\"BDT\"\,\"100\"\)
// To launch:  r00t ApplyRegression.cxx\(\"BDT,MLP\"\)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "substr.C"
using namespace TMVA;

#define ptbins 200
#define etabins 100
#define phibins 100
#define mbins 200
#define devbins 50

void ApplyRegression( TString myMethodList = "BDT", TString SubName = "", int Opt = -1) 
{
   // This loads the library
   TMVA::Tools::Instance();
   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;
   // --- Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 0;
   Use["PDEFoam"]         = 1; 
   Use["KNN"]             = 1;
   // 
   // --- Linear Discriminant Analysis
   Use["LD"]              = 1;
   // 
   // --- Function Discriminant analysis
   Use["FDA_GA"]          = 1;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   // 
   // --- Neural Network
   Use["MLP"]             = 1; 
   // 
   // --- Support Vector Machine 
   Use["SVM"]             = 0;
   // 
   // --- Boosted Decision Trees
   Use["BDT"]             = 0;
   Use["BDTG"]            = 1;
   //
   // --- Configuration of parameters

   // ---------------------------------------------------------------
   std::cout << std::endl;
   std::cout << "==> Start TMVARegressionApplication" << std::endl;
   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);
         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --- Create the Reader object
   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
   Float_t 	metLHEpt, LHE_mlvlv_t, LHE_mllmet, LHE_mll, LHE_mjj,
   			LHE_theta, LHE_dphill, LHE_dphilmet1, LHE_dphilmet2, LHE_dphillxLHE_mll, LHE_dphilmet1xLHE_mll, LHE_dphilmet2xLHE_mll, LHE_dphillxLHE_lepton_pt1,
   			LHE_dphillxptl12, LHE_mlvlv_tx2, LHE_mllx2, LHE_mllx4, metLHEptx2;

   Float_t std_vector_LHElepton_pt1, std_vector_LHElepton_pt1x2;
   Float_t std_vector_LHElepton_pt2, std_vector_LHElepton_pt2x4;
   Float_t std_vector_LHEparton_pt1, std_vector_LHEparton_pt2;
   Float_t LHE_mllmet_norm, LHE_mlvlv_t_norm, LHE_mll_norm, LHE_thetaxLHE_mll;
   Float_t LHE_dphilmet1xmetLHEpt, LHE_dphilmet2xmetLHEpt, LHE_dphijjxLHE_mjj, LHE_dphijj;
   Float_t ptl12, ptp12, LHE_dphijjxLHE_parton_pt1, LHE_dphijjxLHE_parton_pt2;
   vector<float> *std_vector_LHElepton_pt = new std::vector <float>;
   vector<float> *std_vector_LHEparton_pt = new std::vector <float>;

   // Target
   Float_t LHE_mlvlv;

   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
   reader->AddVariable( "LHE_mlvlv_t" , &LHE_mlvlv_t);
   reader->AddVariable( "LHE_mllmet" , &LHE_mllmet);
   //reader->AddVariable( "1.817*LHE_mlvlv_t" , &LHE_mlvlv_t_norm);
   //reader->AddVariable( "2*LHE_mlvlv_t" , &LHE_mlvlv_tx2);
   reader->AddVariable( "LHE_mll" , &LHE_mll);
   //reader->AddVariable( "1.354*LHE_mllmet" , &LHE_mllmet_norm);
   //reader->AddVariable( "2*LHE_mll" , &LHE_mllx2);
   //reader->AddVariable( "4*LHE_mll" , &LHE_mllx4);
   //reader->AddVariable( "2.558*LHE_mll" , &LHE_mll_norm);
   reader->AddVariable( "metLHEpt" , &metLHEpt);
   //reader->AddVariable( "2*metLHEpt" , &metLHEptx2);
   //reader->AddVariable( "std_vector_LHElepton_pt[0]" , &std_vector_LHElepton_pt1);
   //reader->AddVariable( "2*std_vector_LHElepton_pt[0]" , &std_vector_LHElepton_pt1x2);
   //reader->AddVariable( "std_vector_LHElepton_pt[1]" , &std_vector_LHElepton_pt2);
   //reader->AddVariable( "4*std_vector_LHElepton_pt[1]" , &std_vector_LHElepton_pt2x4);
   //reader->AddVariable( "LHE_theta*LHE_mll" , &LHE_thetaxLHE_mll);
   //reader->AddVariable( "LHE_dphill" , &LHE_dphill);
   //reader->AddVariable( "200*LHE_dphill" , &LHE_dphill);
   //reader->AddVariable( "LHE_dphill*LHE_mll" , &LHE_dphillxLHE_mll);
   //reader->AddVariable( "LHE_dphill*std_vector_LHElepton_pt[0]" , &LHE_dphillxLHE_lepton_pt1);
   //reader->AddVariable( "LHE_dphill*sqrt(std_vector_LHElepton_pt[0]*std_vector_LHElepton_pt[0] + std_vector_LHElepton_pt[1]*std_vector_LHElepton_pt[1])" , &LHE_dphillxLHE_lepton_pt1);
   //reader->AddVariable( "dphillmet" , 'F'); 
   //reader->AddVariable( "LHE_dphilmet1" , &LHE_dphilmet1);
   //reader->AddVariable( "LHE_dphilmet1*metLHEpt" , &LHE_dphilmet1xmetLHEpt);
   //reader->AddVariable( "LHE_dphilmet2" , &LHE_dphilmet2);
   //reader->AddVariable( "LHE_dphilmet2*metLHEpt" , &LHE_dphilmet2xmetLHEpt);
   //reader->AddVariable( "LHE_dphilmet1*LHE_mll" , &LHE_dphilmet1xLHE_mll);
   //reader->AddVariable( "LHE_dphilmet2*LHE_mll" , &LHE_dphilmet2xLHE_mll);
   //reader->AddVariable( "sqrt(std_vector_LHElepton_pt[0]*std_vector_LHElepton_pt[0] + std_vector_LHElepton_pt[1]*std_vector_LHElepton_pt[1])", &ptl12);
   //reader->AddVariable( "3*sqrt(std_vector_LHElepton_pt[0]*std_vector_LHElepton_pt[0] + std_vector_LHElepton_pt[1]*std_vector_LHElepton_pt[1])", &ptl12);
   //reader->AddVariable( "4*sqrt(std_vector_LHElepton_pt[0]*std_vector_LHElepton_pt[0] + std_vector_LHElepton_pt[1]*std_vector_LHElepton_pt[1])", &ptl12);
   //reader->AddVariable( "std_vector_LHEparton_pt[0]" , &std_vector_LHEparton_pt1);
   //reader->AddVariable( "std_vector_LHEparton_pt[1]" , &std_vector_LHEparton_pt2);
   //reader->AddVariable( "sqrt(std_vector_LHEparton_pt[0]*std_vector_LHEparton_pt[0] + std_vector_LHEparton_pt[1]*std_vector_LHEparton_pt[1])", &ptp12);
   //reader->AddVariable( "LHE_dphijj*LHE_mjj", &LHE_dphijjxLHE_mjj);
   //reader->AddVariable( "LHE_dphijj*std_vector_LHEparton_pt[0]", &LHE_dphijjxLHE_parton_pt1);
   //reader->AddVariable( "LHE_dphijj*std_vector_LHEparton_pt[1]", &LHE_dphijjxLHE_parton_pt2);
   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   // Dichiaro i nomi delle variabili così come verranno passati nei plot
   // La seguente riga è HARDCODED!

   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}"};								// #1
   TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}"};				// #2
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}"};				// #3
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "2*M_{ll}", "p_{T, MET}"};			// #4
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "4*M_{ll}", "p_{T, MET}"};			// #5
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "2*p_{T, MET}"};			// #6
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}", "p_{T, lepton1}"};			// #7
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}", "2*p_{T, lepton1}"};			// #8
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}", "2*p_{T, lepton1}", "p_{T, lepton2}"};		// #9
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}", "2*p_{T, lepton1}", "4*p_{T, lepton2}"};		// #10
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}", "2*p_{T, lepton1}", "4*p_{T, lepton2}"};		// #11
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "1.354*M_{ll, MET}", "M_{ll}", "p_{T, MET}", "2*p_{T, lepton1}", "4*p_{T, lepton2}"};		// #12
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#theta*M_{ll}", "p_{T, MET}", "2*p_{T, lepton1}", "4*p_{T, lepton2}"};		// #13
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#theta*M_{ll}", "p_{T, MET}"};		// #14
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#theta*M_{ll}"};		// #15
   //TString variable_name[20] = {"M_{ll, MET}", "2*p_{T, lepton1}", "4*p_{T, lepton2}"};		// #16
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "2*p_{T, lepton1}"};		// #17
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}"};				// #18-19-20-21
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, lepton1}"};          // #22
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "p_{T, lepton1}", "p_{T, lepton2}", "p_{T, lepton12}"};          // #23
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "p_{T, lepton1}", "p_{T, lepton2}", "#Delta#phi*M_{ll}"};           // #24
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "p_{T, lepton1}", "p_{T, lepton2}", "#Delta#phi_{ll}"};          // #25
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "p_{T, lepton1}", "p_{T, lepton2}", "200*#Delta#phi_{ll}"};            // #26
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, lepton12}"};            // #27
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "4*p_{T, lepton12}"};          // #28
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}"};           // #29
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "p_{T, lepton12}"};          // #30
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "3*p_{T, lepton12}"};           // #31
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#phi*M_{ll}"};           // #32
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#phi_{1}*M_{ll}", "#Delta#phi_{2}*M_{ll}"};            // #33
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#phi*p_{T, lepton1}"};            // #34
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#phi*p_{T, lepton12}"};           // #35
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "#Delta#phi*p_{T, lepton12}"};          // #36
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "#Delta#phi_{1}*p_{T, MET}"};           // #37
   //TString variable_name[20] = {"M^{T}_{l#nul#nu, NORM}", "M_{ll, MET, NORM}", "M_{ll, NORM}", "#Delta#phi_{1}*p_{T, MET}"};           // #38
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll, NORM}", "#Delta#phi_{1}*p_{T, MET}"};           // #39
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll, NORM}", "#Delta#phi_{1}*p_{T, MET}", "p_{T, lepton12}"};          // #40
   //TString variable_name[20] = {"p_{T, lepton1}", "p_{T, lepton2}", "p_{T, lepton12}"};				// #41
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, parton1}"};                       // #42
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, parton1}", "p_{T, parton2}"};                       // #43
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, parton1}", "p_{T, parton2}", "p_{T, parton12}"};                       // #44
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "#Delta#phi_{jj}*M_{jj}"};                       // #45
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "#Delta#phi_{jj}*p_{T, parton1}"};                       // #46
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "#Delta#phi_{2}*p_{T, MET}"};           // #47
   //TString variable_name[21] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v"}; //#99
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll}", "p_{T, lepton1}"};           // #98
   //TString variable_name[20] = {"M^{T}_{ll, MET}", "M_{ll}", "p_{T, lepton1}"};           // #97


   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   TString target_name = "M_{l#nul#nu}";
   Int_t nvariables = 0;
   for(int i = 0; i < 14; i++) {
   		if(variable_name[i] == "") {
   			nvariables = i;
   			break;
   		}
   		else
   			std::cout << "variable_name[" << i << "] = " << variable_name[i] << std::endl;

   }

   // --- Book the MVA methods
   TString path, dir;
   //if(Use["BDT"] && Opt == -1)	path = "Test_Methods/BDT_AdaBoost/";
   //if(Use["BDTG"] && Opt == -1)	path = "Test_Methods/BDT_Grad/";
   if(Use["BDTG"] && Opt < 0)	path = "Regression/";
   if(Use["BDTG"] && Opt == 0)	path = "NTrees/";
   if(Use["BDTG"] && Opt == 1)	path = "Shrinkage/";
   if(Use["BDTG"] && Opt == 2)	path = "Fraction/";
   if(Use["BDTG"] && Opt == 3)	path = "MaxDepth/";
   dir = path + "dataset_" + SubName + "/weightsMassVariable0Jet_" + SubName + "/";
   TString prefix = "TMVARegression";
   // Book method(s)
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = it->first + " method";
         //TString weightfile = dir + prefix + "_" + TString(it->first) + ".weights.xml";
         TString weightfile = "dataset/weightsMassVariable0Jet_/" + prefix + "_" + TString(it->first) + ".weights.xml";
         reader->BookMVA( methodName, weightfile ); 
      }
   }
   
   // Book output histograms
   TH1* hists[10];
   TH2* plots[20];
   Int_t nhists = -1;
   Int_t nplots = 0;
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      TH1* h = new TH1F( it->first.c_str(), TString(it->first) + " method", 200, 0., 1000.);
      if (it->second) hists[++nhists] = h;

      
   }
   nhists++;

   std::cout << "nvariables = " << nvariables << std::endl;
   std::cout << "nhists = " << nhists << std::endl;
   std::cout << "nplots = " << nplots << std::endl;
   
   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //   
   TFile *input(0);
   //TString fname = "./WpWmJJ/WpWmJJ_reduced.root";
   TString fname = "./WpWmJJ/WpWmJJ_reduced2.root";
   //TString fname = "./WpWpJJ/WpWpJJ_reduced.root";
   //TString fname = "./WpWpJJ/WpWpJJ_reduced2.root";

   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   } 
   else { 
      input = TFile::Open( "http://root.cern.ch/files/tmva_reg_example.root" ); // if not: download from ROOT server
   }
   
   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVARegressionApp        : Using input file: " << input->GetName() << std::endl;
   // --- Event loop
   // Prepare the tree
   // - here the variable names have to corresponds to your tree
   // - you can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
   TTree* theTree = (TTree*)input->Get("latino_reduced");
   //input->Close();
   //TFile *target  = new TFile( path + "TMVARegApp" + SubName + ".root","RECREATE" );
   TFile *target  = new TFile( "TMVARegApp.root","RECREATE" );
   TTree *newtree = theTree->CloneTree();
   newtree->SetName("latino_reg");
   std::cout << "--- Select signal sample" << std::endl;

   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   newtree->SetBranchAddress("LHE_mlvlv", &LHE_mlvlv);
   newtree->SetBranchAddress("LHE_mlvlv_t", &LHE_mlvlv_t);
   newtree->SetBranchAddress("LHE_mllmet", &LHE_mllmet);
   newtree->SetBranchAddress("LHE_mll", &LHE_mll);
   newtree->SetBranchAddress("LHE_mjj", &LHE_mjj);
   newtree->SetBranchAddress("metLHEpt", &metLHEpt);
   newtree->SetBranchAddress("std_vector_LHElepton_pt", &std_vector_LHElepton_pt);
   newtree->SetBranchAddress("std_vector_LHEparton_pt", &std_vector_LHEparton_pt);
   newtree->SetBranchAddress("LHE_theta", &LHE_theta);
   newtree->SetBranchAddress("LHE_dphill", &LHE_dphill);
   newtree->SetBranchAddress("LHE_dphijj", &LHE_dphijj);
   newtree->SetBranchAddress("LHE_dphilmet1", &LHE_dphilmet1);
   newtree->SetBranchAddress("LHE_dphilmet2", &LHE_dphilmet2);
   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   Float_t REG_mlvlv;
   TBranch *b_REG_mlvlv = newtree->Branch("REG_mlvlv", &REG_mlvlv, "REG_mlvlv/F");
   newtree->SetBranchAddress("REG_mlvlv", &REG_mlvlv);

   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   TBranch *b_LHE_mlvlv_tx2 = newtree->Branch("LHE_mlvlv_tx2", &LHE_mlvlv_tx2, "LHE_mlvlv_tx2/F");
   newtree->SetBranchAddress("LHE_mlvlv_tx2", &LHE_mlvlv_tx2);

   TBranch *b_LHE_mllx2 = newtree->Branch("LHE_mllx2", &LHE_mllx2, "LHE_mllx2/F");
   newtree->SetBranchAddress("LHE_mllx2", &LHE_mllx2);

   TBranch *b_LHE_mllx4 = newtree->Branch("LHE_mllx4", &LHE_mllx4, "LHE_mllx4/F");
   newtree->SetBranchAddress("LHE_mllx4", &LHE_mllx4);

   TBranch *b_metLHEptx2 = newtree->Branch("metLHEptx2", &metLHEptx2, "metLHEptx2/F");
   newtree->SetBranchAddress("metLHEptx2", &metLHEptx2);

   TBranch *b_std_vector_LHElepton_pt1x2 = newtree->Branch("std_vector_LHElepton_pt1x2", &std_vector_LHElepton_pt1x2, "std_vector_LHElepton_pt1x2/F");
   newtree->SetBranchAddress("std_vector_LHElepton_pt1x2", &std_vector_LHElepton_pt1x2);

   TBranch *b_std_vector_LHElepton_pt2x4 = newtree->Branch("std_vector_LHElepton_pt2x4", &std_vector_LHElepton_pt2x4, "std_vector_LHElepton_pt2x4/F");
   newtree->SetBranchAddress("std_vector_LHElepton_pt2x4", &std_vector_LHElepton_pt2x4);

   TBranch *b_LHE_mllmet_norm = newtree->Branch("LHE_mllmet_norm", &LHE_mllmet_norm, "LHE_mllmet_norm/F");
   newtree->SetBranchAddress("LHE_mllmet_norm", &LHE_mllmet_norm);

   TBranch *b_LHE_mlvlv_t_norm = newtree->Branch("LHE_mlvlv_t_norm", &LHE_mlvlv_t_norm, "LHE_mlvlv_t_norm/F");
   newtree->SetBranchAddress("LHE_mlvlv_t_norm", &LHE_mlvlv_t_norm);

   TBranch *b_LHE_mll_norm = newtree->Branch("LHE_mll_norm", &LHE_mll_norm, "LHE_mll_norm/F");
   newtree->SetBranchAddress("LHE_mll_norm", &LHE_mll_norm);

   TBranch *b_LHE_thetaxLHE_mll = newtree->Branch("LHE_thetaxLHE_mll", &LHE_thetaxLHE_mll, "LHE_thetaxLHE_mll/F");
   newtree->SetBranchAddress("LHE_thetaxLHE_mll", &LHE_thetaxLHE_mll);

   TBranch *b_ptl12 = newtree->Branch("ptl12", &ptl12, "ptl12/F");
   newtree->SetBranchAddress("ptl12", &ptl12);

   TBranch *b_ptp12 = newtree->Branch("ptp12", &ptp12, "ptp12/F");
   newtree->SetBranchAddress("ptp12", &ptp12);

   TBranch *b_LHE_dphillxLHE_mll = newtree->Branch("LHE_dphillxLHE_mll", &LHE_dphillxLHE_mll, "LHE_dphillxLHE_mll/F");
   newtree->SetBranchAddress("LHE_dphillxLHE_mll", &LHE_dphillxLHE_mll);

   TBranch *b_LHE_dphijjxLHE_mjj = newtree->Branch("LHE_dphijjxLHE_mjj", &LHE_dphijjxLHE_mjj, "LHE_dphijjxLHE_mjj/F");
   newtree->SetBranchAddress("LHE_dphijjxLHE_mjj", &LHE_dphijjxLHE_mjj);

   TBranch *b_LHE_dphillxLHE_lepton_pt1 = newtree->Branch("LHE_dphillxLHE_lepton_pt1", &LHE_dphillxLHE_lepton_pt1, "LHE_dphillxLHE_lepton_pt1/F");
   newtree->SetBranchAddress("LHE_dphillxLHE_lepton_pt1", &LHE_dphillxLHE_lepton_pt1);

   TBranch *b_LHE_dphillxLHE_dphillxptl12 = newtree->Branch("LHE_dphillxptl12", &LHE_dphillxptl12, "LHE_dphillxptl12/F");
   newtree->SetBranchAddress("LHE_dphillxptl12", &LHE_dphillxptl12);

   TBranch *b_LHE_dphijjxLHE_parton_pt1 = newtree->Branch("LHE_dphijjxLHE_parton_pt1", &LHE_dphijjxLHE_parton_pt1, "LHE_dphijjxLHE_parton_pt1/F");
   newtree->SetBranchAddress("LHE_dphijjxLHE_parton_pt1", &LHE_dphijjxLHE_parton_pt1);
   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   std::cout << "--- Processing: " << newtree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<newtree->GetEntries();ievt++) {
      if (ievt%1000 == 0) {
         std::cout << "--- ... Processing event: " << ievt << std::endl;
      }
      newtree->GetEntry(ievt);
      // Retrieve the MVA target values (regression outputs) and fill into histograms
      // NOTE: EvaluateRegression(..) returns a vector for multi-target regression
      for (Int_t ih=0; ih<nhists; ih++) {
         TString title = hists[ih]->GetTitle();
         Float_t val = (reader->EvaluateRegression( title ))[0];
         REG_mlvlv = val;
         b_REG_mlvlv->Fill(); 
         hists[ih]->Fill( val );
   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         LHE_mlvlv_tx2 = 2*LHE_mlvlv_t;
         b_LHE_mlvlv_tx2->Fill();

         LHE_mllx2 = 2*LHE_mll;
         b_LHE_mllx2->Fill();

         LHE_mllx4 = 4*LHE_mll;
         b_LHE_mllx4->Fill();

         metLHEptx2 = 2*metLHEpt;
         b_metLHEptx2->Fill();

         std_vector_LHElepton_pt1x2 = 2*std_vector_LHElepton_pt->at(0);
         b_std_vector_LHElepton_pt1x2->Fill();

         std_vector_LHElepton_pt2x4 = 4*std_vector_LHElepton_pt->at(1);
         b_std_vector_LHElepton_pt2x4->Fill();

         LHE_mllmet_norm = 1.354*LHE_mllmet;
         b_LHE_mllmet_norm->Fill();

         LHE_mlvlv_t_norm = 1.817*LHE_mlvlv_t;
         b_LHE_mlvlv_t_norm->Fill();

         LHE_mll_norm = 2.558*LHE_mll;
         b_LHE_mll_norm->Fill();

         LHE_thetaxLHE_mll = LHE_theta*LHE_mll;
         b_LHE_thetaxLHE_mll->Fill();

         ptl12 = sqrt( pow(std_vector_LHElepton_pt->at(0), 2) + pow(std_vector_LHElepton_pt->at(1), 2) );
         b_ptl12->Fill();

         ptp12 = sqrt( pow(std_vector_LHEparton_pt->at(0), 2) + pow(std_vector_LHEparton_pt->at(1), 2) );
         b_ptp12->Fill();

         LHE_dphillxLHE_mll = LHE_dphill*LHE_mll;
         b_LHE_dphillxLHE_mll->Fill();

         LHE_dphijjxLHE_mjj = LHE_dphijj*LHE_mjj;
         b_LHE_dphijjxLHE_mjj->Fill();

         LHE_dphillxLHE_lepton_pt1 = LHE_dphill*std_vector_LHElepton_pt->at(0);
         b_LHE_dphillxLHE_lepton_pt1->Fill();

         LHE_dphijjxLHE_parton_pt1 = LHE_dphijj*std_vector_LHEparton_pt->at(0);
         b_LHE_dphijjxLHE_parton_pt1->Fill();

         LHE_dphillxptl12 = LHE_dphill*ptl12;
         b_LHE_dphillxLHE_dphillxptl12->Fill();
   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      }
      //std::cout << "fill istogrammi 1D eseguito" << std::endl;
   }
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();
   // --- Write histograms
   //TFile *target  = new TFile( "TMVARegApp" + SubName + ".root","RECREATE" );
   for (Int_t ih=0; ih<nhists; ih++) hists[ih]->Write();
   for (Int_t ih=0; ih<nplots; ih++) plots[ih]->Write();
   
   std::cout << "Nuovo TTree salvato." << std::endl;
   newtree->Print();
   target->Write();
   //newtree->Delete("latino;1");
   std::cout << "Lista dei contenuti del file " << target->GetName() << ":" << std::endl;
   target->ls();

   target->Close();
   std::cout << "--- Created root file: \"" << target->GetName() 
             << "\" containing the MVA output histograms" << std::endl;
  
   delete reader;
    
   std::cout << "==> TMVARegressionApplication is done!" << std::endl << std::endl;
}
int main( int argc, char** argv )
{
   // Select methods (don't look at this code - not of interest)
   TString methodList; 
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(","); 
      methodList += regMethod;
   }
   ApplyRegression(methodList);
   return 0;
}