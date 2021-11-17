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

Double_t wldist(Double_t *x, Double_t *par){
  Double_t A  = par[0];
  Double_t B  = par[1];
  Double_t L0 = par[2];
  Double_t C  = par[3];
  //return 1.0/x[0]/x[0]*(A*A - B*B/x[0]/x[0]) + C;
  return A*A/x[0]/x[0]*(1.0 - B*B/(x[0]-L0)/(x[0]-L0)/(x[0]-L0)/(x[0]-L0)) + C;
}

Int_t fit_wavelength_simple(){
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
  TGraph *gr_sp = new TGraph();
  ///////////////////
  //
  const Int_t npar = 4;
  Double_t inParameters[npar];
  Double_t wl_min  = 620;
  Double_t wl_max  = 900;
  //inParameters[0] = TMath::Sqrt(0.0035*300.0*300.0);
  //inParameters[0] = 18.3192;
  inParameters[0] = TMath::Sqrt(10000.0);
  //inParameters[1] = TMath::Sqrt(0.0005*700*700*700*700);
  //inParameters[1] = 11870.3;
  //inParameters[1] = 1.0e+6;
  inParameters[1] = TMath::Sqrt(10000000000.0);
  inParameters[2] = 200.0;
  inParameters[3] = 0.0;

  //fit
  TF1 *f_wldist = new TF1( "f_wldist", wldist, wl_min, wl_max, npar);
  f_wldist->SetParameters(inParameters);
  f_wldist->SetParName(0, "A");
  f_wldist->SetParName(1, "B");
  f_wldist->SetParName(2, "L0");
  f_wldist->SetParName(3, "C");
  //f_wldist->FixParameter(0,inParameters[0]);
  //f_wldist->FixParameter(1,inParameters[1]);
  f_wldist->FixParameter(2,inParameters[2]);
  //f_wldist->FixParameter(3,inParameters[3]);
  gr->Fit("f_wldist","","",wl_min, wl_max);
  cout<<" 0 "<<f_wldist->GetParameter(0)<<endl
      <<" 1 "<<f_wldist->GetParameter(1)<<endl 
      <<" 2 "<<f_wldist->GetParameter(2)<<endl
      <<" 3 "<<f_wldist->GetParameter(3)<<endl;
  ///////////////////

  Double_t wl_min_f = 450;
  Double_t wl_max_f = 5000;
  Double_t wl_f;
  Int_t nn_f = 10000;
  Double_t myA = 10000.0;
  Double_t myB = 10000000000.0;
  Double_t lambda0 = 300;
  Double_t myC = 0.0;
  for(Int_t i = 0;i<nn_f; i++){
    wl_f = wl_min_f + (wl_max_f - wl_min_f)/(nn_f-1)*i;
    gr_CherenkovSpectrum->SetPoint(gr_CherenkovSpectrum->GetN(),wl_f,myA/wl_f/wl_f);
    gr_RayleighScattering->SetPoint(gr_CherenkovSpectrum->GetN(),wl_f,myB/(wl_f-lambda0)/(wl_f-lambda0)/(wl_f-lambda0)/(wl_f-lambda0));
    gr_sp->SetPoint(gr_CherenkovSpectrum->GetN(),wl_f,(myA/wl_f/wl_f*(1.0 - myB/(wl_f-lambda0)/(wl_f-lambda0)/(wl_f-lambda0)/(wl_f-lambda0)) + myC));
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
  mg->Add(gr_notFit);
  gr_CherenkovSpectrum->SetMarkerColor(kBlue);
  gr_RayleighScattering->SetMarkerColor(kRed);
  //mg->Add(gr_CherenkovSpectrum);
  //mg->Add(gr_RayleighScattering);
  //mg->Add(gr_sp);
  //mg->GetXaxis()->SetLimits(xMin,xMax);
  mg->Draw("AP");
  //mg->SetMinimum(yMin);
  //mg->SetMaximum(yMax);

  ///////////////////
  return 0;
}
