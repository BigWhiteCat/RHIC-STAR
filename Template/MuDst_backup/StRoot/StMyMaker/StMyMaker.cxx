#define XIAOHAI
#ifdef XIAOHAI
#    include "COMMON/StMuDst.h"
#    include "COMMON/StMuDstMaker.h"
#    include "COMMON/StMuEvent.h"
#    include "COMMON/StMuTrack.h"
#    include "StThreeVectorD.hh"
#    include "StThreeVectorF.hh"
#elif

#endif

#include <iostream>

#include "TH1D.h"

#include "StMyMaker.h"

ClassImp(StMyMaker);

/*!
 * \brief StMyMaker::StMyMaker
 * \param maker
 */
StMyMaker::StMyMaker(StMuDstMaker *muDstMaker) {
    this->muDstMaker = muDstMaker;

    eventsProcessed = 0;
    fileName = "";
}

/*!
 * \brief StMyMaker::~StMyMaker
 */
StMyMaker::~StMyMaker() {
}

/*!
 * \brief  Do once at the start the analysis, open files, create histograms, etc.
 * \return
 */
Int_t StMyMaker::Init() {
    hisVz = new TH1D("hisVz", "hisVz", 840, -210.0, 210.0);
    hisRefMult = new TH1D("hisRefMult", "hisRefMult", 10000, 0.0, 10000.0);
    hisPt = new TH1D("hisPz", "hisPz", 100, 0.0, 10.0);

    return StMyMaker::Init();
}

/*!
 * \brief StMyMaker::Clear
 * \param option
 */
void StMyMaker::Clear(Option_t *option) {
}

/*!
 * \brief
 * \return
 */
Int_t StMyMaker::Make() {
    cout << "***** analysis each event *****" << endl;

    StMuEvent *muEvent = muDstMaker->muDst()->event();
    if (!muEvent) {
	return kStOK;
    }

    hisVz->Fill(muEvent->primaryVertexPosition().z());
    hisRefMult->Fill(muEvent->refMult());

    TClonesArray *tracks = dynamic_cast<TClonesArray *>(muDstMaker->muDst()->primaryTracks());
    TIter next(tracks);

    StMuTrack *track = nullptr;
    while (track = (StMuTrack *)next()) {
	hisPt->Fill(track->pt());
    }

    ++eventsProcessed;

    return kStOK;
}

/*!
 * \brief Do once at the end of the analysis, final updates, close files, etc.
 * \return
 */
Int_t StMyMaker::Finish() {
    cout << "***** Number of events processed = " << eventsProcessed << endl;

    TFile *file = new TFile(fileName, "RECREATE");
    hisVz->Write();
    hisRefMult->Write();
    hisPt->Write();
    file->Write();

    return kStOK;
}

/*!
 * \brief StMyMaker::SetFileName
 * \param name
 */
void StMyMaker::SetFileName(TString name) {
    fileName = name;
}
