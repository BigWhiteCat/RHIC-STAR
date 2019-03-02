#ifndef StV0Dst_def
#define StV0Dst_def

#define MAX_NUM_V0 5000
#define MAX_NUM_TOF 1000
struct StV0Dst {
    int nrefmult;
    float primvertexX;
    float primvertexY;
    float primvertexZ;
    int trigger;
    int runnumber;
    int eventnumber;
    float magn;
    int nv0;
    int ndau1;
    int ndau2;

    // StV0Data v0[1000];
    int v0charge[MAX_NUM_V0];
    float v0mass[MAX_NUM_V0];
    float v0pt[MAX_NUM_V0];
    float v0rapidity[MAX_NUM_V0];
    float v0eta[MAX_NUM_V0];
    float v0x[MAX_NUM_V0];
    float v0y[MAX_NUM_V0];
    float v0z[MAX_NUM_V0];
    float v0px[MAX_NUM_V0];
    float v0py[MAX_NUM_V0];
    float v0pz[MAX_NUM_V0];
    float v0declen[MAX_NUM_V0];
    float v0dca[MAX_NUM_V0];
    float dca1to2[MAX_NUM_V0];
    float v0rdotp[MAX_NUM_V0];
    float v0theta[MAX_NUM_V0];
    float v0sinth[MAX_NUM_V0];

    int dau1id[MAX_NUM_V0];
    int dau1charge[MAX_NUM_V0];
    float dau1dca[MAX_NUM_V0];
    float dau1dcaGlobal[MAX_NUM_V0];
    int dau1nhits[MAX_NUM_V0];
    int dau1nhitsfit[MAX_NUM_V0];
    int dau1nhitsdedx[MAX_NUM_V0];
    float dau1eta[MAX_NUM_V0];
    float dau1y[MAX_NUM_V0];
    float dau1dedx[MAX_NUM_V0];
    float dau1Z[MAX_NUM_V0];
    float dau1tofylocal[MAX_NUM_V0];
    float dau1beta[MAX_NUM_V0];
    float dau1tof[MAX_NUM_V0];
    float dau1tofpathlength[MAX_NUM_V0];
    int dau1itofmatch[MAX_NUM_V0];
    float dau1msquare[MAX_NUM_V0];
    float dau1pt[MAX_NUM_V0];
    float dau1px[MAX_NUM_V0];
    float dau1py[MAX_NUM_V0];
    float dau1pz[MAX_NUM_V0];
    //   float dau1ptdiff[MAX_NUM_V0];
    // int dau1tpc[MAX_NUM_V0];
    // int dau1ssd[MAX_NUM_V0];
    // int dau1svt[MAX_NUM_V0];

    int dau2id[MAX_NUM_V0];
    int dau2charge[MAX_NUM_V0];
    float dau2dca[MAX_NUM_V0];
    int dau2nhits[MAX_NUM_V0];
    int dau2nhitsfit[MAX_NUM_V0];
    int dau2nhitsdedx[MAX_NUM_V0];
    float dau2eta[MAX_NUM_V0];
    float dau2dedx[MAX_NUM_V0];
    float dau2nsigma[MAX_NUM_V0];
    float dau2pt[MAX_NUM_V0];
    float dau2px[MAX_NUM_V0];
    float dau2py[MAX_NUM_V0];
    float dau2pz[MAX_NUM_V0];
    // int dau2tpc[MAX_NUM_V0];
    // int dau2ssd[MAX_NUM_V0];
    // int dau2svt[MAX_NUM_V0];
    /*
       int   He3id[MAX_NUM_TOF];
       float nsigmaHe3_TOF[MAX_NUM_TOF];
       float msquareHe3_TOF[MAX_NUM_TOF];
       float He3dedx[MAX_NUM_TOF];
       float He3beta[MAX_NUM_TOF];
       float He3pt[MAX_NUM_TOF];
       float He3px[MAX_NUM_TOF];
       float He3py[MAX_NUM_TOF];
       float He3pz[MAX_NUM_TOF];
       float He3dca[MAX_NUM_TOF];
    */
    /*
       int   He4id[MAX_NUM_TOF];
       float nsigmaHe4_TOF[MAX_NUM_TOF];
       float msquareHe4_TOF[MAX_NUM_TOF];
       float He4dedx[MAX_NUM_TOF];
       float He4beta[MAX_NUM_TOF];
       float He4pt[MAX_NUM_TOF];
       float He4px[MAX_NUM_TOF];
       float He4py[MAX_NUM_TOF];
       float He4pz[MAX_NUM_TOF];
       float He4dca[MAX_NUM_TOF];
    */
    /*
       int   Deuteronid[MAX_NUM_TOF];
       float nsigmaDeuteron_TOF[MAX_NUM_TOF];
       float msquareDeuteron_TOF[MAX_NUM_TOF];
       float Deuterondedx[MAX_NUM_TOF];
       float Deuteronbeta[MAX_NUM_TOF];
       float Deuteronpt[MAX_NUM_TOF];
       float Deuteronpx[MAX_NUM_TOF];
       float Deuteronpy[MAX_NUM_TOF];
       float Deuteronpz[MAX_NUM_TOF];
       float Deuterondca[MAX_NUM_TOF];

       int   Tritonid[MAX_NUM_TOF];
       float nsigmaTriton_TOF[MAX_NUM_TOF];
       float msquareTriton_TOF[MAX_NUM_TOF];
       float Tritondedx[MAX_NUM_TOF];
       float Tritonbeta[MAX_NUM_TOF];
       float Tritonpt[MAX_NUM_TOF];
       float Tritonpx[MAX_NUM_TOF];
       float Tritonpy[MAX_NUM_TOF];
       float Tritonpz[MAX_NUM_TOF];
       float Tritondca[MAX_NUM_TOF];
    */
    /*
       int   toftracknumber;
       int   tofnhits[MAX_NUM_TOF];
       int   tofnhitsfit[MAX_NUM_TOF];
       int   tofnhitsdedx[MAX_NUM_TOF];
       float tofeta[MAX_NUM_TOF];
       float tofdedx[MAX_NUM_TOF];
       float tofdca[MAX_NUM_TOF];
       float tofZHe3[MAX_NUM_TOF];
       float tofp[MAX_NUM_TOF];
       float tofpt[MAX_NUM_TOF];
       float tofpx[MAX_NUM_TOF];
       float tofpy[MAX_NUM_TOF];
       float tofpz[MAX_NUM_TOF];

       float tof[MAX_NUM_TOF];
       float tofpathlength[MAX_NUM_TOF];
       float tot[MAX_NUM_TOF];
       float tofbeta[MAX_NUM_TOF];
       float tofmsquare[MAX_NUM_TOF];

       int   toftrayid[MAX_NUM_TOF];
       int   tofmoduleid[MAX_NUM_TOF];
       int   tofcellid[MAX_NUM_TOF];
       float toflocalY[MAX_NUM_TOF];
       float toflocalZ[MAX_NUM_TOF];
    */
};

#endif
