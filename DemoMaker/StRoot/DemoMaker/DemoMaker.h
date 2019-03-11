#ifndef DEMOMAKER_H
#define DEMOMAKER_H

#include "StMaker.h"

class DemoMaker : public StMaker {
  public:
    /*!  Constructor */
    DemoMaker();
    /*!  Destructor */
    virtual ~DemoMaker();

    /*! Initiliaze the analysis tools ... done once */
    Int_t Init();
    /*! The main analysis that is done on each event */
    Int_t Make();
    /*! Finish the analysis, close files, and clean up. */
    Int_t Finish();

  private:
    ULong_t mEventsProcessed;

  public:
    ClassDef(DemoMaker, 1) /*!< Macro for CINT compatability */
};

#endif
