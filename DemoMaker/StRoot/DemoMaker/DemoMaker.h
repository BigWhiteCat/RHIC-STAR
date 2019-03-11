#ifndef DEMOMAKER_H
#define DEMOMAKER_H

#include "StMaker.h"

class DemoMaker : public StMaker
{

 private:

  ULong_t mEventsProcessed ;

 protected:

 public:

  DemoMaker( ) ;              //  Constructor
  virtual ~DemoMaker( ) ;     //  Destructor

  Int_t Init     ( ) ;              //  Initiliaze the analysis tools ... done once
  Int_t Make     ( ) ;              //  The main analysis that is done on each event
  Int_t Finish   ( ) ;              //  Finish the analysis, close files, and clean up.

  ClassDef(DemoMaker,1)       //  Macro for CINT compatability

};

#endif
