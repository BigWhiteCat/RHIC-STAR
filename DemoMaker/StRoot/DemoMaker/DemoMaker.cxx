#include "DemoMaker.h"
#include <iostream>

ClassImp(DemoMaker)  // Macro for CINT compatibility

DemoMaker::DemoMaker( ) : StMaker( )
{
  // Class constructor ... zero pointers, zero public/private data members, etc.
}


DemoMaker::~DemoMaker()
{
  // Class destructor ... destroy and/or zero out pointers and public/private data members
}


Int_t DemoMaker::Init( )
{
  // Do once at the start the analysis, open files, create histograms, etc.
  mEventsProcessed = 0 ;
  return kStOK ;
}


Int_t DemoMaker::Make( )
{
  // Do once at the start of every event
  cout << "\033[31m This is a demo. \033[0m" << endl ;
  mEventsProcessed++ ;
  return kStOK ;
}


Int_t DemoMaker::Finish( )

{ // Do once at the end of the analysis, final updates, close files, etc.
  cout << "\033[32m Number of events processed is " << mEventsProcessed << "\033[0m" << endl ;
  return kStOK ;
}
