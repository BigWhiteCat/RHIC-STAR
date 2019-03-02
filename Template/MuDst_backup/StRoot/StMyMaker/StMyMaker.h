#ifndef StMyMaker_H
#define StMyMaker_H

#include "StMaker.h"

class StMuDstMaker;
class TFile;
class TH1D;

class StMyMaker : public StMaker {
  public:
    StMyMaker(StMuDstMaker *muDstMaker);
    virtual ~StMyMaker();

    Int_t Init();
    void Clear(Option_t *option);
    Int_t Make();
    Int_t Finish();

    void SetFileName(TString name);

  private:
    StMuDstMaker *muDstMaker;

    int eventsProcessed;
    TString fileName;

    TH1D *hisVz;
    TH1D *hisRefMult;
    TH1D *hisPt;

  public:
    ClassDef(StMyMaker, 1)  //	Macro for CINT compatability
};

#endif
