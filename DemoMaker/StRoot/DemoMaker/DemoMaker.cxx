#include "DemoMaker.h"
#include <iostream>

ClassImp(DemoMaker); /*!< Macro for CINT compatibility */

/*! Class constructor ... zero pointers, zero public/private data members, etc. */
DemoMaker::DemoMaker() : StMaker() {
}

/*! Class destructor ... destroy and/or zero out pointers and public/private data members */
DemoMaker::~DemoMaker() {
}

/*! Do once at the start the analysis, open files, create histograms, etc. */
Int_t DemoMaker::Init() {
    mEventsProcessed = 0;
    return kStOK;
}

/*! Do once at the start of every event */
Int_t DemoMaker::Make() {
    cout << "\033[31m This is a demo. \033[0m" << endl;
    mEventsProcessed++;
    return kStOK;
}

/*! // Do once at the end of the analysis, final updates, close files, etc. */
Int_t DemoMaker::Finish() {
    cout << "\033[32m Number of events processed is " << mEventsProcessed << "\033[0m" << endl;
    return kStOK;
}
