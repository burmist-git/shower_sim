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

void makeNormTH1D(TH1D *h1, Double_t norm);
void IntegrateInTime(TH1D *h1_time_integral, TH1D *h1_time);
void IntegrateInWavelength(TH1D *h1_Wavelength_integral, TH1D *h1_to_integrate);
void loadPDE_formFile(TString fileName, Double_t *xx, Double_t *yy, Int_t &nn);
void conv_with_PDE( TH1D *h1_wl_pde, TH1D *h1_wl, TGraph *gr_PDE);
void conv_with_const( TH1D *h1_out, TH1D *h1_in, Double_t val);

void divideOnBackground(TH1D *h1, TGraph *gr);

void load_NGB_formFile(TString fileName, TGraph *gr);

void compare_PDE_NUV_RGB();

Int_t plots_Impact_Parameter_20_25_30(){
  //
  TString leg01Lable_01;
  TString leg01Lable_02;
  TString leg01Lable_03;
  TString fileN01;
  TString fileN02;
  TString fileN03;
  //
  leg01Lable_01 = "20km altitude";
  leg01Lable_02 = "25km altitude";
  leg01Lable_03 = "30km altitude";
  //
  fileN01 = "./hist/hist_20km_Impact_Parameter.root";
  fileN02 = "./hist/hist_25km_Impact_Parameter.root";
  fileN03 = "./hist/hist_30km_Impact_Parameter.root";
  //
  TFile *f01 = new TFile(fileN01.Data());
  TFile *f02 = new TFile(fileN02.Data());
  TFile *f03 = new TFile(fileN03.Data());
  //
  TH1D *h1_01_1 = (TH1D*)f01->Get("h1_wavelength");
  TH1D *h1_01_2 = (TH1D*)f01->Get("h1_distance");
  TH1D *h1_01_3 = (TH1D*)f01->Get("h1_time_offset");
  TH1D *h1_01_4 = (TH1D*)f01->Get("h1_angle_offset");
  TH1D *h1_01_5 = (TH1D*)f01->Get("h1_timeHist");
  TH1D *h1_01_6 = (TH1D*)f01->Get("h1_angleHist");
  //
  TH1D *h1_02_1 = (TH1D*)f02->Get("h1_wavelength");
  TH1D *h1_02_2 = (TH1D*)f02->Get("h1_distance");
  TH1D *h1_02_3 = (TH1D*)f02->Get("h1_time_offset");
  TH1D *h1_02_4 = (TH1D*)f02->Get("h1_angle_offset");
  TH1D *h1_02_5 = (TH1D*)f02->Get("h1_timeHist");
  TH1D *h1_02_6 = (TH1D*)f02->Get("h1_angleHist");
  //
  TH1D *h1_03_1 = (TH1D*)f03->Get("h1_wavelength");
  TH1D *h1_03_2 = (TH1D*)f03->Get("h1_distance");
  TH1D *h1_03_3 = (TH1D*)f03->Get("h1_time_offset");
  TH1D *h1_03_4 = (TH1D*)f03->Get("h1_angle_offset");
  TH1D *h1_03_5 = (TH1D*)f03->Get("h1_timeHist");
  TH1D *h1_03_6 = (TH1D*)f03->Get("h1_angleHist");
  //
  TH1D *h1_arr[7][6];
  //
  h1_arr[0][0] = h1_01_1;
  h1_arr[0][1] = h1_01_2;
  h1_arr[0][2] = h1_01_3;
  h1_arr[0][3] = h1_01_4;
  h1_arr[0][4] = h1_01_5;
  h1_arr[0][5] = h1_01_6;
  //
  h1_arr[1][0] = h1_02_1;
  h1_arr[1][1] = h1_02_2;
  h1_arr[1][2] = h1_02_3;
  h1_arr[1][3] = h1_02_4;
  h1_arr[1][4] = h1_02_5;
  h1_arr[1][5] = h1_02_6;
  //
  h1_arr[2][0] = h1_03_1;
  h1_arr[2][1] = h1_03_2;
  h1_arr[2][2] = h1_03_3;
  h1_arr[2][3] = h1_03_4;
  h1_arr[2][4] = h1_03_5;
  h1_arr[2][5] = h1_03_6;
  //
  for(Int_t ii = 0;ii<3;ii++){
    for(Int_t jj = 0;jj<6;jj++){
      h1_arr[ii][jj]->SetLineWidth(3.0);
      if(ii == 0)
	h1_arr[ii][jj]->SetLineColor(kBlack);
      if(ii == 1)
	h1_arr[ii][jj]->SetLineColor(kBlue);
      if(ii == 2)
	h1_arr[ii][jj]->SetLineColor(kRed);
    }
  }
  //
  //--------------------------------------------------
  TLegend *leg01 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg01->AddEntry(h1_01_1, leg01Lable_01.Data(), "l");
  leg01->AddEntry(h1_02_1, leg01Lable_02.Data(), "l");
  leg01->AddEntry(h1_03_1, leg01Lable_03.Data(), "l");
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  c1->SetRightMargin(0.03);
  c1->SetLeftMargin(0.09);
  c1->SetTopMargin(0.02);
  c1->SetBottomMargin(0.09);
  //
  //
  makeNormTH1D(h1_arr[0][0], 1.0/h1_arr[0][0]->GetBinWidth(1));
  makeNormTH1D(h1_arr[1][0], 1.0/h1_arr[0][0]->GetBinWidth(1));
  makeNormTH1D(h1_arr[2][0], 1.0/h1_arr[0][0]->GetBinWidth(1));
  //
  h1_arr[0][0]->SetTitle("");
  h1_arr[0][0]->SetName("20km");
  h1_arr[1][0]->SetName("25km");
  h1_arr[2][0]->SetName("30km");
  h1_arr[0][0]->Draw();
  for(Int_t jj = 1;jj<3;jj++)
    h1_arr[jj][0]->Draw("sames");
  h1_arr[0][0]->SetMaximum(0.03);
  h1_arr[0][0]->SetMinimum(0.0);
  leg01->Draw();
  h1_arr[0][0]->GetXaxis()->SetTitle("Wavelength, nm");
  h1_arr[0][0]->GetYaxis()->SetTitle("a.u.");
  //

  //--------------------------------------------------
  TCanvas *c2 = new TCanvas("c2","c2",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  //gStyle->SetOptStat(kFALSE);
  //
  c2->SetRightMargin(0.03);
  c2->SetLeftMargin(0.09);
  c2->SetTopMargin(0.02);
  c2->SetBottomMargin(0.09);
  //
  h1_arr[0][1]->SetTitle("");
  h1_arr[0][1]->SetName("20km");
  h1_arr[1][1]->SetName("25km");
  h1_arr[2][1]->SetName("30km");
  h1_arr[0][1]->Draw();
  for(Int_t jj = 1;jj<3;jj++)
    h1_arr[jj][1]->Draw("sames");
  h1_arr[0][1]->SetMaximum(700.0);
  h1_arr[0][1]->SetMinimum(1.0);
  leg01->Draw();
  h1_arr[0][1]->GetXaxis()->SetTitle("Distance form the axis of the shower, km");
  h1_arr[0][1]->GetYaxis()->SetTitle("Cherenkov photon density, m^{-2}");

  //
  Int_t nnMax = 1000;
  Double_t lam_NUV[nnMax];
  Double_t lam_RGB[nnMax];
  Double_t qe_NUV[nnMax];
  Double_t qe_RGB[nnMax];
  Int_t nn_NUV;
  Int_t nn_RGB;
  //  
  loadPDE_formFile("./PDE_NUVHD_3.90V_Pxt_15.dat", lam_NUV, qe_NUV, nn_NUV);
  loadPDE_formFile("./PDE_in_RGB_SiPMs_ASD-RGB.dat", lam_RGB, qe_RGB, nn_RGB);
  //
  TGraph *gr_NUV = new TGraph(nn_NUV, lam_NUV, qe_NUV);
  TGraph *gr_RGB = new TGraph(nn_RGB, lam_RGB, qe_RGB);
  
  TH1D *h1_wl_NUV[3];
  TH1D *h1_wl_RGB[3];
  for(Int_t jj = 0;jj<3;jj++){
    h1_wl_NUV[jj] = new TH1D(*h1_arr[jj][0]);
    h1_wl_RGB[jj] = new TH1D(*h1_arr[jj][0]);
    conv_with_PDE(h1_wl_NUV[jj],h1_arr[jj][0],gr_NUV);
    conv_with_PDE(h1_wl_RGB[jj],h1_arr[jj][0],gr_RGB);
    cout<<h1_arr[jj][0]->Integral()<<" ---> "<<h1_wl_NUV[jj]->Integral()<<" ---> "<<h1_wl_RGB[jj]->Integral()<<endl;    
  }

  TCanvas *c31 = new TCanvas("c31","c31",10,10,1600,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gPad->SetLogy();
  //gStyle->SetOptStat(kFALSE);
  //
  c31->SetRightMargin(0.03);
  c31->SetLeftMargin(0.09);
  c31->SetTopMargin(0.02);
  c31->SetBottomMargin(0.09);
  c31->Divide(2,1);
  c31->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  Int_t iii = 0;
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(h1_wl_NUV[iii], "NuV", "pl");
  leg->AddEntry(h1_wl_RGB[iii], "RGB", "pl");
  //leg->AddEntry(h1_wl_NUV[iii], "NuV @ 30 km", "pl");
  //leg->AddEntry(h1_wl_RGB[iii], "RGB @ 30 km", "pl");
  //leg->AddEntry(h1_wl_NUV[0], "NuV @ 20 km", "pl");
  //leg->AddEntry(h1_wl_RGB[0], "RGB @ 20 km", "pl");
  //
  //
  //Double_t norm;
  //norm = h1_wl_NUV[iii]->GetBinContent(h1_wl_NUV[iii]->GetMaximumBin());
  //makeNormTH1D(h1_wl_NUV[iii], norm);
  //norm = h1_wl_RGB[iii]->GetBinContent(h1_wl_RGB[iii]->GetMaximumBin());
  //makeNormTH1D(h1_wl_RGB[iii], norm);
  //
  //
  h1_wl_NUV[iii]->SetMinimum(0.0);
  h1_wl_NUV[iii]->SetMaximum(0.014);
  h1_wl_NUV[iii]->SetLineColor(kBlack);
  h1_wl_RGB[iii]->SetLineColor(kRed);
  //h1_wl_NUV[0]->SetLineColor(kBlue);
  //h1_wl_RGB[0]->SetLineColor(kMagenta);
  //h1_wl_NUV[0]->SetLineWidth(3.0);
  //h1_wl_RGB[0]->SetLineWidth(3.0);
  h1_wl_NUV[iii]->SetLineWidth(3.0);
  h1_wl_RGB[iii]->SetLineWidth(3.0);

  h1_wl_NUV[iii]->SetTitle("");
  h1_wl_NUV[iii]->GetXaxis()->SetTitle("Wavelength, nm");
  h1_wl_NUV[iii]->GetYaxis()->SetTitle("a.u.");
  h1_wl_NUV[iii]->Draw();
  h1_wl_RGB[iii]->Draw("sames");
  //h1_wl_NUV[0]->Draw("sames");
  //h1_wl_RGB[0]->Draw("sames");
  leg->Draw();
  //
  c31->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  //
  TGraph *gr_NGB_NUV = new TGraph();
  TGraph *gr_NGB_RGB = new TGraph();
  load_NGB_formFile("./cumulativeSumOftheNightGlowBackground_NUV.dat", gr_NGB_NUV);
  load_NGB_formFile("./cumulativeSumOftheNightGlowBackground_RGB.dat", gr_NGB_RGB);
  //
  //
  TH1D *h1_Wavelength_integral_NUV = new TH1D(*h1_wl_NUV[iii]);
  TH1D *h1_Wavelength_integral_RGB = new TH1D(*h1_wl_RGB[iii]);
  IntegrateInWavelength(h1_Wavelength_integral_NUV, h1_wl_NUV[iii]);
  IntegrateInWavelength(h1_Wavelength_integral_RGB, h1_wl_RGB[iii]);

  //divideOnBackground(h1_Wavelength_integral_NUV, gr_NGB_NUV);
  //divideOnBackground(h1_Wavelength_integral_RGB, gr_NGB_RGB);


  h1_Wavelength_integral_NUV->SetLineColor(kBlack);
  h1_Wavelength_integral_RGB->SetLineColor(kRed);
  h1_Wavelength_integral_NUV->SetLineWidth(3.0);
  h1_Wavelength_integral_RGB->SetLineWidth(3.0);
  //
  h1_Wavelength_integral_NUV->SetMaximum(0.3);
  h1_Wavelength_integral_RGB->SetMaximum(0.3);
  //  h1_Wavelength_integral_NUV->SetTitle("S/#sqrt{S+B}");
  h1_Wavelength_integral_NUV->SetTitle("");
  h1_Wavelength_integral_NUV->GetXaxis()->SetTitle("Wavelength, nm");
  h1_Wavelength_integral_NUV->GetYaxis()->SetTitle("Comulative sum");
  h1_Wavelength_integral_NUV->Draw();
  h1_Wavelength_integral_RGB->Draw("sames");

  leg->Draw();
  
  //
  //
  //
  compare_PDE_NUV_RGB();
  //
  //
  //

  return 0;
}

void IntegrateInTime(TH1D *h1_time_integral, TH1D *h1_time){
  //for(Int_t i = 0;i<h1_time->GetNbinsX();i++)
  //h1_time_integral->SetBinContent(i,h1_time->Integral(0,i)/h1_time->Integral("width"));
  for(Int_t i = 0;i<h1_time->GetNbinsX();i++)
    h1_time_integral->SetBinContent(i,h1_time->Integral(0,i)/h1_time->Integral(0,h1_time->GetNbinsX()));
  //for(Int_t i = 0;i<h1_time->GetNbinsX();i++)
  //h1_time->SetBinContent(i,h1_time->GetBinContent(i)/5.0);
}

void IntegrateInWavelength(TH1D *h1_Wavelength_integral, TH1D *h1_to_integrate){
  for(Int_t i = 0;i<h1_to_integrate->GetNbinsX();i++)
    h1_Wavelength_integral->SetBinContent(i,h1_to_integrate->Integral(0,i));
}

void conv_with_PDE( TH1D *h1_wl_pde, TH1D *h1_wl, TGraph *gr_PDE){
  for(Int_t i = 1;i<=h1_wl->GetNbinsX();i++)
    h1_wl_pde->SetBinContent(i,h1_wl->GetBinContent(i)*gr_PDE->Eval(h1_wl->GetBinCenter(i)));
}

void conv_with_const( TH1D *h1_out, TH1D *h1_in, Double_t val){
  for(Int_t i = 1;i<=h1_in->GetNbinsX();i++)
    h1_out->SetBinContent(i,h1_in->GetBinContent(i)*val);
}

void loadPDE_formFile(TString fileName, Double_t *xx, Double_t *yy, Int_t &nn){
  ifstream fileIn(fileName.Data());
  Double_t x;
  Double_t y;
  Double_t ymax = 0.0;
  Int_t i = 0;
  if(fileIn.is_open()){
    while(fileIn>>x>>y){
      xx[i] = x;
      yy[i] = y;
      if(ymax<y)
	ymax = y;
      i++;
    }
    fileIn.close();
  }
  else
    cout<<"Unable to open file"<<endl;
  nn = i;
  //for(Int_t jj = 0;jj<nn;jj++)
  //yy[jj] = yy[jj]/ymax;
}

void compare_PDE_NUV_RGB(){
  //
  Int_t nnMax = 1000;
  Double_t lam_NUV[nnMax];
  Double_t lam_RGB[nnMax];
  Double_t qe_NUV[nnMax];
  Double_t qe_RGB[nnMax];
  Int_t nn_NUV;
  Int_t nn_RGB;
  //  
  loadPDE_formFile("./PDE_NUVHD_3.90V_Pxt_15.dat", lam_NUV, qe_NUV, nn_NUV);
  loadPDE_formFile("./PDE_in_RGB_SiPMs_ASD-RGB.dat", lam_RGB, qe_RGB, nn_RGB);
  //
  TCanvas *cxx01 = new TCanvas("cxx01","cxx01",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  //
  cxx01->SetRightMargin(0.03);
  cxx01->SetLeftMargin(0.09);
  cxx01->SetTopMargin(0.02);
  cxx01->SetBottomMargin(0.09);
  //
  TGraph *gr_NUV = new TGraph();
  TGraph *gr_RGB = new TGraph();

  //
  gr_NUV->SetLineColor(kBlack);
  gr_NUV->SetLineWidth(2.0);
  gr_NUV->SetMarkerStyle(20);
  gr_NUV->SetMarkerColor(kBlack);
  //

  //
  gr_RGB->SetLineColor(kRed);
  gr_RGB->SetLineWidth(2.0);
  gr_RGB->SetMarkerStyle(21);
  gr_RGB->SetMarkerColor(kRed);
  //

  for(Int_t i = 0;i<nn_NUV;i++)
    gr_NUV->SetPoint(gr_NUV->GetN(),lam_NUV[i], qe_NUV[i]);
  for(Int_t i = 0;i<nn_RGB;i++)
    gr_RGB->SetPoint(gr_RGB->GetN(),lam_RGB[i], qe_RGB[i]);

  //
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_NUV);
  mg->Add(gr_RGB);  

  mg->GetXaxis()->SetTitle("Wavelength, nm");
  mg->GetYaxis()->SetTitle("Photon detection efficiency");

  mg->GetXaxis()->SetLimits(200,1100);
  mg->Draw("APL");
  
  mg->SetMinimum(0.0);
  mg->SetMaximum(0.55);
  //mg->SetMaximum(1.1);

  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_NUV, "NuV", "pl");
  leg->AddEntry(gr_RGB, "RGB", "pl");
  leg->Draw();
}

void makeNormTH1D(TH1D *h1, Double_t norm){
  for(Int_t i = 0;i<=h1->GetNbinsX();i++)
    h1->SetBinContent(i,h1->GetBinContent(i)/norm);
}

void divideOnBackground(TH1D *h1, TGraph *gr){
  for(Int_t i = 0;i<=h1->GetNbinsX();i++){
    Double_t norm = gr->Eval(h1->GetBinCenter(i)) + h1->GetBinContent(i);
    //Double_t norm = gr->Eval(h1->GetBinCenter(i));
    if(norm>0 && h1->GetBinContent(i)>0 && h1->GetBinCenter(i)>315)
      h1->SetBinContent(i,h1->GetBinContent(i)/TMath::Sqrt(norm));
    else
      h1->SetBinContent(i,0);
  }
}

void load_NGB_formFile(TString fileName, TGraph *gr){
  ifstream fileIn(fileName.Data());
  Double_t x;
  Double_t y;
  if(fileIn.is_open()){
    while(fileIn>>x>>y){
      gr->SetPoint(gr->GetN(),x,y);
    }
    fileIn.close();
  }
  else
    cout<<"Unable to open file"<<endl;
}
