#include "TH1D.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

void Read( TString inRootFileName = "./data/Proton_100PeV_525km_67_7.root", TString outHistRootFileName = "./hist/hist_Proton_100PeV_525km_67_7.root"){
  //TFile *fIn = new TFile("./data/Proton_100PeV_525km_67_7.root");
  //TFile *fIn = new TFile("./data/Proton_100PeV_33km_85.root");
  TFile *fIn = new TFile(inRootFileName.Data());

  fIn->ls();
  fIn->Print();

  // -----------------------------------------------------------------------------
  // Shower parameter
  // -----------------------------------------------------------------------------
  cout << endl;
  cout << endl;
  TTree *showerProp = (TTree*)fIn->Get("showerProp");
  showerProp->ls();
  showerProp->Print();
  //
  Double_t zenith, energy, startalt;
  TBranch *energyBr = showerProp->GetBranch("energy");
  energyBr->SetAddress(&energy);
  //
  TBranch *zenithBr = showerProp->GetBranch("zenith");
  zenithBr->SetAddress(&zenith);
  TBranch *startaltBr = showerProp->GetBranch("startalt");
  startaltBr->SetAddress(&startalt);
  Int_t nEntries = showerProp->GetEntries();
  cout<<"nEntries:"<<" "<<nEntries<<endl;
  showerProp->GetEntry(0);
  cout<< "Zenith angle = " << zenith <<endl;
  cout<< "E = " << energy << " PeV" << endl;
  cout<< "Starting altitude = " << startalt << " km" << endl;
  // -----------------------------------------------------------------------------
  
  // -----------------------------------------------------------------------------
  // Cherenkov light parameter
  // -----------------------------------------------------------------------------
  cout << endl;
  cout << endl;
  TTree *cherPhProp = (TTree*)fIn->Get("cherPhProp");
  cherPhProp->ls();
  cherPhProp->Print();
  TH1D *wavelength = NULL;
  TH1D *distance = NULL;
  TH1D *time_offset = NULL;
  TH1D *angle_offset = NULL;
  // wavelength
  TBranch *wavelengthBr = cherPhProp->GetBranch("wavelength");
  wavelengthBr->SetAddress(&wavelength);
  cherPhProp->GetEntry(0);
  TCanvas *cwl = new TCanvas("cwl", "cwl", 800, 600);
  cwl->cd();
  wavelength->SetDirectory(0);
  wavelength->GetXaxis()->SetTitle("wavelength [nm]");
  wavelength->Draw();
  // distance
  TBranch *distanceBr = cherPhProp->GetBranch("distance");
  distanceBr->SetAddress(&distance);
  cherPhProp->GetEntry(0);
  TCanvas *cdst = new TCanvas("cdst", "cdst", 800, 600);
  cdst->cd();
  distance->SetDirectory(0);
  TH1D *hdistance = (TH1D *)(distance)->Clone();
  hdistance->SetTitle("distance");
  hdistance->GetYaxis()->SetTitle("photon density [pht/m^{2}]");
  hdistance->GetXaxis()->SetTitle("distance [km]");
  hdistance->Draw();
  // time_offset
  TBranch *time_offsetBr = cherPhProp->GetBranch("time_offset");
  time_offsetBr->SetAddress(&time_offset);
  cherPhProp->GetEntry(0);
  TCanvas *ctoff = new TCanvas("ctoff", "ctoff", 800, 600);
  ctoff->cd();
  time_offset->SetDirectory(0);
  time_offset->GetXaxis()->SetTitle("ns");
  time_offset->Draw("histo");
  // angle_offset
  TBranch *angle_offsetBr = cherPhProp->GetBranch("angle_offset");
  angle_offsetBr->SetAddress(&angle_offset);
  cherPhProp->GetEntry(0);
  TCanvas *cangoff = new TCanvas("cangoff", "cangoff", 800, 600);
  cangoff->cd();
  angle_offset->SetDirectory(0);
  angle_offset->GetXaxis()->SetTitle("deg");
  angle_offset->Draw("histo");
  //----------------------------------------------------------------------------------------


  //----------------------------------------------------------------------------------------
  double dist=0.0;
  // time distribution
  TTreeReader fReaderCherPh_time;
  TTreeReaderValue<std::vector<TH1D>> fDistTimeVec = {fReaderCherPh_time, "time_dist"};
  fReaderCherPh_time.SetTree("cherPhProp");
  fReaderCherPh_time.SetEntry(0);
  // get number of photons at aperture
  auto nBinDist = distance->FindBin(dist);
  cout<<"nBinDist "<<nBinDist<<endl;
  //auto ApertureSize = 1.0; // in square meters
  //auto nPh = distance->GetBinContent(nBinDist) * ApertureSize;
  TH1D *timeHist = NULL;
  timeHist = (TH1D*)((*fDistTimeVec)[nBinDist-1]).Clone();
  timeHist->GetYaxis()->SetTitle("photon density [pht/m^{2}]");
  timeHist->GetXaxis()->SetTitle("time [ns]");
  // Plot histogram
  TCanvas *ctmHst = new TCanvas("ctmHst", "ctmHst", 800, 600);
  ctmHst->cd();
  ctmHst->SetLogx();
  ctmHst->SetLogy();
  timeHist->Draw();

  //----------------------------------------------------------------------------------------
  // Angle distribution
  TTreeReader fReaderCherPh_angle;
  TTreeReaderValue<std::vector<TH1D>> fDistAngleVec = {fReaderCherPh_angle, "angle_dist"};
  fReaderCherPh_angle.SetTree("cherPhProp");
  fReaderCherPh_angle.SetEntry(0);
  TH1D *angleHist = NULL;
  angleHist = (TH1D*)((*fDistAngleVec)[nBinDist-1]).Clone();
  angleHist->GetYaxis()->SetTitle("photon density [counts/m^{2}]");
  angleHist->GetXaxis()->SetTitle("angle, deg");
  //Plot histogram
  TCanvas *canglHst = new TCanvas("canglHst", "canglHst", 800, 600);
  canglHst->cd();
  canglHst->SetLogx();
  canglHst->SetLogy();
  angleHist->Draw();
  //fIn->Close();

  //----------------------------------------------------------------------------------------

  //----------------------------------------------------------------------------------------
  // hist out
  TFile* rootFile = new TFile(outHistRootFileName.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<outHistRootFileName.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<outHistRootFileName.Data()<<endl;
  //----------------------------------------------------------------------------------------
  wavelength->SetName("h1_wavelength");
  distance->SetName("h1_distance");
  time_offset->SetName("h1_time_offset");
  angle_offset->SetName("h1_angle_offset");
  timeHist->SetName("h1_timeHist");
  angleHist->SetName("h1_angleHist");
  //
  wavelength->Write();
  distance->Write();
  time_offset->Write();
  angle_offset->Write();
  timeHist->Write();
  angleHist->Write();
}
