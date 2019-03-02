#define XIAOHAI
#ifdef XIAOHAI
#    include "COMMON/StMuDstMaker.h"
#    include "StChain.h"
#    include "TChain.h"
#    include "TROOT.h"
#    include "TSystem.h"
#endif

#include "StRoot/StMyMaker/StMyMaker.h"

void Main(TString inFile, TString outFile) {
    // Load libraries
    gROOT->Macro("loadMuDst.C");
    gSystem->Load("StMyMaker.so");

    // List of member links in the chain
    StChain* chain = new StChain;
    StMuDstMaker* muDstMaker = new StMuDstMaker(0, 0, "", inFile, ".", 50);
    StMyMaker* myMaker = new StMyMaker(muDstMaker);
    myMaker->SetFileName("test.root");

    // Loop over the links in the chain
    chain->Init();

    Int_t numberEvents = muDstMaker->chain()->GetEntries();
    for (Int_t i = 0; i != numberEvents; ++i) {
        chain->Clear();
        chain->Make(i);
    }

    chain->Finish();

    // Cleanup
    delete chain;
}
