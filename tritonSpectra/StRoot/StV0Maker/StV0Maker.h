#ifndef StV0Maker_def
#define StV0Maker_def

#include "StMaker.h"
#include "TString.h"

#include "StRoot/StRefMultCorr/StRefMultCorr.h"

class StMuDstMaker;
class StMuTrack;
class TFile;
class TTree;
class TH1D;
class TH2D;

#include "StV0Dst.h"
#include "StV0Type.h"
#include "TH2D.h"
#include "TH3F.h"
class StV0Maker : public StMaker {
  private:
    // constants
    //  enum {
    //     kMaxNumberOfTH1D = 10
    //  };

    // Make MuDst pointer available to member functions
    StMuDstMaker* mMuDstMaker;

    // master switch for the analysis, v0 type
    StV0Type mV0Type;

    // switch for rotating the coordinates and momenta (in transverse direction) of one daughter.
    // for background estimation.
    bool mRotate;
    bool mTof;
    bool mSameSignPlus;
    bool mSameSignMinus;
    bool mDcaAlgoLong;

    // section of v0type related constants
    Float_t mMass1;
    Float_t mMass2;
    Float_t mMassV0;
    Int_t mCharge1;
    Int_t mCharge2;

    // section of parameters for v0 analysis
    int BeamEnergy;
    float cutAbsVertexZLeEq;
    int cutTriggerIdEq;
    int mCentrality;
    int cutRefMult;
    int cutNHitsGr;
    int cutNHitsDedxGr;
    float cutPtGrEq;

    float cutAbsNSigma1Le;
    float cutAbsNSigma2Le;
    float cutDca1GrEq;
    float cutDca2GrEq;
    float cutDca1LeEq;
    float cutDca2LeEq;

    float cutRelativeMSquareLeEq;  // Used in TOF PID cut

    float cutDca1to2LeEq;
    float cutV0MassWidthLeEq;
    float cutDauPtArmLeEq;
    float cutAbsDausPtShoulderDiffLeEq;
    float cutDau1DecAngGr;
    float cutDau2DecAngGr;
    float cutV0rdotpGr;
    float cutDcaV0Le;
    float cutV0DecLenGrEq;
    float cutDau1Dau2Ang3DLe;
    float cutDau1Dau2DipAngDiffLe;

    float dedx_He3_th[11901];
    float dedx_He4_th[11901];
    float dedx_Triton_th[11901];
    float dedx_Deuteron_th[11901];
    // Tof related variables:
    //    ifstream He3MuDstEventIdList;

    // histograms (mostly for QA purpose)
    // TH1D*         histogram[kMaxNumberOfTH1D] ;       //  1D Histograms
    // Event-level
    TH1D* hNPrimVertex;
    TH1D* hTriggerType;
    TH1D* hVertexZ;
    TH1D* hSelectVertexZ;
    TH2D* hvpdVz_vz;
    TH2D* hvpdVz_vz_passEvent;
    TH1D* hvzdiff;

    TH1D* hNRefMult;
    TH2D* hRefmult_comp;
    TH1D* hSelectNRefMult;

    // Track-level
    TH1D* hPt;
    TH1D* hEta;
    TH1D* hPhi;
    TH1D* hPhiLowPt;
    TH1D* hPhiHighPt;

    TH2D* hDedxP;
    TH2D* hDedxP_nhitsFit25;
    //

    TH2D* hZTriton_vs_p_nhitsFit25;
    TH2D* hDcaTriton_vs_p_nhitsFit25;

    TH2D* hZTriton_vs_p_nhitsFit25_TofMatch;
    TH2D* hDcaTriton_vs_p_nhitsFit25_TofMatch;

    // TOF relative
    TH1D* hTofPathLength;
    TH1D* hTofPathLength_afterylocalcut;

    TH1D* hTofMatchFlag;
    TH1D* hTofYLocal;
    TH1D* hTofZLocal;

    TH2D* hTofPathLenvsTray;
    TH2D* hInverseBetavsP;

    TH2D* MSquare_ZdisTritonPos;
    TH2D* MSquare_ZdisTritonNeg;
    TH2D* hTofPathLength_vs_tof;
    TH2D* hMSquare_TOF;
    TH2D* hMSquare_TOFPos;
    TH2D* hMSquare_TOFNeg;
    TH1D* hInvMass;
    TH1D* hInvMass_Pos;
    TH1D* hInvMass_Neg;

    // TH1D*		hInvMassSTD;
    TH1D* hdca1;
    TH1D* hdca2;
    TH1D* hdca1to2;

    TH1D* hHe3Pt;
    TH1D* hantiHe3Pt;
    TH1D* hHe3PtSpectra;
    TH1D* hantiHe3PtSpectra;

    TH1D* hTritonPt;
    TH1D* hantiTritonPt;
    TH1D* hTritonPtSpectra;
    TH1D* hantiTritonPtSpectra;

    TH1D* hPionPlusPt;
    TH1D* hPionMinusPt;
    TH1D* hPionPlusPtSpectra;
    TH1D* hPionMinusPtSpectra;

