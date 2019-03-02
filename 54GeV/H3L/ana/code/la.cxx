#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "v0dst.h"

using namespace std;

TChain* ChainThem(char* filelist, char* treename, int nlist = 0, int block = 100);
const int kCentBin = 10; // 1 for d+Au;10 for MB, 3 for central
double getCentBin(Int_t nrefmult);

//histogram
double array_cent[11] = {0.0,5.0,10.0,20.0,30.0,40.0,50.0,60.0,70.0,80.0,100.0};

TH1D *cent            = new TH1D("centrality","centrality",10,array_cent);
TH1D *hla             = new TH1D("la","la invmass", 80,2.96,3.04);
TH2D *hlavsdau1dca    = new TH2D("lavsdau1dca","la invmass", 80,2.96,3.04,500,0.0,50.0);
TH2D *hlavsdau2dca    = new TH2D("lavsdau2dca","la invmass", 80,2.96,3.04,500,0.0,50.0);
TH2D *hlavsangle      = new TH2D("lavsangle","la invmass", 80,2.96,3.04,314,0.0,3.14);
TH2D *hlavsdecl       = new TH2D("lavsdecl","la invmass", 80,2.96,3.04,500,0.0,50);
TH2D *hlavsdau1pt     = new TH2D("lavsdau1pt","la invmass", 80,2.96,3.04,100,0.0,10.0);
TH2D *hlavsdau2pt     = new TH2D("lavsdau2pt","la invmass", 80,2.96,3.04,100,0.0,10.0);

int main(int n, char** argv)
{
  if(n!=5)
    {
      cout<<"the number of main function's argument is not 4!!!!!!"<<endl;
      return 0;
    }
  int nlist,block;
  nlist = atoi(argv[1]);
  block = atoi(argv[2]);

  //firstly use the TTree::MakeClass to generate a handy wrapper class.
  //modify it (the array size) and load it here!

  char filelist[256];
  sprintf(filelist,"../%s",argv[3]);
  TChain * t  = ChainThem(filelist,"V0PicoDst",nlist,block);
  if(!t){ cout<<"ERROR: no files are added to the chain!"<<endl; return 0; }
  //bound them together
  v0dst dst(t);

  int VertexZPos;
  double centbin = -1.0;

  //book histograms
  char filename[256];
  sprintf(filename,"../%s_%d.root",argv[4],nlist);
  TFile *ohm = new TFile(filename,"recreate");
  cent->SetDirectory(ohm);
  hla->SetDirectory(ohm);
  hlavsdau1dca->SetDirectory(ohm);
  hlavsdau2dca->SetDirectory(ohm);
  hlavsangle->SetDirectory(ohm);
  hlavsdecl->SetDirectory(ohm);
  hlavsdau1pt->SetDirectory(ohm);
  hlavsdau2pt->SetDirectory(ohm);

  cent->Sumw2();
  hla->Sumw2();
  hlavsdau1dca->Sumw2();
  hlavsdau2dca->Sumw2();
  hlavsangle->Sumw2();
  hlavsdecl->Sumw2();
  hlavsdau1pt->Sumw2();
  hlavsdau2pt->Sumw2();

  //event loop (copy from wrapper class' Loop method
  Long64_t nentries = t->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for(Long64_t jentry = 0; jentry<nentries; jentry++)
  {
	  Long64_t ientry = dst.LoadTree(jentry);
	  if(ientry < 0) break;
	  nb = t->GetEntry(jentry);   nbytes += nb;
	  if(jentry%10000==0)
	  {
		  cout<<jentry<<" "<<nentries<<endl;
	  }
	  centbin = getCentBin(dst.nrefmult);
	  cent->Fill(centbin);
	  if(centbin<0)continue;
//	  if(centbin<0||centbin>80)continue;
	  VertexZPos = dst.primvertexZ;
	  if(fabs(VertexZPos)>=60.)continue;//VertexZPos=30->BufferPointer 100,should be 0-99

	  for(Int_t i=0;i<dst.nv0;i++)
	  {

	    if(dst.dau1nhitsfit[i]<22)continue;
	    if(dst.dau2nhitsfit[i]<22)continue;

	    if(dst.dau1nhitsdedx[i]<15)continue;
	    if(dst.dau2nhitsdedx[i]<15)continue;

	    if(dst.dau1Z[i]<-0.10 || dst.dau1Z[i]>0.40)continue;
	    if(fabs(dst.dau2nsigma[i])>3.0)continue;

	    if((dst.dau1mass[i]>0) && (dst.dau1mass[i]<1.40  || dst.dau1mass[i] > 2.40))continue;
	    if((dst.dau2mass[i]>0) && (dst.dau2mass[i]<0.005 || dst.dau2mass[i] > 0.035))continue;

	    if(dst.v0dca[i]>1.0)continue;

	    if(dst.dau1dca[i]<0.0)continue;
	    if(dst.dau1dca[i]>1.0)continue;
	    if(dst.dau2dca[i]<1.5)continue;
	    if(dst.dau2dca[i]>15.0)continue;
	    if(dst.dca1to2[i]>0.7)continue;

	    if(dst.v0declen[i]<2.0)continue;

	    if(dst.v0rdotp[i]<0.0)continue;
	    if(dst.v0sinth[i]>0.20)continue;

	    if(dst.dau1pt[i]<1.0)continue;
	    if(dst.dau2pt[i]<0.15)continue;

	    TVector3 mom_h3l(dst.v0px[i],dst.v0py[i],dst.v0pz[i]);
	    TVector3 mom_he3(dst.dau1px[i],dst.dau1py[i],dst.dau1pz[i]);

	    if(mom_h3l.Angle(mom_he3)>0.08)continue;

	    hlavsdau1dca->Fill(dst.v0mass[i],dst.dau1dca[i]);
	    hlavsdau2dca->Fill(dst.v0mass[i],dst.dau2dca[i]);
	    hlavsangle->Fill(dst.v0mass[i],dst.v0sinth[i]);
	    hlavsdecl->Fill(dst.v0mass[i],dst.v0declen[i]);
	    hlavsdau1pt->Fill(dst.v0mass[i],dst.dau1pt[i]);
	    hlavsdau2pt->Fill(dst.v0mass[i],dst.dau2pt[i]);

	    hla->Fill(dst.v0mass[i]);
	  }

  }
  cout<<"loop finished! Save and Exit!"<<endl;
  ohm->Write();	//save all booked histograms
  ohm->Close();
  delete t;
  return 0;
}

