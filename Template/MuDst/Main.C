//#include "StRoot/MyMaker/MyMaker.h"

//#define XIAOHAI
#ifdef XIAOHAI
#    include "COMMON/StMuDstMaker.h"
#    include "StChain.h"
#    include "StMaker.h"
#    include "TROOT.h"
#    include "TSystem.h"
#endif

void Main(TString InputFileList, Int_t nFiles = 1000, Int_t nEvents = 0, TString OutputDir = "output/", TString JobIdName = "testrun") {
    gROOT->Macro("loadMuDst.C");
    gSystem->Load("MyMaker.so");

    // List of member links in the chain
    StChain* chain = new StChain;

    StMuDstMaker* muDstMaker = new StMuDstMaker(0, 0, "", InputFileList, "MuDst", nFiles);
    // Turn off everything but Primary tracks in order to speed up the analysis and eliminate IO
    // muDstMaker -> SetStatus("*",0);// Turn off all branches
    // muDstMaker -> SetStatus("MuEvent",1); // Turn on the Event data (esp. Event number)
    // muDstMaker -> SetStatus("PrimaryTracks",1);// Turn on the global track data
    muDstMaker->SetDebug(0);  // Turn off Debug information

    MyMaker* test = new MyMaker(muDstMaker, "testMaker");
    TString Name = JobIdName;
    Name.Append(".test.histo.root");
    test->setOutputFileName(OutputDir + Name);
    test->SetDebug(0);

    if (nEvents == 0) {
	nEvents = 10000000;
    }
    Int_t iInit = chain->Init();
    if (iInit) {
	chain->Fatal(iInit, "on init");
    }
    Int_t totalE = muDstMaker->chain()->GetEntries();

    Int_t istat = 0, i = 1;
    cout << " Total entries = " << totalE << endl;
    if (nEvents > totalE) {
	nEvents = totalE;
    }

    while (i <= nEvents && istat != 2) {
	if (i % 1000 == 0) {
	    cout << endl << "== Event " << i << " start ==" << endl;
	}
	chain->Clear();
	istat = chain->Make(i);
	if (istat == 2) {
	    cout << "Last  event processed. Status = " << istat << endl;
	}
	if (istat == 3) {
	    cout << "Error event processed. Status = " << istat << endl;
	}
	i++;
    }

    if (nEvents > 1) {
	chain->Finish();
    }

    delete chain;
}
