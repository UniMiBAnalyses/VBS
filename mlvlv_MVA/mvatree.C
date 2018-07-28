/*
Questa macro apre il file WpWmJJ/latino_WpWmJJ_EWK.root, salva il TTree "latino" contenuto nel file
e definisce le variabili associate ad ogni TBranch, che vengono attivate per essere salvate in un secondo TTree.
Il risultato è un nuovo file, "small.root", che contiene solamente il TTree "latinino" con le variabili necessarie all'MVA...
*/

void mvatree() {
   /*char **files;
   files[0] = "WpWmJJ/latino_WpWmJJ_EWK.root";
   files[1] = "WpWpJJ/latino_WpWpJJ_EWK.root";*/
   
   //Get old file, old tree and set top branch address
   TFile *oldfile = new TFile("WpWmJJ/latino_WpWmJJ_EWK.root");
   if(oldfile->IsOpen())	std::cout << "Apertura file riuscita." << std::endl;
   std::cout << "Lista dei contenuti del file WpWmJJ/latino_WpWmJJ_EWK.root:" << std::endl;
   oldfile->ls();		//List file contents
   TTree *oldtree = (TTree*)oldfile->Get("latino");			//"oldtree" sarà uguale al mio TTree "latino"
   std::cout << "Il numero di eventi è " << oldtree->GetEntries() << std::endl;

   //TObjArray *lista = oldtree->GetListOfBranches();		//Stampo la lista dei Branches
   //lista->Print();
   Float_t LHE_mlvlv;      //Definisco le nuove variabili
   Float_t LHE_mlvlv_t;
   Float_t LHE_mllmet;
   Float_t LHE_mll;
   Float_t LHE_theta;
   Float_t LHE_dphill;
   Float_t LHE_dphilmet1;
   Float_t LHE_dphilmet2;

   TBranch *b_LHE_mlvlv = oldtree->Branch("LHE_mlvlv", &LHE_mlvlv, "LHE_mlvlv/F");           //Definisco i nuovi Branches
   TBranch *b_LHE_mlvlv_t = oldtree->Branch("LHE_mlvlv_t", &LHE_mlvlv_t, "LHE_mlvlv_t/F");
   TBranch *b_LHE_mllmet = oldtree->Branch("LHE_mllmet", &LHE_mllmet, "LHE_mllmet/F");
   TBranch *b_LHE_mll = oldtree->Branch("LHE_mll", &LHE_mll, "LHE_mll/F");
   TBranch *b_LHE_theta = oldtree->Branch("LHE_theta", &LHE_theta, "LHE_theta/F");
   TBranch *b_LHE_dphill = oldtree->Branch("LHE_dphill", &LHE_dphill, "LHE_dphill/F");
   TBranch *b_LHE_dphilmet1 = oldtree->Branch("LHE_dphilmet1", &LHE_dphilmet1, "LHE_dphilmet1/F");
   TBranch *b_LHE_dphilmet2 = oldtree->Branch("LHE_dphilmet2", &LHE_dphilmet2, "LHE_dphilmet2/F");

   oldtree->SetBranchAddress("LHE_mlvlv", &LHE_mlvlv);            //Definisco indirizzo delle variabili dei nuovi Branches
   oldtree->SetBranchAddress("LHE_mlvlv_t", &LHE_mlvlv_t);
   oldtree->SetBranchAddress("LHE_mllmet", &LHE_mllmet);
   oldtree->SetBranchAddress("LHE_mll", &LHE_mll);
   oldtree->SetBranchAddress("LHE_theta", &LHE_theta);
   oldtree->SetBranchAddress("LHE_dphill", &LHE_dphill);
   oldtree->SetBranchAddress("LHE_dphilmet1", &LHE_dphilmet1);
   oldtree->SetBranchAddress("LHE_dphilmet2", &LHE_dphilmet2);
   
   oldtree->SetBranchStatus("*", 0);                              //Attivo solo i Branches che mi interessano
   oldtree->SetBranchStatus("std_vector_LHElepton_pt", 1);
   oldtree->SetBranchStatus("metLHEpt", 1);
   oldtree->SetBranchStatus("LHE_mlvlv", 1);
   oldtree->SetBranchStatus("LHE_mlvlv_t", 1);
   oldtree->SetBranchStatus("LHE_mllmet", 1);
   oldtree->SetBranchStatus("LHE_mll", 1);
   oldtree->SetBranchStatus("LHE_theta", 1);
   oldtree->SetBranchStatus("LHE_dphill", 1);
   oldtree->SetBranchStatus("LHE_dphilmet1", 1);
   oldtree->SetBranchStatus("LHE_dphilmet2", 1);

   ifstream infile("WpWmJJ/variables.dat", ios::in);              //Apro il file "variables.dat" che contiene le variabili interessanti stampate
                                                                  //separate da una tabulazione "\t"

   for(int i = 0; i < oldtree->GetEntries(); i++) {
      oldtree->GetEntry(i);
      infile >> LHE_mlvlv >> LHE_mlvlv_t >> LHE_mllmet >> LHE_mll >> LHE_theta >> LHE_dphill >> LHE_dphilmet1 >> LHE_dphilmet2;   
      b_LHE_mlvlv->Fill();                //Riempio i Branches con le variabili lette dal file
      b_LHE_mlvlv_t->Fill();
      b_LHE_mllmet->Fill();
      b_LHE_mll->Fill();
      b_LHE_theta->Fill();
      b_LHE_dphill->Fill();
      b_LHE_dphilmet1->Fill();
      b_LHE_dphilmet2->Fill();
   }

   infile.close();

   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile("small.root","recreate");
   TTree *newtree = oldtree->CloneTree();
   newtree->SetName("latino_reduced");

   std::cout << "Nuovo TTree salvato." << std::endl;
   newtree->Print();
   newfile->Write();
   std::cout << "Lista dei contenuti del file small.root:" << std::endl;
   newfile->ls();
   delete oldfile;
   delete newfile;

   TFile *_file0 = TFile::Open("small.root");
   new TBrowser();
}
