#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

//AFR, Analysis script For Root
void AFR(){
    TFile* tfile = new TFile("h1.root");
    TH2F* h1 = (TH2F*)tfile->Get("h1");
    h1->Draw();
    return;
}