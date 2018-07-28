// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TMVA Regression for Energy scale estimation
//
// To launch:  r00t TrainRegression_bdtg.cxx\(\"100\"\,\"0.1\"\,\"0.6\"\,\"3\"\,\"TMVAReg100.root\"\)
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

// Opt è l'indice intero che indica la variabile su cui fare la discrezione dei file
// Opt = 0

TString TrainRegression_bdtg( TString NTrees = "", TString Shrinkage = "0.1", TString Fraction = "0.6", TString MaxDepth = "3", int Opt = -1)
{
   TString SubName;
   TString dir;
   if(Opt < 0) {
      SubName = TString::Itoa(fabs(Opt), 10);
      dir = "Regression/";
   }   
   if(Opt == 0) {
      SubName = NTrees;
      dir = "NTrees/";
   }
   if (Opt == 1) {
      SubName = Shrinkage;
      SubName[1] = '_';
      dir = "Shrinkage/";
   }
   if (Opt == 2) {
      SubName = Fraction;
      SubName[1] = '_';
      dir = "Fraction/";
   }
   if (Opt == 3) {
      SubName = MaxDepth;
      dir = "MaxDepth/";
   }

   TMVA::Tools::Instance();
   
   std::cout << "\n==> Start TMVARegression" << std::endl;

   //TString outfileName = dir + "TMVAReg" + SubName + ".root";
   TString outfileName = "TMVAReg.root";
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   TMVA::Factory *factory = new TMVA::Factory( "TMVARegression", outputFile, 
                                               "!V:!Silent:Color:DrawProgressBar:AnalysisType=Regression" );

   //TMVA::DataLoader *dataloader=new TMVA::DataLoader(dir + "dataset_" + SubName);
   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");

	(TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   TMVA::Config::Instance();
   (TMVA::gConfig().GetIONames()).fWeightFileDir = "weightsMassVariable0Jet_";

   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   //dataloader->AddVariable("LHE_mlvlv", 'F');
   //dataloader->AddVariable( "LHE_mlvlv_t" , 'F');
   dataloader->AddVariable( "LHE_mllmet" , 'F');
   
   //dataloader->AddVariable( "2*LHE_mlvlv_t" , 'F');
   //dataloader->AddVariable( "1.817*LHE_mlvlv_t" , 'F');
   dataloader->AddVariable( "LHE_mll" , 'F');
   //dataloader->AddVariable( "LHE_theta*LHE_mll" , 'F');
   //dataloader->AddVariable( "LHE_dphill*LHE_mll" , 'F');

   //dataloader->AddVariable( "std_vector_LHElepton_pt[0]" , 'F');
   //dataloader->AddVariable( "std_vector_LHElepton_pt[1]" , 'F');


   //dataloader->AddVariable( "1.354*LHE_mllmet" , 'F');
   //dataloader->AddVariable( "2*LHE_mll" , 'F');
   //dataloader->AddVariable( "4*LHE_mll" , 'F');
   //dataloader->AddVariable( "2.558*LHE_mll" , 'F');
   //dataloader->AddVariable( "metLHEpt" , 'F');
   //dataloader->AddVariable( "LHE_dphilmet1*metLHEpt" , 'F');

   //dataloader->AddVariable( "2*metLHEpt" , 'F');
   //dataloader->AddVariable( "2*std_vector_LHElepton_pt[0]" , 'F');
   //dataloader->AddVariable( "4*std_vector_LHElepton_pt[1]" , 'F');
   //dataloader->AddVariable( "LHE_dphill" , 'F');
   //dataloader->AddVariable( "200*LHE_dphill" , 'F');
   //dataloader->AddVariable( "LHE_dphill*std_vector_LHElepton_pt[0]" , 'F');	
   //dataloader->AddVariable( "LHE_dphill*sqrt(std_vector_LHElepton_pt[0]*std_vector_LHElepton_pt[0] + std_vector_LHElepton_pt[1]*std_vector_LHElepton_pt[1])" , 'F');
   //dataloader->AddVariable( "dphillmet" , 'F');       //Variabile da salvare nel TTree latino_reduced
   //dataloader->AddVariable( "LHE_dphilmet1" , 'F');
   //dataloader->AddVariable( "LHE_dphilmet2" , 'F');
   //dataloader->AddVariable( "LHE_dphilmet2*metLHEpt" , 'F');
   //dataloader->AddVariable( "LHE_dphilmet1*LHE_mll" , 'F');
   //dataloader->AddVariable( "LHE_dphilmet2*LHE_mll" , 'F');
   //dataloader->AddVariable( "sqrt(std_vector_LHElepton_pt[0]*std_vector_LHElepton_pt[0] + std_vector_LHElepton_pt[1]*std_vector_LHElepton_pt[1])", 'F');
   //dataloader->AddVariable( "3*sqrt(std_vector_LHElepton_pt[0]*std_vector_LHElepton_pt[0] + std_vector_LHElepton_pt[1]*std_vector_LHElepton_pt[1])", 'F');
   //dataloader->AddVariable( "4*sqrt(std_vector_LHElepton_pt[0]*std_vector_LHElepton_pt[0] + std_vector_LHElepton_pt[1]*std_vector_LHElepton_pt[1])", 'F');
   //dataloader->AddVariable( "std_vector_LHEparton_pt[0]" , 'F');
   //dataloader->AddVariable( "std_vector_LHEparton_pt[1]" , 'F');
   //dataloader->AddVariable( "sqrt(std_vector_LHEparton_pt[0]*std_vector_LHEparton_pt[0] + std_vector_LHEparton_pt[1]*std_vector_LHEparton_pt[1])", 'F');
   //dataloader->AddVariable( "LHE_dphijj*LHE_mjj" , 'F');
   //dataloader->AddVariable( "LHE_dphijj*std_vector_LHEparton_pt[0]" , 'F');
   //dataloader->AddVariable( "LHE_dphijj*std_vector_LHEparton_pt[1]" , 'F');
   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   // Add the variable carrying the regression target
   dataloader->AddTarget( "LHE_mlvlv" ); 

  
   // Read training and test data (see TMVAClassification for reading ASCII files)
   // load the signal and background event samples from ROOT trees
   TFile *input(0);
   //TString fname = "./WpWmJJ/WpWmJJ_reduced.root";
   TString fname = "./WpWmJJ/WpWmJJ_reduced2.root";
   //TString fname = "./WpWpJJ/WpWpJJ_reduced.root";
   //TString fname = "./WpWpJJ/WpWpJJ_reduced2.root";
   
   if (!gSystem->AccessPathName( fname )) 
      input = TFile::Open( fname ); // check if file in local directory exists

   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVARegression           : Using input file: " << input->GetName() << std::endl;

   TTree *regTree = (TTree*)input->Get("latino_reduced");
   // global event weights per tree (see below for setting event-wise weights)
   Double_t regWeight  = 1.0;   

   // You can add an arbitrary number of regression trees
   dataloader->AddRegressionTree( regTree, regWeight );
   std::cout << "==> Aggiunto Tree alla regressione" << std::endl;
   // This would set individual event weights (the variables defined in the 
   // expression need to exist in the original TTree)
   //dataloader->SetWeightExpression( "LHE_mlvlv<1000.", "Regression" );      //non funziona

   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // Apply additional cuts on the signal and background samples (can be different)
   //TCut mycut = "LHE_mlvlv > 160. && LHE_mlvlv < 1000.";
   //TCut mycut = "LHE_mllmet < 200.";
   //TCut mycut = "";
   // If no numbers of events are given, half of the events in the tree are used 
   // for training, and the other half for testing:
   //ataloader->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   
   // Neural network (MLP)

//       factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=Norm:NeuronType=tanh:NCycles=20000:HiddenLayers=N+20:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15:!UseRegulator" );
//         factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=Norm:NeuronType=tanh:NCycles=200:HiddenLayers=N+20:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15:!UseRegulator" );
// 	factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=Norm:NeuronType=tanh:NCycles=400:HiddenLayers=N+10:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" );
// 	factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=N:NeuronType=tanh:NCycles=200:HiddenLayers=N+10:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" );
// 	factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=G,N:NeuronType=tanh:NCycles=200:HiddenLayers=N+5:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" );
// 	factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=G,N:NeuronType=tanh:NCycles=100:HiddenLayers=N+5:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" );
//      factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=G,N:NeuronType=tanh:NCycles=200:HiddenLayers=N+7:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" );
//      factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:NeuronType=tanh:NCycles=400:HiddenLayers=N+7:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" );
/*   factory->BookMethod
     (
       dataloader, 
       TMVA::Types::kMLP, 
       "MLP", 
       "!H:!V:NeuronType=tanh:NCycles=100:HiddenLayers=N+7:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" 
     );
*/

   // Boosted Decision Trees

   TString option = "!H:!V:NTrees=" + NTrees + "::BoostType=Grad:Shrinkage=" + Shrinkage + ":UseBaggedBoost:GradBaggingFraction=" + Fraction + ":MaxDepth=" + MaxDepth;

   factory->BookMethod
   (
      dataloader,
      TMVA::Types::kBDT,
      "BDTG",
      option
   );

   // Train MVAs using the set of training events
   factory->TrainAllMethods();
   std::cout << "TrainAllMethods eseguito." << std::endl;


   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();
   std::cout << "TestAllMethods eseguito." << std::endl;


   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();
   std::cout << "EvaluateAllMethods eseguito." << std::endl;


   // --------------------------------------------------------------
   
   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVARegression is done!" << std::endl;      

   delete factory;
   delete dataloader;

   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVARegGui( outfileName );

   return SubName;
}