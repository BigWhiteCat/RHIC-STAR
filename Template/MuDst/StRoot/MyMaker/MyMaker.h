#ifndef MyMaker_H
#define MyMaker_H

#include "StMaker.h"
#include "TString.h"

class StMuDstMaker;
class TFile;
class TH1F;

class MyMaker : public StMaker {
  public:
    MyMaker(StMuDstMaker *maker, const char *name);
    virtual ~MyMaker();

    Int_t Init();
    Int_t Make();
    Int_t Finish();

    void setOutputFileName(TString name);

  private:
    ULong_t eventProcessed;
    StMuDstMaker *muDstMaker;

    TFile *hisOutputFile;
    TString hisOutputFileName;

    TH1F *hisVertexZ;
    TH1F *hisPt;
    TH1F *hisRefMult;
    TH1F *hisMagnetic;

  public:
    ClassDef(MyMaker, 1)
};
#endif
