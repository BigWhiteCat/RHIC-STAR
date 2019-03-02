#include "StV0Maker.h"
#include "TTree.h"

void StV0Maker::initQA() {
    QATree = new TTree("QAPicoDst", "QAPicoDst for QA");
    QATree->SetDirectory(QATreeOutputFile);

    QATree->Branch("referenceMulti", &objectQA.referenceMulti, "refereceMulti/I");   //
    QATree->Branch("primaryVertexX", &objectQA.primeryVertexX, "primaryVertexX/D");  //
    QATree->Branch("primaryVertexY", &objectQA.primeryVertexY, "primaryVertexY/D");  //
    QATree->Branch("primaryVertexZ", &objectQA.primeryVertexZ, "primaryVertexZ/D");  //
    QATree->Branch("eventId", &objectQA.eventId, "eventId/I");                       //
    QATree->Branch("runId", &objectQA.runId, "runId/I");                             //

    /*! pion */
    QATree->Branch("pionNum", &objectQA.pionNum, "pionNum/I");
    QATree->Branch("pionId", objectQA.pionId, "pionId[pionNum/I");
    QATree->Branch("pionDca", objectQA.pionDca, "pionDca[pionNum]/D");
    QATree->Branch("pionMass", objectQA.pionMass, "pionMass[pionNum]/D");
    QATree->Branch("pionEta", objectQA.pionEta, "pionEta[pionNum]/D");
    QATree->Branch("pionRapidity", objectQA.pionRapidity, "pionRapidity[pionNum]/D");
    QATree->Branch("pionNumHitsFit", objectQA.pionNumHitsFit, "pionNumHitsFit[pionNum]/I");
    QATree->Branch("pionNumHitsdEdx", objectQA.pionNumHitsdEdx, "pionNumHitsdEdx[pionNum]/I");
    QATree->Branch("pionNumHitsPossible", objectQA.pionNumHitsPossible, "pionNumHitsPossible[pionNum]/I");
    QATree->Branch("pionNSigma", objectQA.pionNSigma, "pionNSigma[pionNum]/D");
    QATree->Branch("pionPx", objectQA.pionPx, "pionPx[pionNum]/D");
    QATree->Branch("pionPy", objectQA.pionPy, "pionPy[pionNum]/D");
    QATree->Branch("pionPz", objectQA.pionPz, "pionPz[pionNum]/D");
    QATree->Branch("pionPt", objectQA.pionPt, "pionPt[pionNum]/D");
    QATree->Branch("piondEdx", objectQA.piondEdx, "piondEdx[pionNum]/D");
    QATree->Branch("pionZ", objectQA.pionZ, "pionZ[pionNum]/D");
    QATree->Branch("pionBeta", objectQA.pionBeta, "pionBeta[pionNum]/D");

    /*! proton */
    QATree->Branch("protonNum", &objectQA.protonNum, "protonNum/I");
    QATree->Branch("protonId", objectQA.protonId, "protonId[protonNum/I");
    QATree->Branch("protonDca", objectQA.protonDca, "protonDca[protonNum]/D");
    QATree->Branch("protonMass", objectQA.protonMass, "protonMass[protonNum]/D");
    QATree->Branch("protonEta", objectQA.protonEta, "protonEta[protonNum]/D");
    QATree->Branch("protonRapidity", objectQA.protonRapidity, "protonRapidity[protonNum]/D");
    QATree->Branch("protonNumHitsFit", objectQA.protonNumHitsFit, "protonNumHitsFit[protonNum]/I");
    QATree->Branch("protonNumHitsdEdx", objectQA.protonNumHitsdEdx, "protonNumHitsdEdx[protonNum]/I");
    QATree->Branch("protonNumHitsPossible", objectQA.protonNumHitsPossible, "protonNumHitsPossible[protonNum]/I");
    QATree->Branch("protonNSigma", objectQA.protonNSigma, "protonNSigma[protonNum]/D");
    QATree->Branch("protonPx", objectQA.protonPx, "protonPx[protonNum]/D");
    QATree->Branch("protonPy", objectQA.protonPy, "protonPy[protonNum]/D");
    QATree->Branch("protonPz", objectQA.protonPz, "protonPz[protonNum]/D");
    QATree->Branch("protonPt", objectQA.protonPt, "protonPt[protonNum]/D");
    QATree->Branch("protondEdx", objectQA.protondEdx, "protondEdx[protonNum]/D");
    QATree->Branch("protonZ", objectQA.protonZ, "protonZ[protonNum]/D");
    QATree->Branch("protonBeta", objectQA.protonBeta, "protonBeta[pionNum]/D");

    /*! deutron */
    QATree->Branch("deutronNum", &objectQA.deutronNum, "deutronNum/I");
    QATree->Branch("deutronId", objectQA.deutronId, "deutronId[deutronNum/I");
    QATree->Branch("deutronDca", objectQA.deutronDca, "deutronDca[deutronNum]/D");
    QATree->Branch("deutronMass", objectQA.deutronMass, "deutronMass[deutronNum]/D");
    QATree->Branch("deutronEta", objectQA.deutronEta, "deutronEta[deutronNum]/D");
    QATree->Branch("deutronRapidity", objectQA.deutronRapidity, "deutronRapidity[deutronNum]/D");
    QATree->Branch("deutronNumHitsFit", objectQA.deutronNumHitsFit, "deutronNumHitsFit[deutronNum]/I");
    QATree->Branch("deutronNumHitsdEdx", objectQA.deutronNumHitsdEdx, "deutronNumHitsdEdx[deutronNum]/I");
    QATree->Branch("deutronNumHitsPossible", objectQA.deutronNumHitsPossible, "deutronNumHitsPossible[deutronNum]/I");
    QATree->Branch("deutronNSigma", objectQA.deutronNSigma, "deutronNSigma[deutronNum]/D");
    QATree->Branch("deutronPx", objectQA.deutronPx, "deutronPx[deutronNum]/D");
    QATree->Branch("deutronPy", objectQA.deutronPy, "deutronPy[deutronNum]/D");
    QATree->Branch("deutronPz", objectQA.deutronPz, "deutronPz[deutronNum]/D");
    QATree->Branch("deutronPt", objectQA.deutronPt, "deutronPt[deutronNum]/D");
    QATree->Branch("deutrondEdx", objectQA.deutrondEdx, "deutrondEdx[deutronNum]/D");
    QATree->Branch("deutronZ", objectQA.deutronZ, "deutronZ[deutronNum]/D");
    QATree->Branch("deutronBeta", objectQA.deutronBeta, "deutronBeta[deutronNum]/D");

    /*! triton */
    QATree->Branch("tritonNum", &objectQA.tritonNum, "tritonNum/I");
    QATree->Branch("tritonId", objectQA.tritonId, "tritonId[tritonNum/I");
    QATree->Branch("tritonDca", objectQA.tritonDca, "tritonDca[tritonNum]/D");
    QATree->Branch("tritonMass", objectQA.tritonMass, "tritonMass[tritonNum]/D");
    QATree->Branch("tritonEta", objectQA.tritonEta, "tritonEta[tritonNum]/D");
    QATree->Branch("tritonRapidity", objectQA.tritonRapidity, "tritonRapidity[tritonNum]/D");
    QATree->Branch("tritonNumHitsFit", objectQA.tritonNumHitsFit, "tritonNumHitsFit[tritonNum]/I");
    QATree->Branch("tritonNumHitsdEdx", objectQA.tritonNumHitsdEdx, "tritonNumHitsdEdx[tritonNum]/I");
    QATree->Branch("tritonNumHitsPossible", objectQA.tritonNumHitsPossible, "tritonNumHitsPossible[tritonNum]/I");
    QATree->Branch("tritonNSigma", objectQA.tritonNSigma, "tritonNSigma[tritonNum]/D");
    QATree->Branch("tritonPx", objectQA.tritonPx, "tritonPx[tritonNum]/D");
    QATree->Branch("tritonPy", objectQA.tritonPy, "tritonPy[tritonNum]/D");
    QATree->Branch("tritonPz", objectQA.tritonPz, "tritonPz[tritonNum]/D");
    QATree->Branch("tritonPt", objectQA.tritonPt, "tritonPt[tritonNum]/D");
    QATree->Branch("tritondEdx", objectQA.tritondEdx, "tritondEdx[tritonNum]/D");
    QATree->Branch("tritonZ", objectQA.tritonZ, "tritonZ[tritonNum]/D");
    QATree->Branch("tritonBeta", objectQA.tritonBeta, "tritonBeta[tritonNum]/D");

    /*! helium3 */
    QATree->Branch("helium3Num", &objectQA.helium3Num, "helium3Num/I");
    QATree->Branch("helium3Id", objectQA.helium3Id, "helium3Id[helium3Num/I");
    QATree->Branch("helium3Dca", objectQA.helium3Dca, "helium3Dca[helium3Num]/D");
    QATree->Branch("helium3Mass", objectQA.helium3Mass, "helium3Mass[helium3Num]/D");
    QATree->Branch("helium3Eta", objectQA.helium3Eta, "helium3Eta[helium3Num]/D");
    QATree->Branch("helium3Rapidity", objectQA.helium3Rapidity, "helium3Rapidity[helium3Num]/D");
    QATree->Branch("helium3NumHitsFit", objectQA.helium3NumHitsFit, "helium3NumHitsFit[helium3Num]/I");
    QATree->Branch("helium3NumHitsdEdx", objectQA.helium3NumHitsdEdx, "helium3NumHitsdEdx[helium3Num]/I");
    QATree->Branch("helium3NumHitsPossible", objectQA.helium3NumHitsPossible, "helium3NumHitsPossible[helium3Num]/I");
    QATree->Branch("helium3NSigma", objectQA.helium3NSigma, "helium3NSigma[helium3Num]/D");
    QATree->Branch("helium3Px", objectQA.helium3Px, "helium3Px[helium3Num]/D");
    QATree->Branch("helium3Py", objectQA.helium3Py, "helium3Py[helium3Num]/D");
    QATree->Branch("helium3Pz", objectQA.helium3Pz, "helium3Pz[helium3Num]/D");
    QATree->Branch("helium3Pt", objectQA.helium3Pt, "helium3Pt[helium3Num]/D");
    QATree->Branch("helium3dEdx", objectQA.helium3dEdx, "helium3dEdx[helium3Num]/D");
    QATree->Branch("helium3Z", objectQA.helium3Z, "helium3Z[helium3Num]/D");
    QATree->Branch("helium3Beta", objectQA.helium3Beta, "helium3Beta[helium3Num]/D");

    /*! helium4 */
    QATree->Branch("helium4Num", &objectQA.helium4Num, "helium4Num/I");
    QATree->Branch("helium4Id", objectQA.helium4Id, "helium4Id[helium4Num/I");
    QATree->Branch("helium4Dca", objectQA.helium4Dca, "helium4Dca[helium4Num]/D");
    QATree->Branch("helium4Mass", objectQA.helium4Mass, "helium4Mass[helium4Num]/D");
    QATree->Branch("helium4Eta", objectQA.helium4Eta, "helium4Eta[helium4Num]/D");
    QATree->Branch("helium4Rapidity", objectQA.helium4Rapidity, "helium4Rapidity[helium4Num]/D");
    QATree->Branch("helium4NumHitsFit", objectQA.helium4NumHitsFit, "helium4NumHitsFit[helium4Num]/I");
    QATree->Branch("helium4NumHitsdEdx", objectQA.helium4NumHitsdEdx, "helium4NumHitsdEdx[helium4Num]/I");
    QATree->Branch("helium4NumHitsPossible", objectQA.helium4NumHitsPossible, "helium4NumHitsPossible[helium4Num]/I");
    QATree->Branch("helium4NSigma", objectQA.helium4NSigma, "helium4NSigma[helium4Num]/D");
    QATree->Branch("helium4Px", objectQA.helium4Px, "helium4Px[helium4Num]/D");
    QATree->Branch("helium4Py", objectQA.helium4Py, "helium4Py[helium4Num]/D");
    QATree->Branch("helium4Pz", objectQA.helium4Pz, "helium4Pz[helium4Num]/D");
    QATree->Branch("helium4Pt", objectQA.helium4Pt, "helium4Pt[helium4Num]/D");
    QATree->Branch("helium4dEdx", objectQA.helium4dEdx, "helium4dEdx[helium4Num]/D");
    QATree->Branch("helium4Z", objectQA.helium4Z, "helium4Z[helium4Num]/D");
    QATree->Branch("helium4Beta", objectQA.helium4Beta, "helium4Beta[helium4Num]/D");
}

void StV0Maker::setQATreeOutputFileName(TString name) {
    QATreeOutputFileName = name;
}

void StV0Maker::initQAParameter() {
    this->PionMass = 0.13957061;
    this->PionCharge = -1;
    this->ProtonMass = 0.938272081;
    this->ProtonCharge = 1;
    this->DeutronMass = 1.875613;
    this->DeutronCharge = 1;
    this->TritonMass = 2.8089198;
    this->TritonMass = 1;
    this->Helium3Mass = 2.808391586;
    this->Helium3Charge = 2;
    this->Helum4Mass = 3.72737937;
    this->Helium4Charge = 2;
}
