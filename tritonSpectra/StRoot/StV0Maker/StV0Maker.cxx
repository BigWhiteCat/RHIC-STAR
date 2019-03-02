#define XIAOHAI
#ifdef XIAOHAI
#    include "COMMON/StMuDstMaker.h"
#    include "COMMON/StMuEvent.h"
#    include "COMMON/StMuTrack.h"
#    include "StStrangeMuDstMaker.h"
#    include "StV0MuDst.hh"
#endif

#include "StDcaService.h"
#include "StV0Maker.h"
#include "StarClassLibrary/SystemOfUnits.h"
//#include "StBichsel/Bichsel.h"

#include <iostream>
using namespace std;

#include "StMessMgr.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StStrangeMuDstMaker/StStrangeMuDstMaker.h"
#include "StStrangeMuDstMaker/StV0MuDst.hh"

#include "StEvent/StBTofHeader.h"
#include "StMuDSTMaker/COMMON/StMuBTofHit.h"
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"

#include "runnumber.h"
//#include "StStrangeMuDstMaker/StStrangeEvMuDst.hh"

#include "TFile.h"
#include "TH1.h"
#include "TH2F.h"
#include "TObjArray.h"
#include "TTree.h"

ClassImp(StV0Maker)  // Macro for CINT compatibility

    // StV0Maker::StV0Maker( StMuDstMaker* maker,const char * name) : StMaker(name)
    StV0Maker::StV0Maker(StMuDstMaker* maker, const char* name)
    : StMaker(name) {  // Initialize and/or zero all public/private data members here.

    // for ( Int_t i = 0 ; i < kMaxNumberOfTH1F ; i++ )  // Zero the histogram pointers, not necessary. it is NULL naturaly.
    //  {
    //    histogram[i] = NULL ;
    //  }

    mMuDstMaker = maker;  // Pass MuDst pointer to DstAnlysisMaker Class member functions
    mV0Type = kLambda;    // Lambda as default!

    mRotate = false;
    mTof = true;
    mSameSignPlus = false;
    mSameSignMinus = false;

    mDcaAlgoLong = true;  //

    histogram_output = NULL;  // Zero the Pointer to histogram output file
    v0tree_output = NULL;     // Zero the Pointer to v0 tree output file
    toftree_output = NULL;    // Zero the Pointer to v0 tree output file

    mHistogramOutputFileName = "";  // Histogram Output File Name will be set inside the "analysis".C macro
    mV0TreeOutputFileName = "";     // V0 Output File Name will be set inside the "analysis".C macro
    mTofTreeOutputFileName = "";    // TOF Output File Name will be set inside the "analysis".C macro
    mHe3EventIdListName = "";

    mV0Tree = NULL;
    mTofTree = NULL;
    mEventsProcessed = 0;  // Zero the Number of Events processed by the maker
    countHe3 = 0;
    countDeuteron = 0;
    countTriton = 0;

    mTestNTrack = 0;
    mTestVZ = 0;
}

StV0Maker::~StV0Maker() {  // Destroy and/or zero out all public/private data members here.
}

void StV0Maker::initConst() {
    // initialize the constant for different V0 types.

    // for L:He3+pi- and AntiL: Anti-He3+pi+
    mMass1 = 2.809;    // mass of He3
    mMass2 = 0.13957;  // mass of pion
    mMassV0 = 2.991;   // mass of Lamb-He3

    if (mV0Type == kLambda) {
        mCharge1 = 1;
        mCharge2 = -1;
    }
    if (mV0Type == kAntiLambda) {
        mCharge1 = -1;
        mCharge2 = 1;
    }
    // added the same-sign loop for bg reconstruction, statistics
    if (mV0Type == kKs) {
        mCharge1 = 1;
        mCharge2 = 1;
    }
    if (mV0Type == kPhoton) {
        mCharge1 = -1;
        mCharge2 = -1;
    }

    // do not setup the cut values here. those are parameters

    // parameters for StDcaService.cxx
    kShiftConnect = 0.3;
    kShiftContain = 0.3;

    return;
}

