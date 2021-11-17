//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <time.h>

using namespace std;

const Int_t npar_4gauss = 14;
Double_t par_ozone_crossection_4gauss[npar_4gauss];

Double_t wldist(Double_t *x, Double_t *par);
Double_t ozone_crossection(Double_t x);
void read_par_ozone_crossection_4gauss();
  
void read_par_ozone_crossection_4gauss(){
  ifstream modelfile ("./ozon_abs_model_four_gauss.dat");
  Int_t ipar;
  Double_t parVal;
  if(modelfile.is_open()){
    while (modelfile>>ipar>>parVal){
      par_ozone_crossection_4gauss[ipar] = parVal;
    }
    modelfile.close();
  }
  else cout << "Unable to open file"; 
}

Double_t ozone_crossection(Double_t x){
  //
  Double_t A1   = par_ozone_crossection_4gauss[0];
  Double_t x01  = par_ozone_crossection_4gauss[1];
  Double_t sig1 = par_ozone_crossection_4gauss[2];
  //
  Double_t A2   = par_ozone_crossection_4gauss[3];
  Double_t x02  = par_ozone_crossection_4gauss[4];
  Double_t sig2 = par_ozone_crossection_4gauss[5];
  //
  Double_t A3   = par_ozone_crossection_4gauss[6];
  Double_t x03  = par_ozone_crossection_4gauss[7];
  Double_t sig3 = par_ozone_crossection_4gauss[8];
  //
  Double_t A4   = par_ozone_crossection_4gauss[9];
  Double_t x04  = par_ozone_crossection_4gauss[10];
  Double_t sig4 = par_ozone_crossection_4gauss[11];
  //
  Double_t K    = par_ozone_crossection_4gauss[12];
  Double_t C    = par_ozone_crossection_4gauss[13];
  //
  Double_t val = A1*TMath::Exp(-1.0/2.0/sig1/sig1*(x-x01)*(x-x01)) +
    A2*TMath::Exp(-1.0/2.0/sig2/sig2*(x-x02)*(x-x02)) +
    A3*TMath::Exp(-1.0/2.0/sig3/sig3*(x-x03)*(x-x03)) +
    A4*TMath::Exp(-1.0/2.0/sig4/sig4*(x-x04)*(x-x04)) + x*K + C;
  return val;
}

//Double_t wldist(Double_t *x, Double_t *par){
//Double_t A  = par[0];
//Double_t B  = par[1];
//Double_t L0 = par[2];
//Double_t C  = par[3];
////return 1.0/x[0]/x[0]*(A*A - B*B/x[0]/x[0]) + C;
//return A*A/x[0]/x[0]*(1.0 - B*B/(x[0]-L0)/(x[0]-L0)/(x[0]-L0)/(x[0]-L0)*ozone_crossection(x[0])) + C;
//}

Double_t wldist(Double_t *x, Double_t *par){
  Double_t A  = par[0];
  Double_t B  = par[1];
  Double_t C  = par[2];
  return A*A/x[0]/x[0]*(1.0 - B*B/(x[0])/(x[0])/(x[0])/(x[0])*ozone_crossection(x[0])) + C;
}