    TH2D* hdca1_runnumber;
    TH2D* hdca1_anti_runnumber;
    TH2D* hdca2_runnumber;
    TH2D* hdca1to2_runnumber;
    TH2D* hdcav0_runnumber;
    TH2D* hv0declen_runnumber;
    // files related
    TString mHistogramOutputFileName;  //  Name of the histogram output file
    TString mV0TreeOutputFileName;     //  Name of the v0 tree output file
    TString mTofTreeOutputFileName;    //  Name of the tof tree output file
    TString mHe3EventIdListName;
    TFile* histogram_output;  //  Histograms outputfile pointer
    TFile* v0tree_output;     //  V0 Tree outputfile pointer
    TFile* toftree_output;    //  V0 Tree outputfile pointer

    TTree* mV0Tree;   // V0 Tree outputfile pointer
    TTree* mTofTree;  // tof Tree outputfile pointer
    StV0Dst mV0Dst;   // V0 event (picoDst), to fill the tree

    // statistic information
    UInt_t mEventsProcessed;  //  Number of Events read and processed
    UInt_t countHe3;
    UInt_t countHe4;
    UInt_t countDeuteron;
    UInt_t countTriton;

    // some diagnosing variables
    Float_t mTestVZ;
    UInt_t mTestNTrack;
    bool mPassEventCut;

    // temporary variables (put here for performance consideration)
    vector<StMuTrack*> mDauVec1;
    vector<StMuTrack*> mDauVec2;
    vector<StMuTrack*> mDauVec1TPC;
    vector<StMuTrack*> mTrackVecTOF;
    vector<double> mDauDcaVec1;
    vector<double> mDauDcaVec2;
    vector<double> mDauDcaVec1TPC;

    // private member functions
    void initParam();    // initialize parameters
    void initConst();    // initialize constants for v0type
    void initHisto();    // book histograms
    void initTree();     // book tree
    void initTofTree();  // book tof tree
                         // enum {
                         //   kMaxTrackID = 5000
                         //};
                         // StMuTrack * ptrTrack[kMaxTrackID]; // map of key to track ptr.

  protected:
    // I do not expect some class inherits this maker!

  public:
    StV0Maker(StMuDstMaker* maker, const char* name);  //  Constructor
    virtual ~StV0Maker();                              //  Destructor

    Int_t Init();    //  Initiliaze the analysis tools ... done once
    Int_t Make();    //  The main analysis that is done on each event
    Int_t Finish();  //  Finish the analysis, close files, and clean up.

    void setHistoFileName(TString name) {
        mHistogramOutputFileName = name;
    }  // set the name of output file for histograms
    void setV0TreeFileName(TString name) {
        mV0TreeOutputFileName = name;
    }  // set the name of output file for StV0Dst
    void setTofTreeFileName(TString name) {
        mTofTreeOutputFileName = name;
    }  // set the name of output file for StV0Dst
    void setHe3EventIdListName(TString EventList) {
        mHe3EventIdListName = EventList;
    }  // set the name of input EventId file for StV0Dst

    void setV0Type(StV0Type v0type) {
        mV0Type = v0type;
    }  // set the v0 type: kLambda,kAntiLambda,kKs
    void setRotate(bool brot) {
        mRotate = brot;
    }  // set rotation option
    void setTofTree(bool kTofTree) {
        mTof = kTofTree;
    }  // set the option for filling the tof info tree
    void setSameSignPlus(bool brot) {
        mSameSignPlus = brot;
    }  // set same sign plus
    void setSameSignMinus(bool brot) {
        mSameSignMinus = brot;
    }  // set same sign minus

    const StV0Dst& getV0Dst() const {
        return mV0Dst;
    }
    bool passEventCut() const {
        return mPassEventCut;
    }

    void SetEventCuts(int BeamEnergy) {
        if (BeamEnergy == 7) {
            cutAbsVertexZLeEq = 70;
            cutRefMult = 4;
        }

        if (BeamEnergy == 11) {
            cutAbsVertexZLeEq = 50;
            cutRefMult = 5;
        }

        if (BeamEnergy == 19) {
            cutAbsVertexZLeEq = 70;
            cutRefMult = 6;
        }

        if (BeamEnergy == 27) {
            cutAbsVertexZLeEq = 50;
            cutRefMult = 6;
        }

        if (BeamEnergy == 39) {
            cutAbsVertexZLeEq = 40;
            cutRefMult = 7;
        }

        if (BeamEnergy == 62) {
            cutAbsVertexZLeEq = 40;
            cutRefMult = 7;
        }

        if (BeamEnergy == 200) {
            cutAbsVertexZLeEq = 30;
            cutRefMult = 10;
        }
    }

    Double_t dEdxB(double, double);

    // int read_in_dedx_th();
    int index_for_p(float);
    int index_for_runnumber(int);
    ClassDef(StV0Maker, 1)  //  Macro for CINT compatability
};

#endif