double getCentBin(Int_t nrefmult)
{

   //Int_t centbd[kCentBin+1]={0,200}; //d+Au
   Int_t centbd[kCentBin+1]={0,14,31,57,96,150,222,319,441,520,10000}; //Au+Au MB
   //Int_t centbd[kCentBin+1]={0,14,520,10000};

   Int_t i;
   if(nrefmult<centbd[0] || nrefmult>= centbd[kCentBin])return -1;
   for(i=0;i<kCentBin;i++)
   {
	   if(centbd[i]<=nrefmult && centbd[i+1]>nrefmult)break;
   }

   double cent = -999.0;

   if(i==0) cent = 9.0;
   if(i==1) cent = 7.5;
   if(i==2) cent = 6.5;
   if(i==3) cent = 5.5;
   if(i==4) cent = 4.5;
   if(i==5) cent = 3.5;
   if(i==6) cent = 2.5;
   if(i==7) cent = 1.5;
   if(i==8) cent = 0.75;
   if(i==9) cent = 0.25;

   return cent*10;
}

TChain* ChainThem(char* filelist, char* treename, int nlist, int block)
{

   TChain *globChain = new TChain(treename);

   //cout << ">>> Load Chain from file: " << filelist << endl;
   ifstream fList(filelist);
   if (!fList)
   {
	cout << "!!! Can't open file " << filelist << endl;
	return NULL;
   }
   int count=nlist*block; //files per job
   int Ncount = 0;
   int fileGet = 0;
   char lineFromFile[255];

   while(!fList.eof() && Ncount<count)
   {
	   fList.getline(lineFromFile,250,'\n');
	   //cout<<lineFromFile<<endl;
	   Ncount++;
   }
   if(Ncount<count)return NULL;
   int goodfile=0;
   while(!fList.eof() && fileGet<block){
	   fList.getline(lineFromFile,250,'\n');
	   fileGet++;
	   TFile test(lineFromFile);
	   cout<<lineFromFile<<endl;
	   if(test.GetEND()>250)
	   {
		   globChain->Add(lineFromFile,0);
		   cout<<fileGet<<" loaded "<<endl;
		   goodfile++;
	   }
	   else
	   {
		   cout<<fileGet<<" bad! Failed to load"<<endl;
	   }
	   test.Close();
   }
   fList.close();
   cout<<"Good file = "<<goodfile<<endl;

   /*
   while(fList.getline(lineFromFile, 250))
   {
	Ncount++;
	if(Ncount<=nlist*block)continue;
	if(Ncount>(nlist+1)*block)break;
	if(globChain->Add(lineFromFile,0)){
	   cout << ">> File '" << lineFromFile << "' has been loaded" << endl;
	   Nfiles ++;
	}
	else
	   cout << ">> Can't load file '" << lineFromFile << "'" << endl;
   }

   cout << ">> Total number of entries: " << globChain->GetEntriesFast() << endl;
   fList.close();
   */
   if(goodfile == 0)
   {
	delete globChain;
	return NULL;
   }
   return globChain;
}