Int_t fit_wavelength_ozon(){
  //
  read_par_ozone_crossection_4gauss();
  //Get the data
  TString fileN01;
  fileN01 = "./hist/hist_Proton_100PeV_525km_67_7.root";
  TFile *f01 = new TFile(fileN01.Data());
  TH1D *h1 = (TH1D*)f01->Get("h1_wavelength");
  const Int_t nnMax = 1000;
  Int_t nn = 0;
  Double_t x_val;
  Double_t y_val;
  Double_t x[nnMax];
  Double_t y[nnMax];
  Double_t xerr[nnMax];
  Double_t yerr[nnMax];
  for(Int_t i = 1;i<=h1->GetNbinsX();i++){
    x_val = h1->GetBinCenter(i);
    y_val = h1->GetBinContent(i);
    x[i-1] = x_val;
    y[i-1] = y_val;
    xerr[i-1] = 1.0;
    yerr[i-1] = y_val*0.01 + 0.00001;
    nn++;
  }
  TGraphErrors *gr = new TGraphErrors(nn,x,y,xerr,yerr);
  TGraph *gr_notFit = new TGraph(nn,x,y);
  TGraph *gr_CherenkovSpectrum = new TGraph(); 
  TGraph *gr_RayleighScattering = new TGraph();
  TGraph *gr_ozon = new TGraph();
  TGraph *gr_RayleighScattering_ozon = new TGraph();
  TGraph *gr_sp = new TGraph();
  ///////////////////
  //
  const Int_t npar = 3;
  Double_t inParameters[npar];
  Double_t wl_min  = 200;
  Double_t wl_max  = 1100;
  inParameters[0] = TMath::Sqrt(1000.0);
  inParameters[1] = TMath::Sqrt(10000000000000000000000000000000.0);
  inParameters[2] = 0.0;
  //
  //fit
  TF1 *f_wldist = new TF1( "f_wldist", wldist, wl_min, wl_max, npar);
  f_wldist->SetParameters(inParameters);
  f_wldist->SetParName(0, "A");
  f_wldist->SetParName(1, "B");
  f_wldist->SetParName(2, "C");
  //f_wldist->FixParameter(0,inParameters[0]);
  //f_wldist->FixParameter(1,inParameters[1]);
  f_wldist->FixParameter(2,inParameters[2]);
  gr->Fit("f_wldist","","",wl_min, wl_max);
  ///////////////////
  //
  Double_t wl_min_f = 200;
  Double_t wl_max_f = 1100;
  Double_t wl_f;
  Int_t nn_f = 10000;
  Double_t myA = 10000.0;
  Double_t myB = 100000000000000000000000000000.0;
  Double_t myC = 0.0;
  for(Int_t i = 0;i<nn_f; i++){
    wl_f = wl_min_f + (wl_max_f - wl_min_f)/(nn_f-1)*i;
    gr_CherenkovSpectrum->SetPoint(gr_CherenkovSpectrum->GetN(),wl_f,myA/wl_f/wl_f);
    gr_RayleighScattering->SetPoint(gr_CherenkovSpectrum->GetN(),wl_f,myB/wl_f/wl_f/wl_f/wl_f);
    gr_ozon->SetPoint(gr_ozon->GetN(), wl_f, (1.0e+18)*ozone_crossection(wl_f));
    gr_RayleighScattering_ozon->SetPoint(gr_RayleighScattering_ozon->GetN(), wl_f, (10000/wl_f/wl_f - 1.0*(1.7e+14)*ozone_crossection(wl_f) * (1.9e+0)/wl_f/wl_f/wl_f/wl_f));
    gr_sp->SetPoint(gr_CherenkovSpectrum->GetN(),wl_f,(myA/wl_f/wl_f*(1.0 - myB/wl_f/wl_f/wl_f/wl_f*ozone_crossection(wl_f)) + myC));
    //gr_sp->SetPoint(gr_CherenkovSpectrum->GetN(),wl_f,(myA/wl_f/wl_f*myB/wl_f/wl_f/wl_f/wl_f*ozone_crossection(wl_f) + myC));
  }

  //Ploting
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,1200);
  c1->SetRightMargin(0.03);
  c1->SetLeftMargin(0.09);
  c1->SetTopMargin(0.09);
  c1->SetBottomMargin(0.09);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  //
  //gr->Draw("APL");
  //
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr);
  //mg->Add(gr_notFit);
  //gr_CherenkovSpectrum->SetMarkerColor(kBlue);
  //gr_RayleighScattering->SetMarkerColor(kRed);
  //gr_ozon->SetMarkerColor(kMagenta);
  //mg->Add(gr_CherenkovSpectrum);
  //mg->Add(gr_RayleighScattering);
  //mg->Add(gr_ozon);
  //mg->Add(gr_RayleighScattering_ozon);
  //mg->Add(gr_sp);
  //mg->GetXaxis()->SetLimits(xMin,xMax);
  mg->Draw("APL");
  mg->SetMinimum(1.0e-5);
  //mg->SetMaximum(yMax);

  ///////////////////
  return 0;
}
