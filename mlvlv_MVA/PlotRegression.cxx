// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TMVA Regression for Energy scale estimation
//
// To launch:  r00t PlotRegression.cxx\(\"BDT\"\,\"100\"\)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

#define ptbins 200
#define etabins 100
#define phibins 100
#define mbins 200
#define devbins 50
//#define A 1.35362    //WpWm normalization factor
#define A 1.32062    //WpWp normalization factor
   
void PlotRegression( TString TrainName = "", TString SubName = "" ) 
{
   std::cout << "==> Start TMVAPlotRegression" << std::endl;

   TString path, inputfile;
   if(TrainName == "")  path = "Regression/";
   if(TrainName == "BDT")  path = "Test_Methods/BDT_AdaBoost/";
   if(TrainName == "BDTG")  path = "Test_Methods/BDT_Grad/";
   if(TrainName == "BDTG2")  path = "Test_Methods/BDT_Grad_nocuts/";
   if(TrainName == "BDTG3")  path = "Test_Methods/BDT_Grad_MaxDepth10/";
   if(TrainName == "NT")   path = "NTrees/";
   if(TrainName == "SK")   path = "Shrinkage/";
   if(TrainName == "F")   path = "Fraction/";
   if(TrainName == "MD")   path = "MaxDepth/";

   //inputfile = path + "TMVARegApp" + SubName + ".root";
   inputfile = "TMVARegApp.root";

   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}"};                            // #1
   TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}"};              // #2
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}"};            // #3
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "2*M_{ll}", "p_{T, MET}"};          // #4
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "4*M_{ll}", "p_{T, MET}"};          // #5
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "2*p_{T, MET}"};          // #6
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}", "p_{T, lepton1}"};         // #7
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}", "2*p_{T, lepton1}"};       // #8
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}", "2*p_{T, lepton1}", "p_{T, lepton2}"};       // #9
   //TString variable_name[20] = {"2*M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}", "2*p_{T, lepton1}", "4*p_{T, lepton2}"};       // #10
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}", "2*p_{T, lepton1}", "4*p_{T, lepton2}"};       // #11
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "1.354*M_{ll, MET}", "M_{ll}", "p_{T, MET}", "2*p_{T, lepton1}", "4*p_{T, lepton2}"};       // #12
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#theta*M_{ll}", "p_{T, MET}", "2*p_{T, lepton1}", "4*p_{T, lepton2}"};      // #13
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#theta*M_{ll}", "p_{T, MET}"};      // #14
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#theta*M_{ll}"};      // #15
   //TString variable_name[20] = {"M_{ll, MET}", "2*p_{T, lepton1}", "4*p_{T, lepton2}"};      // #16
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "2*p_{T, lepton1}"};      // #17
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, MET}"};              // #18-19-20-21
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, lepton1}"};          // #22
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "p_{T, lepton1}", "p_{T, lepton2}", "p_{T, lepton12}"};          // #23
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "p_{T, lepton1}", "p_{T, lepton2}", "#Delta#phi*M_{ll}"};           // #24
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "p_{T, lepton1}", "p_{T, lepton2}", "#Delta#phi*_{ll}"};           // #25
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "p_{T, lepton1}", "p_{T, lepton2}", "200*#Delta#phi*_{ll}"};           // #26
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "p_{T, lepton12}"};           // #27
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "4*p_{T, lepton12}"};          // #28
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}"};          // #29
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "p_{T, lepton12}"};          // #30
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "3*p_{T, lepton12}"};          // #31
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#phi*M_{ll}"};           // #32
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#phi_{1}*M_{ll}", "#Delta#phi_{2}*M_{ll}"};            // #33
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#phi*p_{T, lepton1}"};            // #34
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "#Delta#phi*p_{T, lepton12}"};            // #35
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "#Delta#phi*p_{T, lepton12}"};          // #36
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}", "#Delta#phi_{1}*p_{T, MET}"};           // #37
   //TString variable_name[20] = {"M^{T}_{l#nul#nu, NORM}", "M_{ll, MET, NORM}", "M_{ll, NORM}", "#Delta#phi_{1}*p_{T, MET}"};           // #38
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll, NORM}", "#Delta#phi_{1}*p_{T, MET}"};           // #39
   //TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll, NORM}", "#Delta#phi_{1}*p_{T, MET}", "p_{T, lepton12}"};           // #40
   //TString variable_name[20] = {"p_{T, lepton1}", "p_{T, lepton2}", "p_{T, lepton12}"};            // #41
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

   TString target_name[3] = {"M_{l#nul#nu}","M_{l#nul#nu, true}","M_{l#nul#nu, regression}"};

   Int_t nvariables = 0;
   for(int i = 0; i < 20; i++) {
         if(variable_name[i] == "") {
            nvariables = i;
            break;
         }
         else
            std::cout << "variable_name[" << i << "] = " << variable_name[i] << std::endl;

   }

   TH2* plots[20];
   Int_t nplots = 0;

   //TH1F* h_target = new TH1F( target_name[1], target_name[1] + " | " + TrainName, mbins, 0., 1500.);
   TH1F* h_target = new TH1F( target_name[1], target_name[1], mbins, 0., 1500.);
   //TH1F* h_regression = new TH1F( target_name[2], target_name[2] + " | " + TrainName, mbins, 0., 1500.);
   TH1F* h_regression = new TH1F( target_name[2], target_name[2], mbins, 0., 1500.);
   //TH1F* h_dev = new TH1F( "(" + target_name[2] + "-" + target_name[1] + ") : " + target_name[1], "Deviation from target | " + TrainName, 2*devbins, -2., 2.);
   TH1F* h_dev = new TH1F( "Deviation", "Deviation from target | Shrinkage", devbins, -1., 1.);
   TH1F* h_resolution = new TH1F( "Resolution", target_name[2] + " : " + target_name[1], devbins, 0., 3.);
   TH1F* h_resolution_mllmet = new TH1F( "Visible resolution", "A*M_{ll, MET} : " + target_name[1], devbins, 0., 3.);
   TH1F* h_mlvlv_t = new TH1F ("M^{T}_{l#nul#nu}", "M^{T}_{l#nul#nu} : " + target_name[1], devbins, 0., 5.);
   TH1F* h_mll = new TH1F ("M_{ll}", "M_{ll} : " + target_name[1], devbins, 0., 5.);
   TProfile* h_profile = new TProfile("Dev profile", "Profile of " + target_name[2] + " deviation vs " + target_name[1], mbins, 0., 1500., -3., 3.);

   //Definisco due TH2F per ogni variabile:
   // - variabile vs target
   // - (variabile - target) : target vs target
   for(nplots = 0; nplots < nvariables; nplots++) {
      plots[nplots] = new TH2F("Corr " + variable_name[nplots] + " | " + TrainName,
                           variable_name[nplots] + " vs " + target_name[0],
                           mbins,
                           0.,
                           1500.,
                           ptbins,
                           0.,
                           1000.
                  );
         
      plots[nplots + nvariables] = new TH2F("Dev " + variable_name[nplots] + " | " + TrainName,
                           "(" + variable_name[nplots] + " - " + target_name[0] + ") : " + target_name[0] + " vs " + target_name[0],
                           mbins,
                           0.,
                           1500.,
                           devbins,
                           -3.,
                           3.
                  );
     }
     nplots *= 2;    //Ho 2 plot per ogni variabile, e dato che nplots era l'indice che scorreva sulle variabili lo moltiplico per 2

     plots[nplots] = new TH2F("Corr " + target_name[2] + " | " + TrainName,
                           target_name[2] + " vs " + target_name[1],
                           mbins,
                           0.,
                           1500.,
                           ptbins,
                           0.,
                           1000.
                  );

     plots[nplots+1] = new TH2F("Dev " + target_name[2] + " | " + TrainName,
                           "(" + target_name[2] + " - " + target_name[1] + ") : " + target_name[1] + " vs " + target_name[1],
                           mbins,
                           0.,
                           1500.,
                           devbins,
                           -3.,
                           3.
                  );

     nplots += 2;

   std::cout << "nvariables = " << nvariables << std::endl;
   std::cout << "nplots = " << nplots << std::endl;

   std::cout << "Opening " << inputfile << std::endl;
   TFile *input(0);
   if (!gSystem->AccessPathName( inputfile )) {
      input = TFile::Open( inputfile ); // check if file in local directory exists
   } 
   else { 
      if (!input) {
         std::cout << "ERROR: could not open data file" << std::endl;
         exit(1);
      }   
   }
      
   // --- Event loop

   TTree* theTree = (TTree*)input->Get("latino_reg");
   //input->Close();

   // Variables
   Float_t  metLHEpt, LHE_mlvlv_t, LHE_mllmet, LHE_mll, LHE_mjj,
            LHE_theta, LHE_dphill, LHE_dphilmet1, LHE_dphilmet2, LHE_dphillxLHE_mll, LHE_dphilmet1xLHE_mll, LHE_dphilmet2xLHE_mll, LHE_dphillxLHE_lepton_pt1,
            LHE_dphillxptl12, LHE_mlvlv_tx2, LHE_mllx2, LHE_mllx4, metLHEptx2;

   Float_t std_vector_LHElepton_pt1, std_vector_LHElepton_pt1x2;
   Float_t std_vector_LHElepton_pt2, std_vector_LHElepton_pt2x4;
   Float_t std_vector_LHEparton_pt1, std_vector_LHEparton_pt2;
   Float_t LHE_mllmet_norm, LHE_mlvlv_t_norm, LHE_mll_norm, LHE_thetaxLHE_mll;
   Float_t LHE_dphilmet1xmetLHEpt, LHE_dphijjxLHE_mjj, LHE_dphijj;
   Float_t ptl12, ptp12, LHE_dphijjxLHE_parton_pt1, LHE_dphijjxLHE_parton_pt2;
   vector<float> *std_vector_LHElepton_pt = new std::vector <float>;
   vector<float> *std_vector_LHEparton_pt = new std::vector <float>;

   // Target
   Float_t LHE_mlvlv;

   // Regression target
   Float_t REG_mlvlv;

   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   theTree->SetBranchAddress("LHE_mlvlv", &LHE_mlvlv);
   theTree->SetBranchAddress("LHE_mlvlv_t", &LHE_mlvlv_t);
   theTree->SetBranchAddress("LHE_mlvlv_tx2", &LHE_mlvlv_tx2);
   theTree->SetBranchAddress("LHE_mllmet", &LHE_mllmet);
   theTree->SetBranchAddress("LHE_mllmet_norm", &LHE_mllmet_norm);
   theTree->SetBranchAddress("LHE_mlvlv_t_norm", &LHE_mlvlv_t_norm);
   theTree->SetBranchAddress("LHE_mll_norm", &LHE_mll_norm);
   theTree->SetBranchAddress("LHE_mll", &LHE_mll);
   theTree->SetBranchAddress("LHE_mjj", &LHE_mjj);
   theTree->SetBranchAddress("LHE_mllx2", &LHE_mllx2);
   theTree->SetBranchAddress("LHE_mllx4", &LHE_mllx4);
   theTree->SetBranchAddress("metLHEpt", &metLHEpt);
   theTree->SetBranchAddress("metLHEptx2", &metLHEptx2);
   theTree->SetBranchAddress("std_vector_LHElepton_pt", &std_vector_LHElepton_pt);
   theTree->SetBranchAddress("std_vector_LHEparton_pt", &std_vector_LHEparton_pt);
   theTree->SetBranchAddress("std_vector_LHElepton_pt1x2", &std_vector_LHElepton_pt1x2);
   theTree->SetBranchAddress("std_vector_LHElepton_pt2x4", &std_vector_LHElepton_pt2x4);
   theTree->SetBranchAddress("LHE_thetaxLHE_mll", &LHE_thetaxLHE_mll);
   //theTree->SetBranchAddress("LHE_theta", &LHE_theta);
   theTree->SetBranchAddress("LHE_dphill", &LHE_dphill);
   theTree->SetBranchAddress("LHE_dphijj", &LHE_dphijj);
   theTree->SetBranchAddress("LHE_dphillxLHE_mll", &LHE_dphillxLHE_mll);
   theTree->SetBranchAddress("LHE_dphijjxLHE_mjj", &LHE_dphijjxLHE_mjj);
   theTree->SetBranchAddress("LHE_dphillxLHE_lepton_pt1" , &LHE_dphillxLHE_lepton_pt1);
   theTree->SetBranchAddress("LHE_dphijjxLHE_parton_pt1" , &LHE_dphijjxLHE_parton_pt1);
   theTree->SetBranchAddress("LHE_dphijjxLHE_parton_pt2" , &LHE_dphijjxLHE_parton_pt2);
   theTree->SetBranchAddress("LHE_dphillxptl12" , &LHE_dphillxptl12);
   theTree->SetBranchAddress("LHE_dphilmet1", &LHE_dphilmet1);
   theTree->SetBranchAddress("LHE_dphilmet2", &LHE_dphilmet2);
   theTree->SetBranchAddress("ptl12", &ptl12);
   theTree->SetBranchAddress("ptp12", &ptp12);
   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   theTree->SetBranchAddress("REG_mlvlv", &REG_mlvlv);

   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {
      if (ievt%1000 == 0) {
         std::cout << "--- ... Processing event: " << ievt << std::endl;
      }
      theTree->GetEntry(ievt);

      //1D histograms fill
      h_target->Fill(LHE_mlvlv);
      h_regression->Fill(REG_mlvlv);
      //if(LHE_mlvlv > 400.)
      h_resolution->Fill(REG_mlvlv/LHE_mlvlv);
      h_resolution_mllmet->Fill(A*LHE_mllmet/LHE_mlvlv);
      h_mlvlv_t->Fill(LHE_mlvlv_t/LHE_mlvlv);
      h_mll->Fill(LHE_mll/LHE_mlvlv);

   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll};                                     // #1
      Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, metLHEpt};                           // #2
      //Float_t y_plots[20] = {LHE_mlvlv_tx2, LHE_mllmet, LHE_mll, metLHEpt};                         // #3
      //Float_t y_plots[20] = {LHE_mlvlv_tx2, LHE_mllmet, LHE_mllx2, metLHEpt};                       // #4
      //Float_t y_plots[20] = {LHE_mlvlv_tx2, LHE_mllmet, LHE_mllx4, metLHEpt};                       // #5
      //Float_t y_plots[20] = {LHE_mlvlv_tx2, LHE_mllmet, LHE_mll, metLHEptx2};                       // #6
      //Float_t y_plots[20] = {LHE_mlvlv_tx2, LHE_mllmet, LHE_mll, metLHEpt, std_vector_LHElepton_pt->at(0)};        // #7
      //Float_t y_plots[20] = {LHE_mlvlv_tx2, LHE_mllmet, LHE_mll, metLHEpt, std_vector_LHElepton_pt1x2};        // #8
      //Float_t y_plots[20] = {LHE_mlvlv_tx2, LHE_mllmet, LHE_mll, metLHEpt, std_vector_LHElepton_pt1x2, std_vector_LHElepton_pt->at(1)};        // #9
      //Float_t y_plots[20] = {LHE_mlvlv_tx2, LHE_mllmet, LHE_mll, metLHEpt, std_vector_LHElepton_pt1x2, std_vector_LHElepton_pt2x4};        // #10
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, metLHEpt, std_vector_LHElepton_pt1x2, std_vector_LHElepton_pt2x4};        // #11
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet_norm, LHE_mll, metLHEpt, std_vector_LHElepton_pt1x2, std_vector_LHElepton_pt2x4};        // #12
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_thetaxLHE_mll, metLHEpt, std_vector_LHElepton_pt1x2, std_vector_LHElepton_pt2x4};        // #13
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_thetaxLHE_mll, metLHEpt};        // #14
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_thetaxLHE_mll};        // #15
      //Float_t y_plots[20] = {LHE_mllmet, std_vector_LHElepton_pt1x2, std_vector_LHElepton_pt2x4};        // #16
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, std_vector_LHElepton_pt1x2};        // #17
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, metLHEpt};                           // #18-19-20-21
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, std_vector_LHElepton_pt->at(0)};       // #22
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, std_vector_LHElepton_pt->at(0), std_vector_LHElepton_pt->at(1), ptl12};       // #23
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, std_vector_LHElepton_pt->at(0), std_vector_LHElepton_pt->at(1), LHE_dphillxLHE_mll};       // #24
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, std_vector_LHElepton_pt->at(0), std_vector_LHElepton_pt->at(1), LHE_dphill};       // #25
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, std_vector_LHElepton_pt->at(0), std_vector_LHElepton_pt->at(1), 200*LHE_dphill};       // #26
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, ptl12};       // #27
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, 4*ptl12};       // #28
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet};       // #29
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, ptl12};       // #30
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, 3*ptl12};       // #31
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_dphilmet1*LHE_mll};       // #32
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_dphilmet1*LHE_mll, LHE_dphilmet2*LHE_mll};       // #33
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_dphill*std_vector_LHElepton_pt->at(0)};       // #34
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_dphill*ptl12};       // #35
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, LHE_dphill*ptl12};       // #36
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, LHE_dphilmet1*metLHEpt};       // #37
      //Float_t y_plots[20] = {LHE_mlvlv_t_norm, LHE_mllmet_norm, LHE_mll_norm, LHE_dphilmet1*metLHEpt};       // #38
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll_norm, LHE_dphilmet1*metLHEpt};       // #39
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll_norm, LHE_dphilmet1*metLHEpt, ptl12};       // #40
      //Float_t y_plots[20] = {std_vector_LHElepton_pt->at(0), std_vector_LHElepton_pt->at(1), ptl12};       // #41
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, std_vector_LHEparton_pt->at(0)};              // #42
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, std_vector_LHEparton_pt->at(0), std_vector_LHEparton_pt->at(1)};              // #43
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, std_vector_LHEparton_pt->at(0), std_vector_LHEparton_pt->at(1), ptp12};              // #44
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, LHE_dphijjxLHE_mjj};              // #45
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, LHE_dphijjxLHE_parton_pt1};              // #46
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, LHE_dphilmet2*metLHEpt};       // #47
      /*Float_t y_plots[21] = {LHE_mlvlv_t, LHE_mllmet, LHE_mll, metLHEpt, std_vector_LHElepton_pt->at(0), std_vector_LHElepton_pt->at(1),
      						LHE_thetaxLHE_mll, LHE_dphillxLHE_mll, LHE_dphill*std_vector_LHElepton_pt->at(0), LHE_dphill*ptl12,
      						LHE_dphilmet1*metLHEpt, LHE_dphilmet2*metLHEpt, LHE_dphilmet1*LHE_mll, LHE_dphilmet2*LHE_mll,
      						ptl12, std_vector_LHEparton_pt->at(0), std_vector_LHEparton_pt->at(1), ptp12,
      						LHE_dphijjxLHE_mjj, LHE_dphijjxLHE_parton_pt1
      						};*/
      //Float_t y_plots[20] = {LHE_mlvlv_t, LHE_mll, std_vector_LHElepton_pt->at(0)}; //#98
      //Float_t y_plots[20] = {LHE_mllmet, LHE_mll, std_vector_LHElepton_pt->at(0)}; //#97


   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      for (Int_t ih=0; ih<nvariables; ih++) {
         //std::cout << "Sto per fare fill" << std::endl;
         plots[ih]->Fill(LHE_mlvlv, y_plots[ih]);
         //std::cout << "Fill 1 eseguito" << std::endl;
         plots[ih + nvariables]->Fill(LHE_mlvlv, (y_plots[ih] - LHE_mlvlv)/LHE_mlvlv);
         //std::cout << "Fill 2 eseguito" << std::endl;
      }

      Float_t dev_mlvlv = (REG_mlvlv - LHE_mlvlv)/LHE_mlvlv;
      plots[nplots-2]->Fill(LHE_mlvlv, REG_mlvlv);
      plots[nplots-1]->Fill(LHE_mlvlv, dev_mlvlv);
      h_profile->Fill(LHE_mlvlv, dev_mlvlv);
      h_dev->Fill(dev_mlvlv);

   }

   TCanvas* c[30];
   path = path + "dataset_" + SubName + "/plots/";     // Mi sposto nella cartella plots/ per salvare i plot
   gSystem->Exec("mkdir " + path);                     // Creo la cartella plots/
   std::cout << "Saving plots in " << path << std::endl;

   TCanvas* b = new TCanvas ("bb0", "bb0", 1196, 690);
   h_resolution->GetXaxis()->SetTitle(target_name[2] + ":" + target_name[1]);
   h_resolution->GetYaxis()->SetTitle("N");
   h_resolution->SetLineColor(kRed);
   h_resolution->SetLineWidth(4);
   h_resolution->Draw();
   b->Print(path + "resolution.png");

   TCanvas* k = new TCanvas ("k0", "k0", 1196, 690);
   h_resolution->SetTitle("Resolution");
   h_resolution->GetXaxis()->SetTitle(target_name[2] + ":" + target_name[1]);
   h_resolution->GetYaxis()->SetTitle("N");
   h_resolution->SetLineColor(kRed);
   h_resolution->Draw();
   h_resolution_mllmet->SetLineColor(kBlue);
   h_resolution_mllmet->SetLineWidth(4);
   h_resolution_mllmet->Draw("same");
   TLegend *legend3 = new TLegend(0.78, 0.60, 0.98, 0.75);
   legend3->AddEntry(h_resolution_mllmet, "Visible");
   legend3->AddEntry(h_resolution, "Regression");
   legend3->Draw();
   k->Print(path + "resolution_cmp.png");

   TCanvas* d = new TCanvas ("d0", "d0", 1196, 690);
   h_resolution_mllmet->GetXaxis()->SetTitle("A*M_{ll, MET} :" + target_name[1]);
   h_resolution_mllmet->GetYaxis()->SetTitle("N");
   h_resolution_mllmet->SetLineColor(kBlue);
   h_resolution_mllmet->Draw();
   TLegend *legend2 = new TLegend(0.78, 0.60, 0.98, 0.75);
   //legend2->AddEntry((TObject*)0, "A = 1.35362", "");     //WpWm normalization factor
   legend2->AddEntry((TObject*)0, "A = 1.32062", "");       //WpWp normalization factor
   legend2->Draw();
   d->Print(path + "resolution_visible.png");

   TCanvas* f = new TCanvas ("f0", "f0", 1196, 690);
   h_mlvlv_t->GetXaxis()->SetTitle("M^{T}_{l#nul#nu} : " + target_name[1]);
   h_mlvlv_t->GetYaxis()->SetTitle("N");
   h_mlvlv_t->SetLineColor(kBlue);
   h_mlvlv_t->Draw();
   f->Print(path + "resolution_mlvlv_t.png");

   TCanvas* g = new TCanvas ("g0", "g0", 1196, 690);
   h_mll->GetXaxis()->SetTitle("M_{ll} : " + target_name[1]);
   h_mll->GetYaxis()->SetTitle("N");
   h_mll->SetLineColor(kBlue);
   h_mll->Draw();
   g->Print(path + "resolution_mll.png");

   c[0] = new TCanvas ("c0", "c0", 1196, 690);
   h_regression->GetXaxis()->SetTitle(target_name[0] + " [GeV]");
   h_regression->GetYaxis()->SetTitle("N");
   h_regression->SetLineColor(kRed);
   h_regression->Draw();
   //c[1] = new TCanvas ("c1", "c1", 1196, 690);
   h_target->GetXaxis()->SetTitle(target_name[0] + " [GeV]");
   h_target->GetYaxis()->SetTitle("N");
   h_target->Draw("same");
   TLegend *legend = new TLegend(0.78, 0.60, 0.98, 0.75);
   legend->AddEntry(h_target, "Target", "l");
   legend->AddEntry(h_regression, "Regression", "l");
   legend->Draw();
   c[0]->Print(path + "target1d.png");


   c[1] = new TCanvas ("c1", "c1", 590, 690);
   //h_dev->GetXaxis()->SetTitle("Relative deviation");
   h_dev->GetXaxis()->SetTitle("Relative deviation");
   //h_dev->GetYaxis()->SetTitle("N");
   h_dev->SetLineWidth(4);
   h_dev->Draw();
   c[1]->Print(path + "dev1d.png");

   if(TrainName == "SK" || TrainName == "F") SubName[1] = '.';

   TString resolution_file = "resolution.txt";
   if(TrainName == "") {
      std::ofstream output (resolution_file.Data(), std::ios::app);
      output << SubName << "\t" << h_resolution->GetRMS() << "\t" << h_resolution_mllmet->GetRMS() << endl;
      output.close();
      if(h_resolution_mllmet->GetMean() < 0.9)        //Altrimenti significa che ho già implementato la correzione #HARDCODED
         std::cout << "Resolution conversion factor = " << 1./h_resolution_mllmet->GetMean() << std::endl;
   }

   TString results_file = "target_deviation.txt";
   std::ofstream output (results_file.Data(), std::ios::app);
   output << TrainName << "\t" << SubName << "\t" << h_dev->GetMean() << "\t" << h_dev->GetRMS() << endl;
   output.close();

   gStyle->SetOptStat(0);     //Elimino lo stat-box dai plot

   int i = 0;
   for(i = 0; i < (nplots-2); i++) {
      char name[3];
      name[0] = 'c';
      if(i + 2 < 10)
         name[1] = 48+(i+2);  // 0-9 numbers
      else
         name[1] = 55+(i+2);  // A-Z letters
      name[2] = '\0';
      c[i+2] = new TCanvas (name, name, 1196, 690);
      plots[i]->Draw("COLZ");
      plots[i]->GetXaxis()->SetTitle(target_name[1] + " [GeV]");

      if(i < nvariables) {
         plots[i]->GetYaxis()->SetTitle(variable_name[i] + " [GeV]");
         c[i+2]->Print(path + "var" + TString((char)(48+i)) + "_corr.png");
      }
      else {
         plots[i]->GetYaxis()->SetTitle("Deviation");
         c[i+2]->Print(path + "var" + TString((char)(48+i-nvariables)) + "_dev.png");
      }
   }

   for(i = nplots-2; i < nplots; i++) {
      char name[3];
      name[0] = 'c';
      if(i + 2 < 10)
         name[1] = 48+(i+2);
      else
         name[1] = 55+(i+2);
      name[2] = '\0';
      c[i+2] = new TCanvas (name, name, 1196, 690);
      plots[i]->Draw("COLZ");
      plots[i]->GetXaxis()->SetTitle(target_name[1] + " [GeV]");

      if(i < nplots-1) {
         plots[i]->GetYaxis()->SetTitle(target_name[2] + " [GeV]");
         c[i+2]->Print(path + "regression_corr.png");
      }
      else {
         plots[i]->GetYaxis()->SetTitle("Deviation");
         c[i+2]->Print(path + "regression_dev.png");
      }
   }

   char name[3];
   name[0] = 'c';
   if(i + 2 < 10)
      name[1] = 48+(i+2);
   else
      name[1] = 55+(i+2);

   c[i+2] = new TCanvas (name, name, 1196, 690);
   h_profile->Draw();
   h_profile->GetXaxis()->SetTitle(target_name[1] + " [GeV]");
   h_profile->GetYaxis()->SetTitle(target_name[2] + " mean deviation");
   c[i+2]->Print(path + "regression_profile.png");

}


