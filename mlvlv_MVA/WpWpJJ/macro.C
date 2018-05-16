/*
option è l'argomento per determinare la selezione sugli eventi:
"raw":			No selection
"selection":	pt1 > 30. && fabs(eta1) < 4.7 && pt2 > 30. && fabs(eta2) < 4.7 && abs(lepton_id1) != 15 && abs(lepton_id2) != 15 && LHE_mlvlv > 130.
*/
//.x macro(-1, "selection colz corr")		Esempi di esecuzione della macro
//.x macro(20000, "raw surf abcd")
void macro(int entries, TString option) {
	//gRoot->Reset();
	TFile *_file0 = TFile::Open("latino_WpWpJJ_EWK.root");

	if(entries < 0)
		latino->Process("myselector.C", option);				//eseguo il selettore su tutti gli eventi del TTree
	else
		latino->Process("myselector.C", option, entries);			//eseguo il selettore solamente sui primi "entries" eventi del TTree
}