void StV0Maker::initParam() {
    // setup the cut values here. do not hard-code them in ::Make()

    BeamEnergy = 7;

    SetEventCuts(BeamEnergy);

    cutNHitsGr = 15;
    cutNHitsDedxGr = 15;
    // 1113	cutPtGrEq = 0.20;
    cutPtGrEq = 0.20;

    // initial dedx_He_th[]
    float temp;
    ifstream f_dedx_th;
    f_dedx_th.open("/star/u/jhai/dedx/dedx_mean_helium3_dx5cm.dat");
    for (int i = 0; i < 11901; i++) {
        f_dedx_th >> temp >> dedx_He3_th[i];
    }
    f_dedx_th.close();
    for (int i = 0; i < 11901; i++) {
        dedx_He3_th[i] *= 1.e-6;  // to adjust the unit of dex to GeV/cm
    }

    float temp_2;
    ifstream f_dedx_th_he4;
    f_dedx_th_he4.open("/star/u/jhai/dedx/dedx_mean_He4.dat");
    for (int i = 0; i < 11901; i++) {
        f_dedx_th_he4 >> temp_2 >> dedx_He4_th[i];
    }
    f_dedx_th_he4.close();
    for (int i = 0; i < 11901; i++) {
        dedx_He4_th[i] *= 1.e-6;  // to adjust the unit of dex to GeV/cm
    }

    float temp_3;
    ifstream f_dedx_th_triton;
    f_dedx_th_triton.open("/star/u/jhai/dedx/dedx_mean_triton.dat");
    for (int i = 0; i < 11901; i++) {
        f_dedx_th_triton >> temp_3 >> dedx_Triton_th[i];
    }
    f_dedx_th_triton.close();
    for (int i = 0; i < 11901; i++) {
        dedx_Triton_th[i] *= 1.e-6;  // to adjust the unit of dex to GeV/cm
    }

    float temp_4;
    ifstream f_dedx_th_deuteron;
    f_dedx_th_deuteron.open("/star/u/jhai/dedx/dedx_mean_deuteron.dat");
    for (int i = 0; i < 11901; i++) {
        f_dedx_th_deuteron >> temp_4 >> dedx_Deuteron_th[i];
    }
    f_dedx_th_deuteron.close();
    for (int i = 0; i < 11901; i++) {
        dedx_Deuteron_th[i] *= 1.e-6;  // to adjust the unit of dex to GeV/cm
    }

    return;
}
void StV0Maker::initHisto() {
    // Create Histograms
    // there is no better way to set QA histograms. do not use histogram arrays or vectors.
    // it is not useful. there are no need to operate all the histograms at the same time.
    const Int_t nbins = 100;
    double Tritonpt[] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.4, 3.8, 4.2, 4.6, 5.0, 5.4};
    const int Tritonptnbins = sizeof(Tritonpt) / sizeof(Tritonpt[0]) - 1;
    // QA for events
    //  hNPrimVertex  = new TH1D( "PrimVertex", "Number of Primary Vertex", 10, 0.0, 10.0 ) ;
    // for primary vertex, the dca are all dcaGlobal
    hTriggerType = new TH1D("TriggerType", "Trigger Type(minbias=1,central=2,both=3)", 5, 0, 5);
    hVertexZ = new TH1D("VertexZ", "Event Vertex Z Position", nbins * 20, -200.0, 200.0);
    hSelectVertexZ = new TH1D("SelectVertexZ", "Event Vertex Z Position of selected events", nbins * 20, -200.0, 200.0);
    //-----------for 200GeV--------------
    hvzdiff = new TH1D("vzdiff", "The difference between Event Vertex Z Position and VPD Vz", nbins * 20, -200.0, 200.0);
    hvpdVz_vz_passEvent = new TH2D("vpdVz_vz_passEvent", "VPD Event Vertex Z Position vs Primary Vz after multi vr cut", nbins * 20, -200.0, 200.0, nbins * 20, -200.0, 200.0);
    //------------
    hRefmult_comp = new TH2D("Refmult_comp", "Reference Multiplicity vs corrected refmul", 1000, 0.0, 1000.0, 1000, 0.0, 1000.0);
    hNRefMult = new TH1D("RefMult", "Reference Multiplicity", 1000, 0.0, 1000.0);
    hSelectNRefMult = new TH1D("SelectRefMult", "Reference Multiplicity of selected events", 1000, 0.0, 1000.0);
    hDedxP_nhitsFit25 = new TH2D("DedxP_nhitsFit25", "dEdx for selected particles with nhitsfit>25(dca<3cm)", nbins * 4, -5, 5, nbins * 6, 0, 6e-5);

    // TPC PID
    hZTriton_vs_p_nhitsFit25 = new TH2D("hZTriton_vs_p_nhitsFit25", "z vs.p dis w dca<3 cm cut for tracks with nhitsFit>=25", nbins * 5, -10.0, 10.0, nbins * 2, -1.0, 1.0);
    hDcaTriton_vs_p_nhitsFit25 = new TH2D("hDcaTriton_vs_p_nhitsFit25", "Dca vs p for TritonTracks(|ZTriton|<0.3) && nhitsFit>25", nbins * 5, -10, 10, nbins * 3, 0, 3.0);
    // TOF QA
    hTofMatchFlag = new TH1D("hTofMatchFlag", "TOF match flag", 5, -1, 4);
    hTofYLocal = new TH1D("hTofYLocal", "TOF ylocal", 300, -3, 3);
    hTofPathLength_vs_tof = new TH2D("hTofPathLength_vs_tof", "tof pathlength vs tof for TritonTracks(|ZTriton|<0.3) && nhitsFit>25", nbins * 7, 0, 70, 2000, 200, 400);
    hInverseBetavsP = new TH2D("hInverseBetavsP", "1/beta vs rigidity*charge with nhitsfit>=25 with gDca<3", 500, -5, 5, 500, 0, 5);
    MSquare_ZdisTritonPos = new TH2D("MSquare_ZdisTritonPos", "msquare vs ZdisTriton(charge>0) with nhitsfit>=25 && gDca<3", nbins * 5, -5.0, 5.0, 600, -1, 14);
    MSquare_ZdisTritonNeg = new TH2D("MSquare_ZdisTritonNeg", "msquare vs ZdisTriton(charge<0) with nhitsfit>=25 && gDca<3", nbins * 5, -5.0, 5.0, 600, -1, 14);
    // TOF+TPC Triton PID
    hZTriton_vs_p_nhitsFit25_TofMatch = new TH2D("hZTriton_vs_p_nhitsFit25_TofMatch", "z vs.p dis w dca<3 cm cut for tracks with nhitsFit>=25 after basic TOFCuts", nbins * 5, -10.0, 10.0, nbins * 2, -1.0, 1.0);
    hDcaTriton_vs_p_nhitsFit25_TofMatch = new TH2D("hDcaTriton_vs_p_nhitsFit25_TofMatch", "dca vs.p dis w dca<3 cm cut for Tritontracks(|Z|<0.3) with nhitsFit>=25 after TOFCuts and msquare>6", nbins * 5, -10.0, 10.0, nbins * 3, 0, 3.0);

    // pT histograms
    hTritonPt = new TH1D("TritonPt", "Triton pT distribution with msquare>6 &|ZdisTriton|<0.3 & nhitsFit>25", Tritonptnbins, Tritonpt);
    hantiTritonPt = new TH1D("antiTritonPt", "antiTriton pT distribution with msquare>6 &|ZdisTriton|<0.3 & nhitsFit>25", Tritonptnbins, Tritonpt);
    hTritonPtSpectra = new TH1D("TritonPtSpectra", "Triton pT spectra(adding 1/2PIpT weight) with msquare>6 &|ZdisTriton|<0.3 & nhitsFit>=25", Tritonptnbins, Tritonpt);
    hantiTritonPtSpectra = new TH1D("antiTritonPtSpectra", "antiTriton pT spectra(adding 1/2PIpT weight) with msquare>6  &|ZdisTriton|<0.3 & nhitsFit>=25", Tritonptnbins, Tritonpt);
    hTritonPtSpectra->Sumw2();
    hantiTritonPtSpectra->Sumw2();

    return;
}

