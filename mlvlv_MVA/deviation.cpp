/*
compile with:
g++ deviation.cpp -o deviation.o `root-config --cflags --glibs`
*/

//This program fits the angular correlation graph of gamma-gamma emission from Co60

#include <fstream>
#include <TMultiGraph.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TROOT.h>
#include <string>
#include <TLegend.h>
#include <cmath>

int main(int argc, char **argv) {
	if(argc < 2) {
		std::cout << "Errore: inserire file sorgente come primo argomento." << std::endl;
		return 1;
	}

	if(argc < 3) {
		std::cout << "Errore: inserire opzione come secondo argomento." << std::endl;
		return 1;
	}

	int nColoumns = 4;
	TString option(argv[2]);
	if(option == "overtraining")	nColoumns = 6;

	const int n = 50;
	double par[n], mean[n], rms[n];
	double mean1[n], rms1[n];

	std::ifstream infile(argv[1]);
	int j = 0;
	char buffer[20];

	for(int i = 0; i < nColoumns; i++) {
		infile >> buffer;
	}
	
	while(infile.good()) {
		if(nColoumns == 4) {
			infile >> buffer >> par[j] >> mean[j] >> rms[j];
			mean1[j] = 0.;
			rms1[j] = 0.;
		}
		if(nColoumns == 6)
			infile >> buffer >> par[j] >> mean[j] >> rms[j] >> mean1[j] >> rms1[j];
		j++;
	}
	infile.close();
	int npoints = j;

	TString TrainName(buffer);
	if(TrainName == "NT")		TrainName = "NTrees";
	if(TrainName == "SK")		TrainName = "Shrinkage";
	if(TrainName == "F")		TrainName = "Fraction";
	if(TrainName == "MD")		TrainName = "MaxDepth";

	TApplication* Grafica = new TApplication("Grafica", 0, NULL);
	TGraph *deviation = new TGraph(npoints-1, par, mean);
	TGraph *RMS = new TGraph(npoints-1, par, rms);
	TGraph *deviation1;
	TGraph *RMS1;
   	TLegend *legend = new TLegend(0.78, 0.60, 0.98, 0.75);

	if(nColoumns == 6) {
		deviation1 = new TGraph(npoints-1, par, mean1);
		RMS1 = new TGraph(npoints-1, par, rms1);

		deviation1->SetMarkerColor(kBlue);
		deviation1->SetLineColor(kBlue);
		deviation1->SetMarkerStyle(7);
		deviation1->SetMarkerSize(5);

		RMS1->SetMarkerColor(kBlue);
		RMS1->SetLineColor(kBlue);
		RMS1->SetMarkerStyle(7);
		RMS1->SetMarkerSize(5);
	}

	deviation->SetMarkerColor(kRed);
	deviation->SetLineColor(kRed);
	deviation->SetMarkerStyle(7);
	deviation->SetMarkerSize(5);	

	RMS->SetMarkerColor(kRed);
	RMS->SetLineColor(kRed);
	RMS->SetMarkerStyle(7);
	RMS->SetMarkerSize(5);

	TMultiGraph *gr_dev = new TMultiGraph();
	TMultiGraph *gr_rms = new TMultiGraph();
	gr_dev->Add(deviation);
	gr_dev->SetTitle("deviation vs " + TrainName + "; "+ TrainName + "; Deviation");
	gr_rms->Add(RMS);
	gr_rms->SetTitle("RMS vs " + TrainName + "; "+ TrainName + "; RMS");

	if(nColoumns == 6) {	
		gr_dev->Add(deviation1);
		gr_rms->Add(RMS1);
	}


	gStyle->SetOptFit(1111);

	TCanvas *c1 = new TCanvas(TrainName,TrainName,800,600);
	c1->Divide(2,1);
	c1->cd(1);
	gr_dev->Draw("ape");
	
	c1->cd(2);
	gr_rms->Draw("ape");

	if(nColoumns == 6) {
		legend->AddEntry(RMS, "Train", "p");
   		legend->AddEntry(RMS1, "Test", "p");
   		legend->Draw();
	}

	if(option == "overtraining")
		c1->Print(TrainName + "/overtrain.png");
	else
		c1->Print(TrainName + "/deviation.png");

	Grafica->Run();
	return 0;
}
