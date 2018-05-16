#define myselector_cxx
// The class definition in myselector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("myselector.C")
// Root > T->Process("myselector.C","some options")
// Root > T->Process("myselector.C+")
//

#include "myselector.h"
#include <TH2.h>
#include <TStyle.h>

#define ptbins 200
#define etabins 100
#define phibins 100
#define mbins 200
TString opzioni[3], dir;
unsigned int entries = 0;
ofstream firstfile("variables.dat", ios::trunc);
firstfile.close();
//ofstream outfile("variables.dat", ios::app);

void myselector::Begin(TTree * tree)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   //_histo_LHElepton_pt = new TH1F ("p_{T,lepton}","p_{T,lepton}",ptbins,0,2000.);
   _histo_LHElepton_pt = new TH1F ("p_{T,lepton}","p_{T,lepton}",ptbins,0,1000.);
   _histo_LHElepton_eta = new TH1F ("#eta_{lepton}","#eta_{lepton}",etabins,-5,5);
   _histo_LHElepton_phi = new TH1F ("#phi_{lepton}","#phi_{lepton}",phibins,-3.5,3.5);
   _histo_LHElepton_id = new TH1F ("ID_{lepton}","Particle ID",36,18,18);
   //_histo_LHEparton_pt = new TH1F ("p_{T,parton}","p_{T,parton}",ptbins,0,2000.);
   _histo_LHEparton_pt = new TH1F ("p_{T,parton}","p_{T,parton}",ptbins,0,200.);
   _histo_LHEparton_eta = new TH1F ("#eta_{parton}","#eta_{parton}",etabins,-8,8);
   _histo_LHEparton_phi = new TH1F ("#phi_{parton}","#phi_{parton}",phibins,-3.5,3.5);
   _histo_LHEparton_id = new TH1F ("ID_{parton}","Particle ID",36,-18,18);
   //_histo_metLHE_pt = new TH1F ("p_{T,MET}","p_{T,MET}",ptbins,0,2200.);
   _histo_metLHE_pt = new TH1F ("p_{T,MET}","p_{T,MET}",ptbins,0,1000.);
   _histo_metLHE_eta = new TH1F ("#eta_{MET}","#eta_{MET}",etabins,-5,5);
   _histo_metLHE_phi = new TH1F ("#phi_{MET}","#phi_{MET}",phibins,-3.5,3.5);
   _histo_jj_deltaeta = new TH1F ("#Delta#eta", "#Delta#eta_{jet-jet}", etabins, 0, +10);
   _histo_jj_m = new TH1F ("M_{jet-jet}", "M_{jet-jet}", mbins, 0, +3500);
   _histo_LHEmlvlv = new TH1F ("M_{l#nul#nu}", "M_{l#nul#nu}", mbins, 0, +1500);
   _histo2_lepton1_pt_mlvlv = new TH2F ("p_{T, lepton1} vs M_{l#nul#nu}", "p_{T, lepton1} vs M_{l#nul#nu}", mbins, 0., 1500., ptbins, 0., 800.);
   _histo2_lepton2_pt_mlvlv = new TH2F ("p_{T, lepton2} vs M_{l#nul#nu}", "p_{T, lepton2} vs M_{l#nul#nu}", mbins, 0., 1500., ptbins, 0., 800.);
   _histo2_met_pt_mlvlv = new TH2F ("p_{T, MET} vs M_{l#nul#nu}", "p_{T, MET} vs M_{l#nul#nu}", mbins, 0., 1500., ptbins, 0., 800.);
   _histo2_mlvlv_t_mlvlv = new TH2F ("M^{T}_{l#nul#nu} vs M_{l#nul#nu}", "M^{T}_{l#nul#nu} vs M_{l#nul#nu}", mbins, 0., 1500., ptbins, 0., 1000.);
   _histo2_mllmet_mlvlv = new TH2F ("M_{ll, MET} vs M_{l#nul#nu}", "M_{ll, MET} vs M_{l#nul#nu}", mbins, 0., 1500., ptbins, 0., 1000.);
   _histo2_mll_mlvlv = new TH2F ("M_{ll} vs M_{l#nul#nu}", "M_{ll} vs M_{l#nul#nu}", mbins, 0., 1500., ptbins, 0., 1000.);
   _histo2_theta_mlvlv = new TH2F ("#theta_{12} vs M_{l#nul#nu}", "#theta_{12} vs M_{l#nul#nu}", mbins, 0., 1500., phibins, 0., 3.15);
   _histo2_dphill_mlvlv = new TH2F ("#Delta#phi_{ll} vs M_{l#nul#nu}", "#Delta#phi_{ll} vs M_{l#nul#nu}", mbins, 0., 1500., phibins, 0., 3.15);
   _histo2_dphilmet1_mlvlv = new TH2F ("#Delta#phi_{l1,MET} vs M_{l#nul#nu}", "#Delta#phi_{l1,MET} vs M_{l#nul#nu}", mbins, 0., 1500., phibins, 0., 3.15);
   _histo2_dphilmet2_mlvlv = new TH2F ("#Delta#phi_{l2,MET} vs M_{l#nul#nu}", "#Delta#phi_{l2,MET} vs M_{l#nul#nu}", mbins, 0., 1500., phibins, 0., 3.15);
   _histo2_dphillxmll_mlvlv = new TH2F ("#Delta#phi_{ll} M_{ll} vs M_{l#nul#nu}", "#Delta#phi_{ll} M_{ll} vs M_{l#nul#nu}", mbins, 0., 1500., ptbins, 0., 2000.);

   TBranch *b_LHE_mlvlv = fChain->Branch("LHE_mlvlv", &LHE_mlvlv, "LHE_mlvlv/F");           //Definisco i nuovi Branches
   TBranch *b_LHE_mlvlv_t = fChain->Branch("LHE_mlvlv_t", &LHE_mlvlv_t, "LHE_mlvlv_t/F");
   TBranch *b_LHE_mllmet = fChain->Branch("LHE_mllmet", &LHE_mllmet, "LHE_mllmet/F");
   TBranch *b_LHE_mll = fChain->Branch("LHE_mll", &LHE_mll, "LHE_mll/F");
   TBranch *b_LHE_theta = fChain->Branch("LHE_theta", &LHE_theta, "LHE_theta/F");
   TBranch *b_LHE_dphill = fChain->Branch("LHE_dphill", &LHE_dphill, "LHE_dphill/F");
   TBranch *b_LHE_dphilmet1 = fChain->Branch("LHE_dphilmet1", &LHE_dphilmet1, "LHE_dphilmet1/F");
   TBranch *b_LHE_dphilmet2 = fChain->Branch("LHE_dphilmet2", &LHE_dphilmet2, "LHE_dphilmet2/F");

   fChain->SetBranchAddress("LHE_mlvlv", &LHE_mlvlv);            //Definisco indirizzo delle variabili dei nuovi Branches
   fChain->SetBranchAddress("LHE_mlvlv_t", &LHE_mlvlv_t);
   fChain->SetBranchAddress("LHE_mllmet", &LHE_mllmet);
   fChain->SetBranchAddress("LHE_mll", &LHE_mll);
   fChain->SetBranchAddress("LHE_theta", &LHE_theta);
   fChain->SetBranchAddress("LHE_dphill", &LHE_dphill);
   fChain->SetBranchAddress("LHE_dphilmet1", &LHE_dphilmet1);
   fChain->SetBranchAddress("LHE_dphilmet2", &LHE_dphilmet2);

   TString option = GetOption();
   TObjArray *buffer = option.Tokenize(" ");
   int i = 0;
   while(i < buffer->GetEntries()) {
   		 opzioni[i] = ((TObjString*)(buffer->At(i)))->String();
		 //std::cout << i << "\t" << opzioni[i] << std::endl;
		 i++;
	}
   //opzioni = option;
   
   if(opzioni[0] == "selection")
         dir = "Selection/";
   if(opzioni[0] == "raw")
         dir = "Raw/";
   if(opzioni[0] == "test")
   		 dir = "Test/";

}

