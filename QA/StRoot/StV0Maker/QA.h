#ifndef QA_H
#define QA_H

const int MAXMULTI = 5000;

struct QA {
    int referenceMulti;
    double primeryVertexX;
    double primeryVertexY;
    double primeryVertexZ;
    long eventId;
    long runId;

    /*! pion */
    int pionNum = 0;
    int pionId[MAXMULTI];
    double pionDca[MAXMULTI];
    double pionMass[MAXMULTI];
    double pionEta[MAXMULTI];
    double pionRapidity[MAXMULTI];
    int pionNumHitsFit[MAXMULTI];
    int pionNumHitsdEdx[MAXMULTI];
    int pionNumHitsPossible[MAXMULTI];
    double pionNSigma[MAXMULTI];
    double pionPx[MAXMULTI];
    double pionPy[MAXMULTI];
    double pionPz[MAXMULTI];
    double pionPt[MAXMULTI];
    double piondEdx[MAXMULTI];
    double pionZ[MAXMULTI];
    double pionBeta[MAXMULTI];

    /*! proton */
    int protonNum = 0;
    int protonId[MAXMULTI];
    double protonDca[MAXMULTI];
    double protonMass[MAXMULTI];
    double protonEta[MAXMULTI];
    double protonRapidity[MAXMULTI];
    int protonNumHitsFit[MAXMULTI];
    int protonNumHitsdEdx[MAXMULTI];
    int protonNumHitsPossible[MAXMULTI];
    double protonNSigma[MAXMULTI];
    double protonPx[MAXMULTI];
    double protonPy[MAXMULTI];
    double protonPz[MAXMULTI];
    double protonPt[MAXMULTI];
    double protondEdx[MAXMULTI];
    double protonZ[MAXMULTI];
    double protonBeta[MAXMULTI];

    /*! deutron */
    int deutronNum = 0;
    int deutronId[MAXMULTI];
    double deutronDca[MAXMULTI];
    double deutronMass[MAXMULTI];
    double deutronEta[MAXMULTI];
    double deutronRapidity[MAXMULTI];
    int deutronNumHitsFit[MAXMULTI];
    int deutronNumHitsdEdx[MAXMULTI];
    int deutronNumHitsPossible[MAXMULTI];
    double deutronNSigma[MAXMULTI];
    double deutronPx[MAXMULTI];
    double deutronPy[MAXMULTI];
    double deutronPz[MAXMULTI];
    double deutronPt[MAXMULTI];
    double deutrondEdx[MAXMULTI];
    double deutronZ[MAXMULTI];
    double deutronBeta[MAXMULTI];

    /*! triton */
    int tritonNum = 0;
    int tritonId[MAXMULTI];
    double tritonDca[MAXMULTI];
    double tritonMass[MAXMULTI];
    double tritonEta[MAXMULTI];
    double tritonRapidity[MAXMULTI];
    int tritonNumHitsFit[MAXMULTI];
    int tritonNumHitsdEdx[MAXMULTI];
    int tritonNumHitsPossible[MAXMULTI];
    double tritonNSigma[MAXMULTI];
    double tritonPx[MAXMULTI];
    double tritonPy[MAXMULTI];
    double tritonPz[MAXMULTI];
    double tritonPt[MAXMULTI];
    double tritondEdx[MAXMULTI];
    double tritonZ[MAXMULTI];
    double tritonBeta[MAXMULTI];

    /*! helium3 */
    int helium3Num = 0;
    int helium3Id[MAXMULTI];
    double helium3Dca[MAXMULTI];
    double helium3Mass[MAXMULTI];
    double helium3Eta[MAXMULTI];
    double helium3Rapidity[MAXMULTI];
    int helium3NumHitsFit[MAXMULTI];
    int helium3NumHitsdEdx[MAXMULTI];
    int helium3NumHitsPossible[MAXMULTI];
    double helium3NSigma[MAXMULTI];
    double helium3Px[MAXMULTI];
    double helium3Py[MAXMULTI];
    double helium3Pz[MAXMULTI];
    double helium3Pt[MAXMULTI];
    double helium3dEdx[MAXMULTI];
    double helium3Z[MAXMULTI];
    double helium3Beta[MAXMULTI];

    /*! helium4 */
    int helium4Num = 0;
    int helium4Id[MAXMULTI];
    double helium4Dca[MAXMULTI];
    double helium4Mass[MAXMULTI];
    double helium4Eta[MAXMULTI];
    double helium4Rapidity[MAXMULTI];
    int helium4NumHitsFit[MAXMULTI];
    int helium4NumHitsdEdx[MAXMULTI];
    int helium4NumHitsPossible[MAXMULTI];
    double helium4NSigma[MAXMULTI];
    double helium4Px[MAXMULTI];
    double helium4Py[MAXMULTI];
    double helium4Pz[MAXMULTI];
    double helium4Pt[MAXMULTI];
    double helium4dEdx[MAXMULTI];
    double helium4Z[MAXMULTI];
    double helium4Beta[MAXMULTI];
};

#endif  // QA_H
