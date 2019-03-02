#include "MyMaker.h"
#include <iostream>

#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"

#include "TFile.h"
#include "TH1F.h"
#include "TObjArray.h"

#define XIAOHAI
#ifdef XIAOHAI
#    include "StPicoDst.h"
#    include "StPicoDstMaker.h"
#    include "StPicoEvent.h"
#    include "StPicoTrack.h"
#    include "StRunInfo.h"
#endif

ClassImp(MyMaker)

    MyMaker::MyMaker(StPicoDstMaker *maker, const char *name)
    : StMaker(name) {
    picoDstMaker = maker;

    hisVertexZ = nullptr;
    hisRefMult = nullptr;
    hisPt = nullptr;
    hisOutputFile = nullptr;

    eventProcessed = 0;

    hisOutputFileName = "";
}
MyMaker::~MyMaker() {
}

Int_t MyMaker::Init() {
    if (hisOutputFileName != "") {
        hisOutputFile = new TFile(hisOutputFileName, "RECREATE");
    } else {
        cout << "Error: Please specify the histogtam output file!!!!!!!!!!!!!!" << endl;
    }

    hisVertexZ = new TH1F("VertexZ", "Event Vertex Z Position", 20000, -100, 100);
    hisRefMult = new TH1F("RefMult", "Reference of Multiplicity of events", 1000, 0.0, 1000.0);
    hisPt = new TH1F("pt", "the pt of tracks", 200, 0.0, 20.0);
    hisMagnetic = new TH1F("Magnetic", "Magnetic", 200, -10.0, 10.0);

    return kStOK;
}

Int_t MyMaker::Make() {
    StPicoEvent *picoEvent = picoDstMaker->picoDst()->event();

    if (!picoEvent) {
        return kStOK;
    }
    if (!picoEvent->isTrigger(1)) {
        return kStOK;
    }

    StThreeVectorF primaryVertex = picoEvent->primaryVertex();
    if (fabs(primaryVertex.x()) < 1e-5f && fabs(primaryVertex.y()) < 1e-5f && fabs(primaryVertex.z()) < 1e-5f) {
        return kStOK;
    }
    if (primaryVertex.perp() > 2.0f) {
        return kStOk;
    }
    hisVertexZ->Fill(primaryVertex.z());

    hisRefMult->Fill(picoEvent->refMult());

    TObjArray *tracks = picoDstMaker->picoDst()->primaryTracks();
    TObjArrayIter GetTracks(tracks);

    StMuTrack *track = 0;
    while ((track = (StMuTrack *)GetTracks.Next())) {
        const StMuBTofPidTraits &tofpid = track->btofPidTraits();

        double tofbeta = -999.0;
        tofbeta = tofpid.beta();
        if (tofbeta > 0) {
            // beta2->Fill(tofpid.beta());
        }

        hisPt->Fill(track->pt());
    }
    eventProcessed++;
    return kStOK;
}
Int_t MyMaker::Finish() {
    hisOutputFile->Write();
    cout << "Total Events Processed in DstMaker  " << eventProcessed << endl;
    return kStOK;
}

void MyMaker::setOutputFileName(TString name) {
    hisOutputFileName = name;
}
