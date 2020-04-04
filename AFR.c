#include "TFile.h"
#include "TH2F.h"
#include "TH1F.h"

//AFR, Analysis script For Root
void AFR(){
    TCanvas *c1 = new TCanvas("c1","c1");
    c1->Divide(2,1);
    c1->SetWindowSize(1000,500);
    TFile* tfile = new TFile("testrandom.root");
    TH2F* h1 = (TH2F*)tfile->Get("h1");
    TH1F* h2 = (TH1F*)tfile->Get("h2");

    h1->SetXTitle("x");
    h1->SetYTitle("y");
    h2->SetXTitle("\\theta");
    h2->SetYTitle("count");



    c1->cd(1);
    h1->Draw();
    c1->cd(2);
    h2->Draw("B");
    return;
}