// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TMVA Regression for Energy scale estimation
//
// To launch:  r00t Overtrain.cxx\(\"SK\"\,\"0_1\"\)
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
   
void Overtrain( TString TrainName = "", TString SubName = "" ) 
{
   std::cout << "==> Start TMVAOvertrain" << std::endl;

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

   inputfile = path + "TMVAReg" + SubName + ".root";

   TString target_name[3] = {"M_{l#nul#nu}","M_{l#nul#nu, true}","M_{l#nul#nu, regression}"};

   TH2* plots[4];
   Int_t nplots = 4;

   TH1F* train_dev = new TH1F( target_name[2] + " dev Train", "Training/test sample deviation", 2*devbins, -2., 2.);
   TH1F* test_dev = new TH1F( target_name[2] + " dev Test", "Training/test sample deviation", 2*devbins, -2., 2.);
   TProfile* train_profile = new TProfile("Train profile", "Training/test sample profile of deviation", mbins, 0., 1500., -3., 3.);
   TProfile* test_profile = new TProfile("Test profile", "Training/test sample profile of deviation", mbins, 0., 1500., -3., 3.);
   

   plots[0] = new TH2F("Dev " + target_name[2] + " | Training sample",
                           "(" + target_name[2] + " - " + target_name[1] + ") : " + target_name[1] + " vs " + target_name[1] + " | Training sample",
                           mbins,
                           0.,
                           1500.,
                           devbins,
                           -3.,
                           3.
                  );

   plots[1] = new TH2F("Dev " + target_name[2] + " | Test sample",
                           "(" + target_name[2] + " - " + target_name[1] + ") : " + target_name[1] + " vs " + target_name[1] + " | Test sample",
                           mbins,
                           0.,
                           1500.,
                           devbins,
                           -3.,
                           3.
                  );

   plots[2] = new TH2F("Corr " + target_name[2] + " | Training sample",
                           target_name[2] + " vs " + target_name[1] + " | Training sample",
                           mbins,
                           0.,
                           1500.,
                           ptbins,
                           0.,
                           1000.
                  );

   plots[3] = new TH2F("Corr " + target_name[2] + " | Test sample",
                           target_name[2] + " vs " + target_name[1] + " | Test sample",
                           mbins,
                           0.,
                           1500.,
                           ptbins,
                           0.,
                           1000.
                  );


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

   path = path + "dataset_" + SubName + "/";
   std::cout << path << std::endl;

   // --- Event loop

   TTree* trainTree = (TTree*)input->Get(path + "TrainTree");
   TTree* testTree = (TTree*)input->Get(path + "TestTree");
   //input->Close();

   // Target
   Float_t LHE_mlvlv;

   // Regression target
   Float_t REG_mlvlv;

   trainTree->SetBranchAddress("LHE_mlvlv", &LHE_mlvlv);
   trainTree->SetBranchAddress("BDTG", &REG_mlvlv);

   std::cout << "--- Processing: " << trainTree->GetEntries() << " events" << std::endl;
   for (Long64_t ievt=0; ievt<trainTree->GetEntries();ievt++) {
      if (ievt%1000 == 0) {
         std::cout << "--- ... Processing event: " << ievt << std::endl;
      }
      trainTree->GetEntry(ievt);

      Float_t dev_mlvlv = (REG_mlvlv - LHE_mlvlv)/LHE_mlvlv;
      plots[0]->Fill(LHE_mlvlv, dev_mlvlv);
      plots[2]->Fill(LHE_mlvlv, REG_mlvlv);
      train_profile->Fill(LHE_mlvlv, dev_mlvlv);
      train_dev->Fill(dev_mlvlv);
   }

   testTree->SetBranchAddress("LHE_mlvlv", &LHE_mlvlv);
   testTree->SetBranchAddress("BDTG", &REG_mlvlv);

   std::cout << "--- Processing: " << testTree->GetEntries() << " events" << std::endl;
   for (Long64_t ievt=0; ievt<testTree->GetEntries();ievt++) {
      if (ievt%1000 == 0) {
         std::cout << "--- ... Processing event: " << ievt << std::endl;
      }
      testTree->GetEntry(ievt);

      Float_t dev_mlvlv = (REG_mlvlv - LHE_mlvlv)/LHE_mlvlv;
      plots[1]->Fill(LHE_mlvlv, dev_mlvlv);
      plots[3]->Fill(LHE_mlvlv, REG_mlvlv);
      test_profile->Fill(LHE_mlvlv, dev_mlvlv);
      test_dev->Fill(dev_mlvlv);
   }

   TCanvas* c[6];
   path = path + "plots/";            // Mi sposto nella cartella plots/ per salvare i plot
   gSystem->Exec("mkdir " + path);     // Creo la cartella plots/
   std::cout << "Saving plots in " << path << std::endl;

   c[0] = new TCanvas ("b0", "b0", 1196, 690);
   train_dev->GetXaxis()->SetTitle("Deviation");
   train_dev->GetYaxis()->SetTitle("N");
   train_dev->SetLineColor(kRed);
   train_dev->Draw();
   test_dev->GetXaxis()->SetTitle("Deviation");
   test_dev->GetYaxis()->SetTitle("N");
   test_dev->Draw("same");

   TLegend *legend = new TLegend(0.78, 0.60, 0.98, 0.75);
   legend->AddEntry(train_dev, "Training", "l");
   legend->AddEntry(test_dev, "Test", "l");
   legend->Draw();
   c[0]->Print(path + "overtrain1d.png");

   gStyle->SetOptStat(0);     //Elimino lo stat-box dai plot

   c[1] = new TCanvas ("b1", "b1", 1196, 690);
   train_profile->GetXaxis()->SetTitle(target_name[1] + " [GeV]");
   train_profile->GetYaxis()->SetTitle(target_name[2] + " mean deviation");
   train_profile->SetLineColor(kRed);
   train_profile->Draw();
   test_profile->GetXaxis()->SetTitle(target_name[1] + " [GeV]");
   test_profile->GetYaxis()->SetTitle(target_name[2] + " mean deviation");
   test_profile->Draw("same");

   TLegend *legend2 = new TLegend(0.78, 0.60, 0.98, 0.75);
   legend2->AddEntry(train_profile, "Training", "lp");
   legend2->AddEntry(test_profile, "Test", "lp");
   legend2->Draw();
   c[1]->Print(path + "overtrain_profile.png");

   if(TrainName == "SK" || TrainName == "F") SubName[1] = '.';

   TString results_file = "overtrain_deviation.txt";
   std::ofstream output (results_file.Data(), std::ios::app);
   output << TrainName << "\t" << SubName << "\t" <<
             train_dev->GetMean() << "\t" << train_dev->GetRMS() << "\t" <<
             test_dev->GetMean() << "\t" << test_dev->GetRMS() << endl;
   output.close();

   for(int i = 0; i < 4; i++) {
      char name[3];
      name[0] = 'b';
      if(i + 2 < 10)
         name[1] = 48+(i+2);
      else
         name[1] = 55+(i+2);
      name[2] = '\0';
      c[i+2] = new TCanvas (name, name, 1196, 690);
      plots[i]->Draw("COLZ");
      plots[i]->GetXaxis()->SetTitle(target_name[1] + " [GeV]");

      TString sample;
      if(i % 2 == 0)
         sample = "train";
      else
         sample = "test";

      if(i < 2) {
         plots[i]->GetYaxis()->SetTitle("Deviation");         
         c[i+2]->Print(path + "overtrain_" + sample + "_dev.png");
      }
      else {
         plots[i]->GetYaxis()->SetTitle(target_name[2] + " [GeV]");
         c[i+2]->Print(path + "overtrain_" + sample + "_corr.png");
      }
   }

}