void StV0Maker::initTree() {
    // initialize the TTree for StV0Dst
    mV0Tree = new TTree("TritonPicoDst", "TritonPicoDst from StV0Maker");

    mV0Tree->SetDirectory(v0tree_output);

    mV0Tree->Branch("nrefmult", &mV0Dst.nrefmult, "nrefmult/I");
    mV0Tree->Branch("primvertexX", &mV0Dst.primvertexX, "primvertexX/F");
    mV0Tree->Branch("primvertexY", &mV0Dst.primvertexY, "primvertexY/F");
    mV0Tree->Branch("primvertexZ", &mV0Dst.primvertexZ, "primvertexZ/F");
    mV0Tree->Branch("magn", &mV0Dst.magn, "magn/F");
    mV0Tree->Branch("trigger", &mV0Dst.trigger, "trigger/I");
    mV0Tree->Branch("runnumber", &mV0Dst.runnumber, "runnumber/I");
    mV0Tree->Branch("eventnumber", &mV0Dst.eventnumber, "eventnumber/I");
    mV0Tree->Branch("ndau1", &mV0Dst.ndau1, "ndau1/I");

    mV0Tree->Branch("dau1id", mV0Dst.dau1id, "dau1id[ndau1]/I");
    mV0Tree->Branch("dau1charge", mV0Dst.dau1charge, "dau1charge[ndau1]/I");
    mV0Tree->Branch("dau1dca", mV0Dst.dau1dca, "dau1dca[ndau1]/F");
    mV0Tree->Branch("dau1dcaGlobal", mV0Dst.dau1dcaGlobal, "dau1dcaGlobal[ndau1]/F");
    mV0Tree->Branch("dau1nhitsfit", mV0Dst.dau1nhitsfit, "dau1nhitsfit[ndau1]/I");
    mV0Tree->Branch("dau1nhitsdedx", mV0Dst.dau1nhitsdedx, "dau1nhitsdedx[ndau1]/I");
    mV0Tree->Branch("dau1eta", mV0Dst.dau1eta, "dau1eta[ndau1]/F");
    mV0Tree->Branch("dau1y", mV0Dst.dau1y, "dau1y[ndau1]/F");
    mV0Tree->Branch("dau1dedx", mV0Dst.dau1dedx, "dau1dedx[ndau1]/F");
    mV0Tree->Branch("dau1itofmatch", mV0Dst.dau1itofmatch, "dau1itofmatch[ndau1]/I");
    mV0Tree->Branch("dau1beta", mV0Dst.dau1beta, "dau1beta[ndau1]/F");
    mV0Tree->Branch("dau1tof", mV0Dst.dau1tof, "dau1tof[ndau1]/F");
    mV0Tree->Branch("dau1tofpathlength", mV0Dst.dau1tofpathlength, "dau1tofpathlength[ndau1]/F");
    mV0Tree->Branch("dau1tofylocal", mV0Dst.dau1tofylocal, "dau1tofylocal[ndau1]/F");
    mV0Tree->Branch("dau1msquare", mV0Dst.dau1msquare, "dau1msquare[ndau1]/F");
    mV0Tree->Branch("dau1Z", mV0Dst.dau1Z, "dau1Z[ndau1]/F");
    mV0Tree->Branch("dau1px", mV0Dst.dau1px, "dau1px[ndau1]/F");
    mV0Tree->Branch("dau1py", mV0Dst.dau1py, "dau1py[ndau1]/F");
    mV0Tree->Branch("dau1pz", mV0Dst.dau1pz, "dau1pz[ndau1]/F");
    return;
}

