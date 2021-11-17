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
  Double_t xMin = par[0];
  Double_t xMax = par[1];
  Double_t sig  = par[2];
  Double_t x0   = par[3];
  Double_t lam  = par[4];  
  Int_t nn = 10000;
  Double_t dx = (xMax - xMin)/nn;
  Double_t dx_div_2 = dx/2.0;
  Double_t xx;
  Double_t convVal = 0.0;
  for(Int_t i = 0;i<nn;i++){ 
    xx = dx_div_2 + dx*i;
    convVal += step_exp( xx, x0, lam)*TMath::Gaus(x[0] - xx,0.0,sig)/sig/TMath::Sqrt(2.0*TMath::Pi())*dx;
  }
  return convVal;
}
//    
Int_t convolution(){
  const Int_t n = 10000;
  Double_t xMin = 0.0;
  Double_t xMax = 100.0;
  Double_t x[n];
  Double_t y[n];
  Double_t y_conv[n];
  Double_t sig  = 1.0;
  Double_t  x0 = 10.0;
  Double_t lam = 1.0/10.0;
  const Int_t npar_conv = 5;
  Double_t inParameters_conv[npar_conv];
  inParameters_conv[0] = xMin;
  inParameters_conv[1] = xMax;
  inParameters_conv[2] = sig;
  inParameters_conv[3] = x0;
  inParameters_conv[4] = lam;
  //
  TF1 *f_conv = new TF1("f_conv",conv,xMin,xMax,npar_conv);
  f_conv->SetParameters(inParameters_conv);
  f_conv->FixParameter(0,inParameters_conv[0]);
  f_conv->FixParameter(1,inParameters_conv[1]);
  //
  const Int_t npar_step_exp = 2;
  Double_t inParameters_step_exp[npar_step_exp];
  inParameters_step_exp[0] = x0;
  inParameters_step_exp[1] = lam;
  TF1 *f_step_exp = new TF1("f_step_exp",step_exp_wrapper,xMin,xMax,npar_step_exp);
  f_step_exp->SetParameters(inParameters_step_exp);
  //
  for(Int_t i = 0;i<n;i++){
    x[i] = xMin + (xMax - xMin)/(n-1)*i;
    y[i] = f_step_exp->Eval(x[i]);
    y_conv[i] = f_conv->Eval(x[i]);
  }
  TGraph *gr = new TGraph(n,x,y);
  TGraph *gr_conv = new TGraph(n,x,y_conv);
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
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr);
  mg->Add(gr_conv);
  mg->Draw("APL");
  //
  cout<<"f_step_exp->Integral(xMin,xMax) "<<f_step_exp->Integral(xMin,xMax)<<endl
      <<"f_conv->Integral(xMin,xMax)     "<<f_conv->Integral(xMin,xMax)<<endl;
  //
  return 0;
}