void myselector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t myselector::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.   // It can be passed to either myselector::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
   GetEntry(entry);
   //std::cout << std_vector_LHElepton_pt->size() << std::endl;
   //std::cout << entry << std::endl;

   Float_t lepton_id1 = std_vector_LHElepton_id->at(0), lepton_id2 = std_vector_LHElepton_id->at(1);

   Float_t pt1 = std_vector_LHEneutrino_pt->at(0), pt2 = std_vector_LHEneutrino_pt->at(1);
   Float_t phi1 = std_vector_LHEneutrino_phi->at(0), phi2 = std_vector_LHEneutrino_phi->at(1);
   Float_t eta1 = std_vector_LHEneutrino_eta->at(0), eta2 = std_vector_LHEneutrino_eta->at(1);
   p_neutrino1.SetPtEtaPhiM(pt1, eta1, phi1, 0.);     //Approssimo la massa del neutrino a 0
   p_neutrino2.SetPtEtaPhiM(pt2, eta2, phi2, 0.);     //Approssimo la massa del neutrino a 0
   p_met.SetPtEtaPhiM(metLHEpt, 0., metLHEphi, 0.);	//Approssimo la massa invariante dei due neutrini pari a 0 poiché non la conosco!
													//Metto a zero metLHEeta perché MET è una quantità trasversa e non conosco la componente z!
   pt1 = std_vector_LHElepton_pt->at(0), pt2 = std_vector_LHElepton_pt->at(1);
   phi1 = std_vector_LHElepton_phi->at(0), phi2 = std_vector_LHElepton_phi->at(1);
   eta1 = std_vector_LHElepton_eta->at(0), eta2 = std_vector_LHElepton_eta->at(1);
   p_lepton1.SetPtEtaPhiM(pt1, eta1, phi1, 0.);    //Approssimo la massa del leptone a 0
   p_lepton2.SetPtEtaPhiM(pt2, eta2, phi2, 0.);    //Approssimo la massa del leptone a 0
   p_lepton1_t.SetPtEtaPhiM(pt1, 0., phi1, 0.);    //Approssimo la massa del leptone a 0
   p_lepton2_t.SetPtEtaPhiM(pt2, 0., phi2, 0.);    //Approssimo la massa del leptone a 0
   p_lvlv = p_neutrino1 + p_neutrino2 + p_lepton1 + p_lepton2;
   p_lvlv_t = p_lepton1_t + p_lepton2_t + p_met;
   p_llmet = p_lepton1 + p_lepton2 + p_met;
   p_ll = p_lepton1 + p_lepton2;
   LHE_mlvlv = p_lvlv.M();		//variabile target

   pt1 = std_vector_LHEparton_pt->at(0), pt2 = std_vector_LHEparton_pt->at(1);
   phi1 = std_vector_LHEparton_phi->at(0), phi2 = std_vector_LHEparton_phi->at(1);
   eta1 = std_vector_LHEparton_eta->at(0), eta2 = std_vector_LHEparton_eta->at(1);
   p_parton1.SetPtEtaPhiM(pt1, eta1, phi1, 0.);    //Approssimo la massa del partone a 0
   p_parton2.SetPtEtaPhiM(pt2, eta2, phi2, 0.);    //Approssimo la massa del partone a 0
   p_jj = p_parton1 + p_parton2;
   LHE_mjj = p_jj.M();

   //p_lvlv_t.SetPtEtaPhiM((p_lepton1 + p_lepton2 + p_met).Pt(), 0., (p_lepton1 + p_lepton2 + p_met).Phi(), (p_lepton1 + p_lepton2 + p_met).M());
   LHE_mlvlv_t = p_lvlv_t.M();                     //Massa invariante trasversa leptoni (non longitudinale) + neutrini
   //p_llmet.SetPtEtaPhiM((p_lepton1 + p_lepton2 + p_met).Pt(), (p_lepton1 + p_lepton2).Eta(), (p_lepton1 + p_lepton2 + p_met).Phi(), (p_lepton1 + p_lepton2 + p_met).M());
   LHE_mllmet = p_llmet.M();                     //Massa invariante trasversa leptoni (anche longitudinale) + neutrini
   LHE_theta = p_lepton1.Angle(p_lepton2.Vect());	 //Angolo tra i due leptoni
   LHE_dphill = p_lepton1_t.Angle(p_lepton2_t.Vect());
   LHE_dphilmet1 = p_lepton1_t.Angle(p_met.Vect());
   LHE_dphilmet2 = p_lepton2_t.Angle(p_met.Vect());
   LHE_mll = p_ll.M();

   Bool_t selection = 1;
   if(opzioni[0] == "raw") {
      selection = 1;
      //std::cout << selection << std::endl;
   }
   if(opzioni[0] == "selection") {
      selection = pt1 > 30. && fabs(eta1) < 4.7 && pt2 > 30. && fabs(eta2) < 4.7 && abs(lepton_id1) != 15 && abs(lepton_id2) != 15 && LHE_mlvlv > 130.;
      //std::cout << selection << " " << pt1 << " " <<  pt2 << " " << eta1 << " " << eta2 << " " << lepton_id1 << " " << lepton_id2 << " " << LHE_mlvlv << std::endl;
   }

   int i = 0;
   //if(pt1 > 30. && fabs(eta1) < 4.7 && pt2 > 30. && fabs(eta2) < 4.7 && abs(lepton_id1) != 15 && abs(lepton_id2) != 15 && LHE_mlvlv > 130.) {   //seleziono gli eventi senza TAU
   if(selection) {   //seleziono gli eventi a seconda del valore di selection
      b_LHE_mlvlv->Fill();                //Riempio i Branches con le variabili interessanti
      b_LHE_mlvlv_t->Fill();
      b_LHE_mllmet->Fill();
      b_LHE_mll->Fill();
      b_LHE_theta->Fill();
      b_LHE_dphill->Fill();
      b_LHE_dphilmet1->Fill();
      b_LHE_dphilmet2->Fill();
	   while(i < 2) {
	    	_histo_LHElepton_pt->Fill(std_vector_LHElepton_pt->at(i));
	    	_histo_LHElepton_eta->Fill(std_vector_LHElepton_eta->at(i));
	    	_histo_LHElepton_phi->Fill(std_vector_LHElepton_phi->at(i));
	    	_histo_LHElepton_id->Fill(std_vector_LHElepton_id->at(i));

	    	_histo_LHEparton_pt->Fill(std_vector_LHEparton_pt->at(i));
	    	_histo_LHEparton_eta->Fill(std_vector_LHEparton_eta->at(i));
	   	_histo_LHEparton_phi->Fill(std_vector_LHEparton_phi->at(i));
	   	_histo_LHEparton_id->Fill(std_vector_LHEparton_id->at(i));

	      //std::cout << std_vector_LHElepton_pt->at(i) << std::endl;
			//std::cout << i << std::endl;
	    	i++;
	  }

   _histo_jj_deltaeta->Fill(fabs(eta2 - eta1));   //Riempio istogramma deltaeta jet-jet
   _histo_jj_m->Fill(LHE_mjj);                    //Riempio istogramma massa invariante jet-jet
   _histo_LHEmlvlv->Fill(LHE_mlvlv);
   _histo_metLHE_pt->Fill(metLHEpt);
   _histo_metLHE_eta->Fill(metLHEeta);
   _histo_metLHE_phi->Fill(metLHEphi);

   _histo2_lepton1_pt_mlvlv->Fill(LHE_mlvlv, p_lepton1.Pt());   //Riempio istogrammi 2-D
   _histo2_lepton2_pt_mlvlv->Fill(LHE_mlvlv, p_lepton2.Pt());
   _histo2_met_pt_mlvlv->Fill(LHE_mlvlv, metLHEpt);
   _histo2_mlvlv_t_mlvlv->Fill(LHE_mlvlv, LHE_mlvlv_t);
   _histo2_mllmet_mlvlv->Fill(LHE_mlvlv, LHE_mllmet);
   _histo2_mll_mlvlv->Fill(LHE_mlvlv, LHE_mll);
   _histo2_theta_mlvlv->Fill(LHE_mlvlv, LHE_theta);
   _histo2_dphill_mlvlv->Fill(LHE_mlvlv, LHE_dphill);
   _histo2_dphilmet1_mlvlv->Fill(LHE_mlvlv, LHE_dphilmet1);
   _histo2_dphilmet2_mlvlv->Fill(LHE_mlvlv, LHE_dphilmet2);
   _histo2_dphillxmll_mlvlv->Fill(LHE_mlvlv, LHE_dphill*LHE_mll);

   //outfile << LHE_mlvlv << "\t" << LHE_mlvlv_t << "\t" << LHE_mllmet << "\t" << LHE_mll;                    //Salvo in un file di testo le variabili interessanti
   //outfile << LHE_theta << "\t" << LHE_dphill << "\t" << LHE_dphilmet1 << "\t" << LHE_dphilmet2 << endl;
   
   }

   entries = entry;

   return kTRUE;
}

