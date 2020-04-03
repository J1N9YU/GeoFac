#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

//AFR, Analysis script For Root
void AFR(){
    TCanvas *c1 = new TCanvas("c1","c1");
    c1->Divide(2,1);
    TFile* tfile = new TFile("testrandom.root");
    TH2F* h1 = (TH2F*)tfile->Get("h1");
    TH1F* h2 = (TH1F*)tfile->Get("h2");
    c1->cd(1);
    h1->Draw();
    c1->cd(2);
    h2->Draw();
    return;
}