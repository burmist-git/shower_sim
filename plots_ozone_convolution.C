//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
//
#include <time.h>
//
using namespace std;
//
Double_t step_exp(Double_t x, Double_t x0, Double_t lam);
Double_t step_exp_wrapper(Double_t *x, Double_t *par);
Double_t conv(Double_t *x, Double_t *par);
//
Double_t step_exp(Double_t x, Double_t x0, Double_t lam){
  if(x<x0)
    return 0.0;
  return TMath::Exp(-lam*(x-x0));
}
//
Double_t step_exp_wrapper(Double_t *x, Double_t *par){
  Double_t x0 = par[0];
  Double_t lam = par[1];
  return step_exp( x[0], x0, lam);
}
//
Double_t conv(Double_t *x, Double_t *par){
  //
  Double_t xMin    = par[0];
  Double_t xMax    = par[1];
  Double_t sig     = par[2];
  Double_t x0      = par[3];
  Double_t lam     = par[4];
  Double_t A       = par[5];
  Double_t AGaus   = par[6];
  Double_t x0Gaus  = par[7];
  Double_t sigGaus = par[8];
  //
  Int_t nn = 10000;
  Double_t dx = (xMax - xMin)/nn;
  Double_t dx_div_2 = dx/2.0;
  Double_t xx;
  Double_t convVal = 0.0;
  for(Int_t i = 0;i<nn;i++){ 
    xx = dx_div_2 + dx*i;
    convVal += step_exp( xx, x0, lam)*TMath::Gaus(x[0] - xx,0.0,sig)/sig/TMath::Sqrt(2.0*TMath::Pi())*dx;
  }
  return A*convVal + AGaus*TMath::Exp(-1.0/2.0/sigGaus/sigGaus*(x[0]-x0Gaus)*(x[0]-x0Gaus));
}
//
Double_t one_gauss(Double_t *x, Double_t *par){
  Double_t A1   = par[0];
  Double_t x01  = par[1];
  Double_t sig1 = par[2];
  return A1*TMath::Exp(-1.0/2.0/sig1/sig1*(x[0]-x01)*(x[0]-x01));
}
//
Int_t plots_ozone_convolution(){
  //
  TString fileN;
  fileN = "./ozone/ozone_crossection_02.csv";
  //
  Double_t wl_min  = 200;
  Double_t wl_max  = 1100;
  Double_t  fit_gauss_min = 200.0;
  Double_t  fit_gauss_max = 300.0;
  //
  const Int_t npar_conv = 9;
  Double_t inParameters_conv[npar_conv];
  //
  TF1 *f_conv = new TF1("f_conv",conv,wl_min,wl_max,npar_conv);
  //
  TGraph *gr1 = new TGraph();
  TGraphErrors *grall = new TGraphErrors();
  TGraph *gr_nofit = new TGraph();
  grall->SetName("");
  gr_nofit->SetName("");
  gr1->SetName("");
  Double_t x,y;
  ifstream fileIn(fileN.Data());
  if (fileIn.is_open()) {
    while ( fileIn>>x>>y ) {
      Int_t ii = grall->GetN();
      grall->SetPoint(ii,x,y);
      grall->SetPointError(ii,1.0*1,1.0*(y*0.1 + 1.0e-18*0.001));
      gr_nofit->SetPoint(gr_nofit->GetN(),x,y);
      if(x>=fit_gauss_min && x<=fit_gauss_max)
        gr1->SetPoint(gr1->GetN(),x,y);
    }
    fileIn.close();
  }
  else cout<<"Unable to open file"<<endl; 
  ///////////////////////////////////////
  //
  gr1->Fit("gaus","","",fit_gauss_min, fit_gauss_max);
  TF1 *f_git_gaus1 = (TF1*)gr1->GetListOfFunctions()->FindObject("gaus");
  //
  inParameters_conv[0] = wl_min-1000;
  inParameters_conv[1] = wl_max+1000;
  inParameters_conv[2] = 30;           //sig
  inParameters_conv[3] = 530;          //x0
  inParameters_conv[4] = 1.0/100;      //lam
  inParameters_conv[5] = 7.0*1.0e-21;  //A
  f_git_gaus1->GetParameters(&inParameters_conv[6]);
  f_conv->SetParameters(inParameters_conv);
  f_conv->FixParameter(0,inParameters_conv[0]);
  f_conv->FixParameter(1,inParameters_conv[1]);
  //f_conv->FixParameter(2,inParameters_conv[2]);
  //f_conv->FixParameter(3,inParameters_conv[3]);
  //f_conv->FixParameter(4,inParameters_conv[4]);
  //f_conv->FixParameter(5,inParameters_conv[5]);
  grall->Fit("f_conv","","",wl_min,wl_max);
  TF1 *f_fit_all = (TF1*)grall->GetListOfFunctions()->FindObject("f_conv");
  //
  ///////////////////////////////////////
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  //
  grall->Draw("APL");
  //
  TCanvas *c2 = new TCanvas("c2","c2",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  //
  //gr_nofit->Draw("APL");
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_nofit);
  mg->Draw("APL");
  mg->GetXaxis()->SetTitle("wavelength, nm");
  mg->GetYaxis()->SetTitle("cross-section, cm^{2}/molecule");
  f_fit_all->Draw("same");
  //
  TF1 *f_one_gauss01 = new TF1("f_one_gauss01",one_gauss,wl_min,wl_max,3);
  f_one_gauss01->SetParameter(0,f_fit_all->GetParameter(6));
  f_one_gauss01->SetParameter(1,f_fit_all->GetParameter(7));
  f_one_gauss01->SetParameter(2,f_fit_all->GetParameter(8));
  f_one_gauss01->Draw("same");
  f_one_gauss01->SetLineColor(kMagenta);
  TF1 *f_conv_p = new TF1("f_conv_p",conv,wl_min,wl_max,npar_conv);
  f_conv_p->SetParameter(0,f_fit_all->GetParameter(0));
  f_conv_p->SetParameter(1,f_fit_all->GetParameter(1));
  f_conv_p->SetParameter(2,f_fit_all->GetParameter(2));
  f_conv_p->SetParameter(3,f_fit_all->GetParameter(3));
  f_conv_p->SetParameter(4,f_fit_all->GetParameter(4));
  f_conv_p->SetParameter(5,f_fit_all->GetParameter(5));
  f_conv_p->SetParameter(6,0.0);
  f_conv_p->SetParameter(7,0.0);
  f_conv_p->SetParameter(8,1.0);
  f_conv_p->SetLineColor(kBlue);
  f_conv_p->Draw("same");
  //
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_nofit, "Data", "lp");
  leg->AddEntry(f_fit_all, "Total fit", "l");
  leg->AddEntry(f_one_gauss01, "Gauss", "l");
  leg->AddEntry(f_conv_p, "Step exponent convoluted with gauss", "l");
  leg->Draw();
  //
  //
  FILE *fp;
  fp = fopen("./ozon_abs_model_conv.dat", "w+");
  for(Int_t ii = 0;ii<npar_conv;ii++)
    fprintf(fp,"%d %100.90f \n",ii, f_fit_all->GetParameter(ii));
  fclose(fp);
  //
  return 0;
}