Int_t StV0Maker::Init() {
    // setup the constants according to mV0Type
    initConst();

    // initialize parameters (cuts)
    initParam();

    // Create Histogram output file
    if (mHistogramOutputFileName == "") {
        // CAUTION: ALWAYS USE { } HERE!!! LOG_XXX is a if()xxx macro!!!
        LOG_ERROR << "StV0Maker: Please specify the histrogram output file" << endm;
        exit(-1);
    } else {
        histogram_output = new TFile(mHistogramOutputFileName, "recreate");
    }
    // Book histograms
    initHisto();

    // Create V0 Tree output file
    if (mV0TreeOutputFileName == "") {
        LOG_WARN << "StV0Maker: The V0 tree output file is not specified! output is smeared!" << endm;
    } else {
        v0tree_output = new TFile(mV0TreeOutputFileName, "recreate");
        initTree();
    }

    return kStOK;
}

Int_t StV0Maker::Make() {  // Do each event

    if (GetDebug())
        LOG_QA << "in StV0Maker::Make" << endm;
    // Do some cleaning here, used for StXiMaker or other subsequent makers

    mPassEventCut = false;

    mV0Dst.ndau1 = 0;

    // Get 'event' data
    StMuEvent* muEvent = mMuDstMaker->muDst()->event();
    int runnumber = muEvent->runId();
    int eventnumber = muEvent->eventId();
    int runindex = index_for_runnumber(runnumber);

    for (int i = 0; i < 328; i++) {
        if (runnumber == bad_run_list_7GeV[i]) {
            cout << "bad runnumber:" << runnumber << endl;
            return kStOK;
        }
    }
    /*
    //-----------------------------list filter------------------------
      int refrunnumber=0;
      int refeventnumber=0;

      int iflag= -1;

      He3MuDstEventIdList.open(mHe3EventIdListName);
      He3MuDstEventIdList.seekg(0,ios::beg);

      cout<<mHe3EventIdListName<<endl;
      for(;He3MuDstEventIdList.good();)
      {
        He3MuDstEventIdList>>refrunnumber>>refeventnumber;
    //    cout<<"refrunnumber="<<refrunnumber<<endl;
    //    cout<<"refeventnumber="<<refeventnumber<<endl;
        iflag=-1;

        if(refrunnumber!=runnumber || refeventnumber!=eventnumber)
        {
          iflag=-1;
          continue;
        }
        if(refrunnumber==runnumber || refeventnumber==eventnumber)
        {
          iflag=1;
          cout<<"Matched! refrunnumber="<<refrunnumber<<"  refeventnumber="<<refeventnumber<<endl;
          break;
        }
      }
      He3MuDstEventIdList.close();

      if(iflag == -1)
      {
         cout<<"No Match"<<endl;
         return kStOK;
      }

    //-----------------------------list filter ^------------------------
    */

    //  cout<<"vpdVz =  "<<muEvent->vpdVz()<<endl;
    // Cut on the number of vertices in the event.  On old tapes, no-vertex gets reported as VtxPosition=(0,0,0).
    // Skip events that do not have a primary vertex. the small value '1e-5' is ok for hard coding.
    if (fabs(muEvent->primaryVertexPosition().x()) < 1e-5 && fabs(muEvent->primaryVertexPosition().y()) < 1e-5 && fabs(muEvent->primaryVertexPosition().z()) < 1e-5)
        return kStOK;
    // if(GetDebug()) LOG_QA<<"in StV0Maker::Make : has pv"<<endm;

    // further selection on events. find qualified events!!
    // triggerid, skip events that do not comply with the required trigger id.
    if (!muEvent)
        return kStOK;

    // cut on Vr (essential at low energies)
    if (sqrt(muEvent->primaryVertexPosition().x() * muEvent->primaryVertexPosition().x() + muEvent->primaryVertexPosition().y() * muEvent->primaryVertexPosition().y()) > 2)
        return kStOK;

    // select mb trigger for run10 auau 7GeV
    if ((!muEvent->triggerIdCollection().nominal().isTrigger(290001)) && (!muEvent->triggerIdCollection().nominal().isTrigger(290004)))
        return kStOK;
    mV0Dst.trigger = 1;  // minbias
    hTriggerType->Fill(mV0Dst.trigger);

    // select mb trigger for run10 auau 200GeV
    /*
      if ( (!muEvent->triggerIdCollection().nominal().isTrigger(260001)) && (!muEvent->triggerIdCollection().nominal().isTrigger(260011)) &&
      (!muEvent->triggerIdCollection().nominal().isTrigger(260021)) &&(!muEvent->triggerIdCollection().nominal().isTrigger(260031))) return kStOK;
    */
    /*
       //select mb+central+NPE(HT) trigger for run10 auau 200GeV
    //  cout<<"before trigger selection"<<endl;
      if ( (!muEvent->triggerIdCollection().nominal().isTrigger(260001)) && (!muEvent->triggerIdCollection().nominal().isTrigger(260011)) &&
    (!muEvent->triggerIdCollection().nominal().isTrigger(260021)) &&(!muEvent->triggerIdCollection().nominal().isTrigger(260031)) &&
    (!muEvent->triggerIdCollection().nominal().isTrigger(260101)) && (!muEvent->triggerIdCollection().nominal().isTrigger(260103)) &&
    (!muEvent->triggerIdCollection().nominal().isTrigger(260113)) &&(!muEvent->triggerIdCollection().nominal().isTrigger(260123)) )
    */
    /*
        (!muEvent->triggerIdCollection().nominal().isTrigger(260502)) &&
        (!muEvent->triggerIdCollection().nominal().isTrigger(260512)) &&
        (!muEvent->triggerIdCollection().nominal().isTrigger(260522)) &&
        (!muEvent->triggerIdCollection().nominal().isTrigger(260503)) &&
        (!muEvent->triggerIdCollection().nominal().isTrigger(260513)) &&
        (!muEvent->triggerIdCollection().nominal().isTrigger(260523)) &&
        (!muEvent->triggerIdCollection().nominal().isTrigger(260504)) &&
        (!muEvent->triggerIdCollection().nominal().isTrigger(260514)) &&
        (!muEvent->triggerIdCollection().nominal().isTrigger(260524)) &&
    */
    /*
      return kStOK;
    //  cout<<"after trigger selection"<<endl;


      if( ( (muEvent->triggerIdCollection().nominal().isTrigger(260001)) || (muEvent->triggerIdCollection().nominal().isTrigger(260011)) || (
    muEvent->triggerIdCollection().nominal().isTrigger(260021))||(muEvent->triggerIdCollection().nominal().isTrigger(260031)) ) &&
          ( (muEvent->triggerIdCollection().nominal().isTrigger(260101)) || (muEvent->triggerIdCollection().nominal().isTrigger(260103)) || (
    muEvent->triggerIdCollection().nominal().isTrigger(260113))||(muEvent->triggerIdCollection().nominal().isTrigger(260123)) ) )
      {
       mV0Dst.trigger=3;//triggered by both minbias and central
       hTriggerType->Fill(mV0Dst.trigger);
      }

      else if( (muEvent->triggerIdCollection().nominal().isTrigger(260001)) || (muEvent->triggerIdCollection().nominal().isTrigger(260011)) || (
    muEvent->triggerIdCollection().nominal().isTrigger(260021))||(muEvent->triggerIdCollection().nominal().isTrigger(260031)) )
      {
       mV0Dst.trigger=1;//minbias
       hTriggerType->Fill(mV0Dst.trigger);
      }

      else if( (muEvent->triggerIdCollection().nominal().isTrigger(260101)) || (muEvent->triggerIdCollection().nominal().isTrigger(260103)) || (
    muEvent->triggerIdCollection().nominal().isTrigger(260113))||(muEvent->triggerIdCollection().nominal().isTrigger(260123)) )
      {
       mV0Dst.trigger=2;//central
       hTriggerType->Fill(mV0Dst.trigger);
      }

    */
    /*
      //select mb trigger for run10 auau 11GeV

         if ( (!muEvent->triggerIdCollection().nominal().isTrigger(310004)) &&
         (!muEvent->triggerIdCollection().nominal().isTrigger(310014)) )
         return kStOK;

         mV0Dst.trigger=1;//minbias
         hTriggerType->Fill(mV0Dst.trigger);
    */
    // select mb trigger included mb-zdc, mb-vpd,mb-vpd30cm for run7 auau200 GeV
    /*
      if ( (!muEvent->triggerIdCollection().nominal().isTrigger(200001)) &&
           (!muEvent->triggerIdCollection().nominal().isTrigger(200003)) &&
         (!muEvent->triggerIdCollection().nominal().isTrigger(200013)) &&
         (!muEvent->triggerIdCollection().nominal().isTrigger(200020)) &&
         (!muEvent->triggerIdCollection().nominal().isTrigger(200000)) &&
         (!muEvent->triggerIdCollection().nominal().isTrigger(200002)) &&
         (!muEvent->triggerIdCollection().nominal().isTrigger(200012)) ){
      //cout<<"Bad Trigger id, Event Past."<<endl;
           return kStOK ;
        }
    */
    // AuAu07 high tower trigger
    // if ( (!muEvent->triggerIdCollection().nominal().isTrigger(200211)) &&
    //     (!muEvent->triggerIdCollection().nominal().isTrigger(200212)) &&
    //     (!muEvent->triggerIdCollection().nominal().isTrigger(200220)) &&
    //     (!muEvent->triggerIdCollection().nominal().isTrigger(200221)) &&
    //     (!muEvent->triggerIdCollection().nominal().isTrigger(200222)) &&
    //     (!muEvent->triggerIdCollection().nominal().isTrigger(200213)) &&
    //     (!muEvent->triggerIdCollection().nominal().isTrigger(200214)) ){
    // cout<<"Bad Trigger id, Event Past."<<endl;
    //       return kStOK ;
    //    }

    // select mb + central trigger for Run-4
    /*
      if ( (!muEvent->triggerIdCollection().nominal().isTrigger(15007)) &&
          (!muEvent->triggerIdCollection().nominal().isTrigger(15003)) &&
          (!muEvent->triggerIdCollection().nominal().isTrigger(15105)) ){
        //cout<<"Bad Trigger id, Event Past."<<endl;
        return kStOK ;
      }
    */
    /*
     //Run-4 minbias sample 1 and 2
      if(!muEvent->triggerIdCollection().nominal().isTrigger(15007)) {
        //cout<<"Bad Trigger id, Event Past."<<endl;
        return kStOK ;
      }
    */
    /*
      //select mb trigger for Run10 39GeV
      if( !muEvent->triggerIdCollection().nominal().isTrigger(280001) )
        return kStOK;

        mV0Dst.trigger=1;//minbias
        hTriggerType->Fill(mV0Dst.trigger);
     */

    // Fill some QA plots
    hVertexZ->Fill(muEvent->primaryVertexPosition().z());  // Make histogram of the vertex Z distribution

    hNRefMult->Fill(muEvent->refMult());

    // cut on vertexZ, not applied here to enlarge the statistics, can be narrowed in analysis code
    if (fabs(muEvent->primaryVertexPosition().z()) > cutAbsVertexZLeEq)
        return kStOK;

    //-------------added from Hiroshi's refmult correction-----------
    Int_t zdcRate = muEvent->runInfo().zdcCoincidenceRate();
    Int_t refmult = muEvent->refMult();

    StRefMultCorr refmultCorrUtil;

    refmultCorrUtil.init(runnumber);
    refmultCorrUtil.initEvent(refmult, muEvent->primaryVertexPosition().z(), zdcRate);

    Int_t cent9 = refmultCorrUtil.getCentralityBin9();
    Double_t refmultCor = refmultCorrUtil.getRefMultCorr();

    mCentrality = cent9 + 1;
    // cout<<"cent9   "<<cent9<<"    "<<refmult<<"   "<<vz<<"   "<<zdcRate<<endl;
    // mCentrality = getCentrality(muEvent);
    if (mCentrality == 0)
        return kStOK;
    mCentrality = mCentrality - 1;

    mPassEventCut = true;

    hRefmult_comp->Fill(refmultCor, refmult);
    //---------------------

    // cut on centrality or reference multiplicity.
    //  if ( muEvent->refMult() <= cutRefMult ) return kStOK; //cut off the background events in 11.5

    mV0Dst.primvertexX = muEvent->primaryVertexPosition().x();
    mV0Dst.primvertexY = muEvent->primaryVertexPosition().y();
    mV0Dst.primvertexZ = muEvent->primaryVertexPosition().z();

    mV0Dst.nrefmult = muEvent->refMult();

    /*
      hvpdVz_vz->Fill(muEvent->primaryVertexPosition().z(),mMuDstMaker->muDst()->btofHeader()->vpdVz());
      hvzdiff->Fill(mMuDstMaker->muDst()->btofHeader()->vpdVz()-muEvent->primaryVertexPosition().z());

      //cut on |vzVPD-Vz|
      if(fabs(muEvent->primaryVertexPosition().z()-mMuDstMaker->muDst()->btofHeader()->vpdVz())>4) return kStOK;
    */

    mPassEventCut = true;
    // Do 'event' analysis based on event data

    //  hvpdVz_vz_passEvent->Fill(muEvent->primaryVertexPosition().z(),mMuDstMaker->muDst()->btofHeader()->vpdVz());
    //  cout<<"Event Num is ::"<<muEvent->eventNumber()<<endl;
    cout << "Event Multiplicity is ::" << muEvent->refMult() << endl;

    mV0Dst.runnumber = runnumber;
    mV0Dst.eventnumber = eventnumber;

    // Record some information...
    hSelectVertexZ->Fill(muEvent->primaryVertexPosition().z());
    hSelectNRefMult->Fill(muEvent->refMult());  // this is an ESSENTIAL histogram to record the total number of events for certain centrality. always
                                                // make sure it is filled AFTER event selection!

    Double_t magn = muEvent->runInfo().magneticField();
    // Double_t magn = muEvent->magneticField();	//checked! the same as above
    mV0Dst.magn = magn;

    // Get 'track' data, make cuts on tracks, do physics analysis, histogram results.
    //  TObjArray* tracks = mMuDstMaker->muDst()->globalTracks() ;    // Create a TObject array containing the global tracks
    TObjArray* tracks = mMuDstMaker->muDst()->primaryTracks();  // Create a TObject array containing the primary tracks
    TObjArrayIter GetTracks(tracks);                            // Create an iterator to step through the tracks
    //  float nsigma_He3[500]={0.0,};

    StMuTrack* track;  // Pointer to a track
    //  StMuDst* mu = mMuDstMaker->muDst();

    int ndau1 = 0;
    while ((track = (StMuTrack*)GetTracks.Next()))  // Main loop for Iterating over tracks
    {
        // ptrTrack[track->id()] = track;

        // hPtRaw -> Fill( track->pt() ) ; //at dca to PV, for a global track, this value is useless. anyway, the pt value is supposed to be the same
        // anywhere.

        short flag = track->flag();
        // unsigned short nHits = track->nHits();	//total # of hits in all available detectors
        unsigned short nHitsDedx = track->nHitsDedx();  // added dEdx Hits to restrict the background!
        unsigned short nHitsFit = track->nHitsFit(kTpcId);
        short charge = track->charge();
        // StThreeVectorF p = track->p();	  //at dca to PV
        // StThreeVectorF origin = track->firstPoint();  //? NOT SURE whether firstPoint from detectorinfo is the same as helix.orgin()!!!
        double nsigmapion = track->nSigmaPion();
        //	  double nsigmaproton = track->nSigmaProton();
        // double nsigmakaon = track->nSigmaKaon();
        // double nsigmaelectron = track->nSigmaElectron();
        double dedx = track->dEdx();

        StPhysicalHelixD helix = track->helix();              // inner helix. good for dca to PV.
        StThreeVectorD p = helix.momentum(magn * kilogauss);  // momentum at origin
        //!!!!!!!!!!!This p is not accurate momentum, it is rigidity = momentum/nuclear_charge

        // StThreeVectorD origin = helix.origin();  //origin of helix
        double pt = p.perp();

        //+------------------------------------------------------------------------------------------+
        // some checks
        // hNHitsFit -> Fill( nHitsFit ) ;
        // hNHits -> Fill( nHits ) ;
        // hPtDiff -> Fill( track->pt() - p.perp() ) ;
        // hOrDiff -> Fill( (track->firstPoint() - origin).mag() ) ;
        // hPDiff -> Fill( fabs(track->p().mag() - p.mag()) ) ;
        // comments: there are difference between the values above. But they seem to be acceptably small!
        //+--------------------------------------------------------------------------------------------+

        // if(track->vertexIndex()!=StMuDst::currentVertexIndex())continue;
        // if you want to use dca.mag(), turn this on. if it is not turned on, that function crashes.

        // cut on tracks
        if (nHitsFit <= cutNHitsGr)
            continue;
        if (nHitsDedx < cutNHitsDedxGr)
            continue;
        if (flag <= 0)
            continue;  // or <=0 ?
        // if(track->bad() )continue;
        if (abs(charge) != 1)
            continue;  // Let's comment out this line for checking
        if (fabs(track->eta()) > 1.0)
            continue;
        if (Float_t(nHitsFit) / Float_t(track->nHitsPoss()) < 0.52)
            continue;

        // hPt -> Fill( track->pt() ) ; //at dca to PV, for a global track, this value is useless. anyway, the pt value is supposed to be the same
        // anywhere. hPhi -> Fill( track->phi() ) ;		  //at dca to PV if(pt<0.5)hPhiLowPt->Fill(track->phi()); else
        // hPhiHighPt->Fill(track->phi());
        Double_t dedxZ_Triton = TMath::Log(dedx / dedx_Triton_th[index_for_p(p.mag())]);  // triton charge = 2, build in mom is p/q, should be corrected here!
        //    Double_t dedxZ_He4 = TMath::Log(dedx/dedx_He4_th[index_for_p(2*p.mag())]); //triton charge = 2, build in mom is p/q, should be corrected
        //    here!

        double pathlength = helix.pathLength(muEvent->primaryVertexPosition(),
                                             false);  // do scan periods. NOTE: the default is false. this is not necessary for tracks with pt>0.15GeV/c
        StThreeVectorF dca = helix.at(pathlength) - muEvent->primaryVertexPosition();

        // cut on dca.mag() to check whether the background trackes are due to large dca tracks
        if (track->dcaGlobal().mag() > 3)
            continue;

        if (nHitsFit >= 25 && track->dcaGlobal().mag() < 3)
            hDedxP_nhitsFit25->Fill(p.mag() * charge, dedx);

        if (pt < cutPtGrEq)
            continue;  // should be larger. like 0.15 or 0.2

        if (track->dcaGlobal().mag() < 3 && nHitsFit >= 25) {
            hZTriton_vs_p_nhitsFit25->Fill(p.mag() * charge, dedxZ_Triton);
        }

        //-------------TOF track qualities start-------------//
        // StMuBTofPidTraits tofPid = (StMuBTofPidTraits)pMuGlobalTrack->btofPidTraits();//glob TOF info
        StMuBTofPidTraits tofPid = (StMuBTofPidTraits)track->btofPidTraits();
        float tof = -999.;
        float beta = -999.;
        float tofpathlength = -999.;
        float tofylocal = -999.;

        int tofmatchflag = -999;
        float c = 29.9792458;  // [cm/ns]

        tofmatchflag = tofPid.matchFlag();
        tofpathlength = tofPid.pathLength();
        tof = tofPid.timeOfFlight();
        beta = tofpathlength / (tof * c);
        tofylocal = tofPid.yLocal();

        hTofMatchFlag->Fill(tofmatchflag);

        if (tofmatchflag > 0 && beta > 1e-5) {
            float mSquare = (p.mag() * p.mag()) * (1. / (beta * beta) - 1.);
            if (track->dcaGlobal().mag() < 3 && track->charge() > 0 && nHitsFit >= 25) {
                hTofYLocal->Fill(tofylocal);
                MSquare_ZdisTritonPos->Fill(dedxZ_Triton, mSquare);
                hInverseBetavsP->Fill(charge * p.mag(), 1 / beta);
                hZTriton_vs_p_nhitsFit25_TofMatch->Fill(p.mag() * charge, dedxZ_Triton);
            } else if (track->dcaGlobal().mag() < 3 && track->charge() < 0 && nHitsFit >= 25) {
                hTofYLocal->Fill(tofylocal);
                MSquare_ZdisTritonNeg->Fill(dedxZ_Triton, mSquare);
                hInverseBetavsP->Fill(charge * p.mag(), 1 / beta);
                hZTriton_vs_p_nhitsFit25_TofMatch->Fill(p.mag() * charge, dedxZ_Triton);
            }
        }

        // Triton identification!!!!!!!
        if (fabs(dedxZ_Triton) < 0.3 && track->dcaGlobal().mag() < 3 && nHitsFit >= 15)  // Triton
        {
            if (nHitsFit >= 25) {
                hDcaTriton_vs_p_nhitsFit25->Fill(p.mag() * charge, track->dcaGlobal().mag());
            }
            if (charge > 0) {
                hTritonPt->Fill(pt);
                hTritonPtSpectra->Fill(pt, 1. / (TMath::TwoPi() * pt));
            }
            if (charge < 0) {
                hantiTritonPt->Fill(pt);
                hantiTritonPtSpectra->Fill(pt, 1. / (TMath::TwoPi() * pt));
            }

            mV0Dst.dau1id[ndau1] = track->id();
            mV0Dst.dau1charge[ndau1] = track->charge();
            mV0Dst.dau1dca[ndau1] = dca.mag();
            mV0Dst.dau1dcaGlobal[ndau1] = track->dcaGlobal().mag();
            mV0Dst.dau1nhitsfit[ndau1] = track->nHitsFit();
            mV0Dst.dau1nhitsdedx[ndau1] = track->nHitsDedx();
            mV0Dst.dau1dedx[ndau1] = track->dEdx();
            mV0Dst.dau1eta[ndau1] = p.pseudoRapidity();
            mV0Dst.dau1y[ndau1] = log((sqrt(mMass1 * mMass1 + p.mag2()) + p.z()) / sqrt(mMass1 * mMass1 + p.perp2()));
            mV0Dst.dau1Z[ndau1] = dedxZ_Triton;
            mV0Dst.dau1px[ndau1] = p.x();
            mV0Dst.dau1py[ndau1] = p.y();
            mV0Dst.dau1pz[ndau1] = p.z();

            mV0Dst.dau1itofmatch[ndau1] = tofmatchflag;

            //      cout<<"one Triton found:Z_Triton="<<dedxZ_Triton<<"\n";
            mV0Dst.dau1msquare[ndau1] = -99.;
            mV0Dst.dau1tofylocal[ndau1] = -99.;
            mV0Dst.dau1beta[ndau1] = -99.;
            mV0Dst.dau1tof[ndau1] = -99.;
            mV0Dst.dau1tofpathlength[ndau1] = -99.;

            if (tofmatchflag > 0) {
                mV0Dst.dau1beta[ndau1] = beta;
                mV0Dst.dau1tof[ndau1] = tof;

                mV0Dst.dau1tofpathlength[ndau1] = tofpathlength;

                //      float c = 29.9792458; // [cm/ns]
                if (beta > 1e-5) {
                    //      cout<<"beta="<<beta<<endl;
                    float mSquare = (p.mag() * p.mag()) * (1. / (beta * beta) - 1.);

                    if (mSquare > 6 && nHitsFit >= 25) {
                        hTofPathLength_vs_tof->Fill(tof, tofpathlength);
                        hDcaTriton_vs_p_nhitsFit25_TofMatch->Fill(p.mag() * charge, track->dcaGlobal().mag());
                    }
                    mV0Dst.dau1msquare[ndau1] = mSquare;
                    mV0Dst.dau1tofylocal[ndau1] = tofylocal;

                }  // if(beta>0)
            }      // tofmatchflag loop ends

            ndau1++;

        }  // TPC Triton cuts loop

    }  // track loop ends

    mV0Dst.ndau1 = ndau1;

    if (ndau1 > 0 && mV0Tree)
        mV0Tree->Fill();  // Fill all variables defined in V0Tree?

    mEventsProcessed++;
    // LOG_QA << mDauVec1.size() <<" "<< mDauVec2.size() <<" "<< mV0Vec.size()<<endm;

    return kStOK;
}

// Double_t StV0Maker::dEdxB(double xp,double ymass){//x-momentum; par[0]--mass
//  Bichsel *m_Bichsel = new Bichsel();
//  return 1e-6*m_Bichsel->GetI70M(TMath::Log(xp/ymass));
//}

int StV0Maker::index_for_p(float tp) {
    int i = int((tp - 0.1) / 0.001 + 0.5);
    if (i < 0)
        return 0;
    else if (i > 11900)
        return 11900;
    else
        return i;
    return 0;
}

int StV0Maker::index_for_runnumber(int n) {
    int i = 0;
    while (runnum_7GeV[i] < n) {
        i++;
    }
    return i;
}

Int_t StV0Maker::Finish() {  // Do once at the end the analysis

    // Write histograms to disk, output miscellaneous other information
    if (histogram_output != NULL)
        histogram_output->Write();  // Write all histograms to disk
    if (v0tree_output != NULL) {
        v0tree_output->Write();  // Write all histograms to disk
        cout << "v0tree written" << endl;
    }
    cout << "Total Events Processed in StV0Maker " << mEventsProcessed << endl;

    return kStOk;
}
