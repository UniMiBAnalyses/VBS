/*
Questa macro è un esempio per clonare un nuovo TTree con solo 3 Branches attivati.
Questa macro apre il file WpWmJJ/latino_WpWmJJ_EWK.root, salva il TTree "latino" contenuto nel file
e definisce le variabili associate ad ogni TBranch, che vengono attivate per essere salvate in un secondo TTree.
Il risultato è un nuovo file, "small.root", che contiene solamente il TTree "latinino" con le variabili metLHE...
*/

void newtree() {

   //Get old file, old tree and set top branch address
   TFile *oldfile = new TFile("WpWmJJ/latino_WpWmJJ_EWK.root");
   if(oldfile->IsOpen())	std::cout << "Apertura file riuscita." << std::endl;
   std::cout << "Lista dei contenuti del file WpWmJJ/latino_WpWmJJ_EWK.root:" << std::endl;
   oldfile->ls();		//List file contents
   TTree *oldtree = (TTree*)oldfile->Get("latino");			//"oldtree" sarà uguale al mio TTree "latino"

   float metLHEpt;
   float metLHEeta;
   float metLHEphi;
   oldtree->SetBranchAddress("metLHEpt", &metLHEpt);		//Voglio creare un nuovo TTree con le sole variabili metLHE...
   oldtree->SetBranchAddress("metLHEeta", &metLHEeta);
   oldtree->SetBranchAddress("metLHEphi", &metLHEphi);
   oldtree->SetBranchStatus("*",0);
   oldtree->SetBranchStatus("metLHE*",1);
   oldtree->SetName("latinino");
   //TObjArray *lista = oldtree->GetListOfBranches();		//Stampo la lista dei Branches
   //lista->Print();

   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile("small.root","recreate");
   TTree *newtree = oldtree->CloneTree();

   std::cout << "Nuovo TTree salvato." << std::endl;
   newtree->Print();
   newfile->Write();
   std::cout << "Lista dei contenuti del file small.root:" << std::endl;
   newfile->ls();
   delete oldfile;
   delete newfile;
}