void myselector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void myselector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   
   gStyle->SetOptFit(1111);
   TStyle *th1Style = new TStyle(*gStyle);
   th1Style->cd();
   //TString file;

   //TCanvas* c1 = new TCanvas ("c1", "c1", 1200, 800);
   TCanvas* c1 = new TCanvas ("c1", "c1", 1196, 690);
   c1->Divide(2, 2);
   _histo_LHElepton_pt->SetFillColor(kYellow);
   _histo_LHElepton_pt->GetXaxis()->SetTitle("p_{T} [GeV]");
   _histo_LHElepton_pt->GetYaxis()->SetTitle("counts");
   _histo_LHElepton_eta->SetFillColor(kRed);
   _histo_LHElepton_eta->GetXaxis()->SetTitle("#eta");
   _histo_LHElepton_eta->GetYaxis()->SetTitle("counts");
   _histo_LHElepton_phi->SetFillColor(kBlue);
   _histo_LHElepton_phi->GetXaxis()->SetTitle("#phi [rad]");
   _histo_LHElepton_phi->GetYaxis()->SetTitle("counts");
   _histo_LHElepton_id->SetFillColor(kGreen);
   c1->cd(1);
   _histo_LHElepton_pt->Draw();
   c1->cd(2);
   _histo_LHElepton_eta->Draw();
   c1->cd(3);
   _histo_LHElepton_phi->Draw();
   c1->cd(4);
   _histo_LHElepton_id->Draw();

   TCanvas* c2 = new TCanvas ("c2", "c2", 1196, 690);
   c2->Divide(2, 2);
   _histo_LHEparton_pt->SetFillColor(kYellow);
   _histo_LHEparton_pt->GetXaxis()->SetTitle("p_{T} [GeV]");
   _histo_LHEparton_pt->GetYaxis()->SetTitle("counts");
   _histo_LHEparton_eta->SetFillColor(kRed);
   _histo_LHEparton_eta->GetXaxis()->SetTitle("#eta");
   _histo_LHEparton_eta->GetYaxis()->SetTitle("counts");
   _histo_LHEparton_phi->SetFillColor(kBlue);
   _histo_LHEparton_phi->GetXaxis()->SetTitle("#phi [rad]");
   _histo_LHEparton_phi->GetYaxis()->SetTitle("counts");
   _histo_LHEparton_id->SetFillColor(kGreen);
   c2->cd(1);
   _histo_LHEparton_pt->Draw();
   c2->cd(2);
   _histo_LHEparton_eta->Draw();
   c2->cd(3);
   _histo_LHEparton_phi->Draw();
   c2->cd(4);
   _histo_LHEparton_id->Draw();

   TCanvas* c3 = new TCanvas ("c3", "c3", 1196, 690);
   c3->Divide(2, 2);
   _histo_metLHE_pt->SetFillColor(kYellow);
   _histo_metLHE_pt->GetXaxis()->SetTitle("p_{T} [GeV]");
   _histo_metLHE_pt->GetYaxis()->SetTitle("counts");
   _histo_metLHE_eta->SetFillColor(kRed);
   _histo_metLHE_eta->GetXaxis()->SetTitle("#eta");
   _histo_metLHE_eta->GetYaxis()->SetTitle("counts");
   _histo_metLHE_phi->SetFillColor(kBlue);
   _histo_metLHE_phi->GetXaxis()->SetTitle("#phi [rad]");
   _histo_metLHE_phi->GetYaxis()->SetTitle("counts");
   c3->cd(1);
   _histo_metLHE_pt->Draw();
   c3->cd(2);
   _histo_metLHE_eta->Draw();
   c3->cd(3);
   _histo_metLHE_phi->Draw();

   TCanvas* c4 = new TCanvas ("c4", "c4", 1200, 800);
   _histo_jj_deltaeta->SetFillColor(kYellow);
   _histo_jj_deltaeta->GetXaxis()->SetTitle("#Delta#eta");
   _histo_jj_deltaeta->GetYaxis()->SetTitle("counts");
   _histo_jj_deltaeta->Draw();

   TCanvas* c5 = new TCanvas ("c5", "c5", 1200, 800);
   _histo_jj_m->SetFillColor(kYellow);
   _histo_jj_m->GetXaxis()->SetTitle("M_{jj} [GeV]");
   _histo_jj_m->GetYaxis()->SetTitle("counts");
   _histo_jj_m->Draw();

   TCanvas* c6 = new TCanvas ("c6", "c6", 1200, 800);
   _histo_LHEmlvlv->SetFillColor(kYellow);
   _histo_LHEmlvlv->GetXaxis()->SetTitle("M_{l#nul#nu} [GeV]");
   _histo_LHEmlvlv->GetYaxis()->SetTitle("counts");
   _histo_LHEmlvlv->Draw();
   //TF1* fitfunc = new TF1 ("fitfunc","gaus", 124.995, 125.005);		//Fit della risonanza dell'Higgs
   //fitfunc->SetParameter(1, 125.0);
   //fitfunc->SetParameter(2, 0.008);
   //_histo_LHEmlvlv->Fit("fitfunc", "R");

	if(entries > 20000 && opzioni[2] != "corr") {
		c1->Print(dir + "leptons.png");
   		c2->Print(dir + "partons.png");
  		c3->Print(dir + "MET.png");
  		c4->Print(dir + "deltaeta_jj.png");
  		c5->Print(dir + "mass_jj.png");
   		c6->Print(dir + "mass_lvlv.png");
   	}
   	else {
   		c1->Close();
   		c2->Close();
   		c3->Close();
   		c4->Close();
   		c5->Close();
   		c6->Close();
   	}

	TStyle *th2Style = new TStyle(*gStyle);
   	th2Style->SetStatX(0.35);
  	th2Style->SetStatY(0.88);
  	th2Style->cd();
  	Option_t* draw_option = "COLZ";
  	if(opzioni[1] == "surf")	draw_option = "SURF1";

   TCanvas* c7 = new TCanvas ("c7", "c7", 1196, 690);
   _histo2_lepton1_pt_mlvlv->GetXaxis()->SetTitle("M_{l#nul#nu} [GeV]");
   _histo2_lepton1_pt_mlvlv->GetYaxis()->SetTitle("p_{T, lepton1} [GeV]");
   _histo2_lepton1_pt_mlvlv->Draw(draw_option);

   TCanvas* c7_bis = new TCanvas ("c7_bis", "c7_bis", 1196, 690);
   _histo2_lepton2_pt_mlvlv->GetXaxis()->SetTitle("M_{l#nul#nu} [GeV]");
   _histo2_lepton2_pt_mlvlv->GetYaxis()->SetTitle("p_{T, lepton2} [GeV]");
   _histo2_lepton2_pt_mlvlv->Draw(draw_option);

   TCanvas* c8 = new TCanvas ("c8", "c8", 1200, 800);
   _histo2_met_pt_mlvlv->GetXaxis()->SetTitle("M_{l#nul#nu} [GeV]");
   _histo2_met_pt_mlvlv->GetYaxis()->SetTitle("p_{T, MET} [GeV]");
   _histo2_met_pt_mlvlv->Draw(draw_option);

   TCanvas* c9 = new TCanvas ("c9", "c9", 1200, 800);
   _histo2_mlvlv_t_mlvlv->GetXaxis()->SetTitle("M_{l#nul#nu} [GeV]");
   _histo2_mlvlv_t_mlvlv->GetYaxis()->SetTitle("M^{T}_{l#nul#nu} [GeV]");
   _histo2_mlvlv_t_mlvlv->Draw(draw_option);

   TCanvas* c10 = new TCanvas ("c10", "c10", 1200, 800);
   _histo2_mllmet_mlvlv->GetXaxis()->SetTitle("M_{l#nul#nu} [GeV]");
   _histo2_mllmet_mlvlv->GetYaxis()->SetTitle("M_{ll, MET} [GeV]");
   _histo2_mllmet_mlvlv->Draw(draw_option);

   TCanvas* c11 = new TCanvas ("c11", "c11", 1200, 800);
   _histo2_mll_mlvlv->GetXaxis()->SetTitle("M_{l#nul#nu} [GeV]");
   _histo2_mll_mlvlv->GetYaxis()->SetTitle("M_{ll} [GeV]");
   _histo2_mll_mlvlv->Draw(draw_option);

   TCanvas* c15 = new TCanvas ("c15", "c15", 1200, 800);
   _histo2_dphillxmll_mlvlv->GetXaxis()->SetTitle("M_{l#nul#nu} [GeV]");
   _histo2_dphillxmll_mlvlv->GetYaxis()->SetTitle("#Delta#phi_{ll} M_{ll} [GeV]");
   _histo2_dphillxmll_mlvlv->Draw(draw_option);

   if(entries > 20000 && opzioni[0] == "selection") {
   		c7->Print("Correlations/pt_lepton1_vs_mlvlv.png");		
   		c7_bis->Print("Correlations/pt_lepton2_vs_mlvlv.png");		
   		c8->Print("Correlations/met_pt_vs_mlvlv.png");
   		c9->Print("Correlations/mlvlv_t_vs_mlvlv.png");
   		c10->Print("Correlations/mllmet_vs_mlvlv.png");
   		c11->Print("Correlations/mll_vs_mlvlv.png");
   		c15->Print("Correlations/dphillxmll_vs_mlvlv.png");
   }

   th1Style->SetStatX(0.88);
   th1Style->SetStatY(0.38);	
   th1Style->cd();

   TCanvas* c12 = new TCanvas ("c12", "c12", 1196, 690);
   _histo2_theta_mlvlv->GetXaxis()->SetTitle("M_{l#nul#nu} [GeV]");
   _histo2_theta_mlvlv->GetYaxis()->SetTitle("#theta_{12} [rad]");
   _histo2_theta_mlvlv->Draw(draw_option);

   TCanvas* c13 = new TCanvas ("c13", "c13", 1200, 800);
   _histo2_dphill_mlvlv->GetXaxis()->SetTitle("M_{l#nul#nu} [GeV]");
   _histo2_dphill_mlvlv->GetYaxis()->SetTitle("#Delta#phi_{ll} [rad]");
   _histo2_dphill_mlvlv->Draw(draw_option);

   TCanvas* c14 = new TCanvas ("c14", "c14", 1200, 800);
   _histo2_dphilmet1_mlvlv->GetXaxis()->SetTitle("M_{l#nul#nu} [GeV]");
   _histo2_dphilmet1_mlvlv->GetYaxis()->SetTitle("#Delta#phi_{l1,MET} [rad]");
   _histo2_dphilmet1_mlvlv->Draw(draw_option);

   TCanvas* c14_bis = new TCanvas ("c14_bis", "c14_bis", 1200, 800);
   _histo2_dphilmet2_mlvlv->GetXaxis()->SetTitle("M_{l#nul#nu} [GeV]");
   _histo2_dphilmet2_mlvlv->GetYaxis()->SetTitle("#Delta#phi_{l2,MET} [rad]");
   _histo2_dphilmet2_mlvlv->Draw(draw_option);
   
   if(entries > 20000 && opzioni[0] == "selection") {
   		c12->Print("Correlations/theta_vs_mlvlv.png");
   		c13->Print("Correlations/dphill_vs_mlvlv.png");
   		c14->Print("Correlations/dphilmet1_vs_mlvlv.png");
   		c14_bis->Print("Correlations/dphilmet2_vs_mlvlv.png");
   }

   std::ofstream output ("Correlations/correlation.txt", std::ios::out);

   std::cout << "variable\tcorrelation factor" << std::endl;
   std::cout << "pt_lepton1\t" << _histo2_lepton1_pt_mlvlv->GetCorrelationFactor() << std::endl;
   std::cout << "pt_lepton2\t" << _histo2_lepton2_pt_mlvlv->GetCorrelationFactor() << std::endl;
   std::cout << "met_pt\t\t" << _histo2_met_pt_mlvlv->GetCorrelationFactor() << std::endl;
   std::cout << "mlvlv_t\t\t" << _histo2_mlvlv_t_mlvlv->GetCorrelationFactor() << std::endl;
   std::cout << "mllmet\t\t" << _histo2_mllmet_mlvlv->GetCorrelationFactor() << std::endl;
   std::cout << "mll\t\t" << _histo2_mll_mlvlv->GetCorrelationFactor() << std::endl;
   std::cout << "theta\t\t" << _histo2_theta_mlvlv->GetCorrelationFactor() << std::endl;
   std::cout << "dphill\t\t" << _histo2_dphill_mlvlv->GetCorrelationFactor() << std::endl;
   std::cout << "dphilmet1\t" << _histo2_dphilmet1_mlvlv->GetCorrelationFactor() << std::endl;
   std::cout << "dphilmet2\t" << _histo2_dphilmet2_mlvlv->GetCorrelationFactor() << std::endl;
   std::cout << "dphill*mll\t" << _histo2_dphillxmll_mlvlv->GetCorrelationFactor() << std::endl;

   output << "variable\tcorrelation factor" << endl;
   output << "pt_lepton1\t" << _histo2_lepton1_pt_mlvlv->GetCorrelationFactor() << endl;
   output << "pt_lepton2\t" << _histo2_lepton2_pt_mlvlv->GetCorrelationFactor() << endl;
   output << "met_pt\t\t" << _histo2_met_pt_mlvlv->GetCorrelationFactor() << endl;
   output << "mlvlv_t\t\t" << _histo2_mlvlv_t_mlvlv->GetCorrelationFactor() << endl;
   output << "mllmet\t\t" << _histo2_mllmet_mlvlv->GetCorrelationFactor() << endl;
   output << "mll\t\t" << _histo2_mll_mlvlv->GetCorrelationFactor() << endl;
   output << "theta\t\t" << _histo2_theta_mlvlv->GetCorrelationFactor() << endl;
   output << "dphill\t\t" << _histo2_dphill_mlvlv->GetCorrelationFactor() << endl;
   output << "dphilmet1\t" << _histo2_dphilmet1_mlvlv->GetCorrelationFactor() << endl;
   output << "dphilmet2\t" << _histo2_dphilmet2_mlvlv->GetCorrelationFactor() << endl;
   output << "dphill*mll\t" << _histo2_dphillxmll_mlvlv->GetCorrelationFactor() << endl;

   output.close();
   //outfile.close();
   //TTree *fChain = latino;

   fChain->SetBranchStatus("*", 0);                              //Attivo solo i Branches che mi interessano
   fChain->SetBranchStatus("std_vector_LHElepton_pt", 1);
   fChain->SetBranchStatus("metLHEpt", 1);
   fChain->SetBranchStatus("LHE_mlvlv", 1);
   fChain->SetBranchStatus("LHE_mlvlv_t", 1);
   fChain->SetBranchStatus("LHE_mllmet", 1);
   fChain->SetBranchStatus("LHE_mll", 1);
   fChain->SetBranchStatus("LHE_theta", 1);
   fChain->SetBranchStatus("LHE_dphill", 1);
   fChain->SetBranchStatus("LHE_dphilmet1", 1);
   fChain->SetBranchStatus("LHE_dphilmet2", 1);

   /*fChain->SetBranchAddress("LHE_mlvlv", &LHE_mlvlv);
   fChain->SetBranchStatus("*", 0);                          //PROVA: salvo un TTree con la sola variabile std_vector_LHElepton_pt
   fChain->SetBranchStatus("std_vector_LHElepton_pt", 1);
   fChain->SetBranchStatus("metLHEpt", 1);
   fChain->SetBranchStatus("LHE_mlvlv", 1);                  //errore: unknown branch -> LHE_mlvlv*/

   TFile *newfile = new TFile("WpWpJJ_reduced.root","recreate");
   TTree *newtree = fChain->CloneTree();
   newtree->SetName("latino_reduced");

   std::cout << "Nuovo TTree salvato." << std::endl;
   newtree->Print();
   newtree->Write();
   newfile->Write();
   std::cout << "Lista dei contenuti del file WpWmJJ_reduced.root:" << std::endl;
   newfile->ls();
   delete newfile;
}
