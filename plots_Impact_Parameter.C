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

void IntegrateInTime(TH1D *h1_time_integral, TH1D *h1_time);
void loadPDE_formFile(TString fileName, Double_t *xx, Double_t *yy, Int_t &nn);
void conv_with_PDE( TH1D *h1_wl_pde, TH1D *h1_wl, TGraph *gr_PDE);
void conv_with_const( TH1D *h1_out, TH1D *h1_in, Double_t val);

void compare_PDE_NUV_RGB();

Int_t plots_Impact_Parameter(){
  //
  // hist_Proton_100PeV_33km_85.root
  // hist_Proton_100PeV_525km_67_7.root
  // hist_0km_Impact_Parameter.root
  // hist_5km_Impact_Parameter.root
  // hist_10km_Impact_Parameter.root
  // hist_15km_Impact_Parameter.root
  // hist_20km_Impact_Parameter.root
  // hist_25km_Impact_Parameter.root
  // hist_30km_Impact_Parameter.root
  //
  TString leg01Lable_01;
  TString leg01Lable_02;
  TString leg01Lable_03;
  TString leg01Lable_04;
  TString leg01Lable_05;
  TString leg01Lable_06;
  TString leg01Lable_07;
  TString fileN01;
  TString fileN02;
  TString fileN03;
  TString fileN04;
  TString fileN05;
  TString fileN06;
  TString fileN07;
  //
  //leg01Lable_01 = "@: 100 PeV,  33 km, 85.0^{o}";
  //leg01Lable_02 = "@: 100 PeV, 525 km, 67.7^{o}";
  //fileN01 = "./hist/hist_Proton_100PeV_33km_85.root";
  //fileN02 = "./hist/hist_Proton_100PeV_525km_67_7.root";
  //
  //leg01Lable_01 = "@: 100 PeV, 525 km, 67.7^{o}";
  //leg01Lable_02 = "@: 30km Impact Parameter";
  //fileN01 = "./hist/hist_Proton_100PeV_525km_67_7.root";
  //fileN02 = "./hist/hist_30km_Impact_Parameter.root";
  //
  leg01Lable_01 = "@: 0km Impact Parameter";
  leg01Lable_02 = "@: 5km Impact Parameter";
  leg01Lable_03 = "@: 10km Impact Parameter";
  leg01Lable_04 = "@: 15km Impact Parameter";
  leg01Lable_05 = "@: 20km Impact Parameter";
  leg01Lable_06 = "@: 25km Impact Parameter";
  leg01Lable_07 = "@: 30km Impact Parameter";
  //
  fileN01 = "./hist/hist_0km_Impact_Parameter.root";
  fileN02 = "./hist/hist_5km_Impact_Parameter.root";
  fileN03 = "./hist/hist_10km_Impact_Parameter.root";
  fileN04 = "./hist/hist_15km_Impact_Parameter.root";
  fileN05 = "./hist/hist_20km_Impact_Parameter.root";
  fileN06 = "./hist/hist_25km_Impact_Parameter.root";
  fileN07 = "./hist/hist_30km_Impact_Parameter.root";
  //
  TFile *f01 = new TFile(fileN01.Data());
  TFile *f02 = new TFile(fileN02.Data());
  TFile *f03 = new TFile(fileN03.Data());
  TFile *f04 = new TFile(fileN04.Data());
  TFile *f05 = new TFile(fileN05.Data());
  TFile *f06 = new TFile(fileN06.Data());
  TFile *f07 = new TFile(fileN07.Data());
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
  TH1D *h1_04_1 = (TH1D*)f04->Get("h1_wavelength");
  TH1D *h1_04_2 = (TH1D*)f04->Get("h1_distance");
  TH1D *h1_04_3 = (TH1D*)f04->Get("h1_time_offset");
  TH1D *h1_04_4 = (TH1D*)f04->Get("h1_angle_offset");
  TH1D *h1_04_5 = (TH1D*)f04->Get("h1_timeHist");
  TH1D *h1_04_6 = (TH1D*)f04->Get("h1_angleHist");
  //
  TH1D *h1_05_1 = (TH1D*)f05->Get("h1_wavelength");
  TH1D *h1_05_2 = (TH1D*)f05->Get("h1_distance");
  TH1D *h1_05_3 = (TH1D*)f05->Get("h1_time_offset");
  TH1D *h1_05_4 = (TH1D*)f05->Get("h1_angle_offset");
  TH1D *h1_05_5 = (TH1D*)f05->Get("h1_timeHist");
  TH1D *h1_05_6 = (TH1D*)f05->Get("h1_angleHist");
  //
  TH1D *h1_06_1 = (TH1D*)f06->Get("h1_wavelength");
  TH1D *h1_06_2 = (TH1D*)f06->Get("h1_distance");
  TH1D *h1_06_3 = (TH1D*)f06->Get("h1_time_offset");
  TH1D *h1_06_4 = (TH1D*)f06->Get("h1_angle_offset");
  TH1D *h1_06_5 = (TH1D*)f06->Get("h1_timeHist");
  TH1D *h1_06_6 = (TH1D*)f06->Get("h1_angleHist");
  //
  TH1D *h1_07_1 = (TH1D*)f07->Get("h1_wavelength");
  TH1D *h1_07_2 = (TH1D*)f07->Get("h1_distance");
  TH1D *h1_07_3 = (TH1D*)f07->Get("h1_time_offset");
  TH1D *h1_07_4 = (TH1D*)f07->Get("h1_angle_offset");
  TH1D *h1_07_5 = (TH1D*)f07->Get("h1_timeHist");
  TH1D *h1_07_6 = (TH1D*)f07->Get("h1_angleHist");
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
  h1_arr[3][0] = h1_04_1;
  h1_arr[3][1] = h1_04_2;
  h1_arr[3][2] = h1_04_3;
  h1_arr[3][3] = h1_04_4;
  h1_arr[3][4] = h1_04_5;
  h1_arr[3][5] = h1_04_6;
  //
  h1_arr[4][0] = h1_05_1;
  h1_arr[4][1] = h1_05_2;
  h1_arr[4][2] = h1_05_3;
  h1_arr[4][3] = h1_05_4;
  h1_arr[4][4] = h1_05_5;
  h1_arr[4][5] = h1_05_6;
  //
  h1_arr[5][0] = h1_06_1;
  h1_arr[5][1] = h1_06_2;
  h1_arr[5][2] = h1_06_3;
  h1_arr[5][3] = h1_06_4;
  h1_arr[5][4] = h1_06_5;
  h1_arr[5][5] = h1_06_6;
  //
  h1_arr[6][0] = h1_07_1;
  h1_arr[6][1] = h1_07_2;
  h1_arr[6][2] = h1_07_3;
  h1_arr[6][3] = h1_07_4;
  h1_arr[6][4] = h1_07_5;
  h1_arr[6][5] = h1_07_6;
  //
  for(Int_t ii = 0;ii<7;ii++){
    for(Int_t jj = 0;jj<6;jj++){
      h1_arr[ii][jj]->SetLineWidth(3.0);
      if(ii == 0)
	h1_arr[ii][jj]->SetLineColor(kBlack);
      if(ii == 1)
	h1_arr[ii][jj]->SetLineColor(kBlue);
      if(ii == 2)
	h1_arr[ii][jj]->SetLineColor(kRed);
      if(ii == 3)
	h1_arr[ii][jj]->SetLineColor(kMagenta);
      if(ii == 4)
	h1_arr[ii][jj]->SetLineColor(kGreen+2);
      if(ii == 5)
	h1_arr[ii][jj]->SetLineColor(kRed+2);
      if(ii == 6)
	h1_arr[ii][jj]->SetLineColor(kBlue+2);
    }
  }
  /*
  h1_01_1->SetLineColor(kBlack);
  h1_01_1->SetLineWidth(3.0);
  h1_01_2->SetLineColor(kBlack);
  h1_01_2->SetLineWidth(3.0);
  h1_01_3->SetLineColor(kBlack);
  h1_01_3->SetLineWidth(3.0);
  h1_01_4->SetLineColor(kBlack);
  h1_01_4->SetLineWidth(3.0);
  h1_01_5->SetLineColor(kBlack);
  h1_01_5->SetLineWidth(3.0);
  h1_01_6->SetLineColor(kBlack);
  h1_01_6->SetLineWidth(3.0);
  //
  h1_02_1->SetLineColor(kRed);
  h1_02_1->SetLineWidth(3.0);
  h1_02_2->SetLineColor(kRed);
  h1_02_2->SetLineWidth(3.0);
  h1_02_3->SetLineColor(kRed);
  h1_02_3->SetLineWidth(3.0);
  h1_02_4->SetLineColor(kRed);
  h1_02_4->SetLineWidth(3.0);
  h1_02_5->SetLineColor(kRed);
  h1_02_5->SetLineWidth(3.0);
  h1_02_6->SetLineColor(kRed);
  h1_02_6->SetLineWidth(3.0);
  */
  //
  //--------------------------------------------------
  TLegend *leg01 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg01->AddEntry(h1_01_1, leg01Lable_01.Data(), "l");
  leg01->AddEntry(h1_02_1, leg01Lable_02.Data(), "l");
  leg01->AddEntry(h1_03_1, leg01Lable_03.Data(), "l");
  leg01->AddEntry(h1_04_1, leg01Lable_04.Data(), "l");
  leg01->AddEntry(h1_05_1, leg01Lable_05.Data(), "l");
  leg01->AddEntry(h1_06_1, leg01Lable_06.Data(), "l");
  leg01->AddEntry(h1_07_1, leg01Lable_07.Data(), "l");
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  //
  h1_arr[0][0]->SetTitle("");
  h1_arr[0][0]->SetName("0km");
  h1_arr[1][0]->SetName("5km");
  h1_arr[2][0]->SetName("10km");
  h1_arr[3][0]->SetName("15km");
  h1_arr[4][0]->SetName("20km");
  h1_arr[5][0]->SetName("25km");
  h1_arr[6][0]->SetName("30km");
  h1_arr[0][0]->Draw();
  for(Int_t jj = 1;jj<7;jj++)
    h1_arr[jj][0]->Draw("sames");
  h1_arr[0][0]->SetMaximum(0.02);
  h1_arr[0][0]->SetMinimum(0.0);
  leg01->Draw();
  h1_arr[0][0]->GetXaxis()->SetTitle("Photon wavelenght, nm");
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
  //
  h1_arr[0][1]->SetTitle("");
  h1_arr[0][1]->SetName("0km");
  h1_arr[1][1]->SetName("5km");
  h1_arr[2][1]->SetName("10km");
  h1_arr[3][1]->SetName("15km");
  h1_arr[4][1]->SetName("20km");
  h1_arr[5][1]->SetName("25km");
  h1_arr[6][1]->SetName("30km");
  h1_arr[0][1]->Draw();
  for(Int_t jj = 1;jj<7;jj++)
    h1_arr[jj][1]->Draw("sames");
  h1_arr[0][1]->SetMaximum(700.0);
  h1_arr[0][1]->SetMinimum(0.01);
  leg01->Draw();
  h1_arr[0][1]->GetXaxis()->SetTitle("distance, km");
  /*
  //--------------------------------------------------
  TCanvas *c3 = new TCanvas("c3","c3",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  //
  h1_02_3->Draw();
  h1_01_3->Draw("sames");
  h1_02_3->GetXaxis()->SetTitle("ns");
  leg01->Draw();
  //--------------------------------------------------
  TCanvas *c4 = new TCanvas("c4","c4",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  //
  h1_02_4->Draw();
  h1_01_4->Draw("sames");
  leg01->Draw();
  */
  //--------------------------------------------------
  TCanvas *c5 = new TCanvas("c5","c5",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogx();
  //
  //
  h1_arr[0][4]->SetTitle("");
  h1_arr[0][4]->SetName("0km");
  h1_arr[1][4]->SetName("5km");
  h1_arr[2][4]->SetName("10km");
  h1_arr[3][4]->SetName("15km");
  h1_arr[4][4]->SetName("20km");
  h1_arr[5][4]->SetName("25km");
  h1_arr[6][4]->SetName("30km");
  h1_arr[0][4]->Draw();
  for(Int_t jj = 1;jj<7;jj++)
    h1_arr[jj][4]->Draw("sames");
  h1_arr[0][4]->SetMinimum(1.0e-16);
  h1_arr[0][4]->SetMaximum(1.0e+1);
  leg01->Draw();
  cout<<" h1_arr[6][4]->Integral "<<h1_arr[6][4]->Integral("width")<<endl;
  cout<<" h1_arr[6][4]->Integral "<<h1_arr[6][4]->Integral()<<endl;
  //////////////////////////////////////////////////////
  TH1D *h1_time_integral[7];
  for(Int_t jj = 0;jj<7;jj++){
    h1_time_integral[jj] = new TH1D(*h1_arr[jj][4]);
    IntegrateInTime(h1_time_integral[jj],h1_arr[jj][4]);
  }
  //--------------------------------------------------
  TCanvas *c6 = new TCanvas("c6","c6",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogx();
  //
  //
  h1_time_integral[0]->SetTitle("");
  h1_time_integral[0]->SetName("0km");
  h1_time_integral[1]->SetName("5km");
  h1_time_integral[2]->SetName("10km");
  h1_time_integral[3]->SetName("15km");
  h1_time_integral[4]->SetName("20km");
  h1_time_integral[5]->SetName("25km");
  h1_time_integral[6]->SetName("30km");
  h1_time_integral[0]->Draw();
  for(Int_t jj = 1;jj<7;jj++)
    h1_time_integral[jj]->Draw("sames");
  h1_time_integral[0]->SetMinimum(0.0);
  h1_time_integral[0]->SetMaximum(1.1);
  leg01->Draw();
  //////////////////////////////////////////////////////
  //
  Int_t nnMax = 1000;
  Double_t xx[nnMax];
  Double_t yy[nnMax];
  Int_t nn;
  //  
  loadPDE_formFile("./PDE_NUVHD_3.90V_Pxt_15.dat", xx, yy, nn);
  //loadPDE_formFile("./PDE_in_RGB_SiPMs_ASD-RGB.dat", xx, yy, nn);
  cout<<"nn "<<nn<<endl;
  //
  //--------------------------------------------------
  TCanvas *c7 = new TCanvas("c7","c7",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  gPad->SetGridx();
  gPad->SetGridy();
  TGraph *gr_pde = new TGraph(nn,xx,yy);
  //cout<<"gr_pde->Eval(305) = "<<gr_pde->Eval(305)<<endl;
  gr_pde->Draw("APL");


  //////////////////////////////////////////////////////
  TH1D *h1_wl_pde[7];
  for(Int_t jj = 0;jj<7;jj++){
    h1_wl_pde[jj] = new TH1D(*h1_arr[jj][0]);
    conv_with_PDE(h1_wl_pde[jj],h1_arr[jj][0],gr_pde);
    cout<<h1_arr[jj][0]->Integral("width")<<" ---> "<<h1_wl_pde[jj]->Integral("width")<<endl;    
  }
  //--------------------------------------------------
  //

  TCanvas *c8 = new TCanvas("c8","c8",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kTRUE);
  gPad->SetGridx();
  gPad->SetGridy();
  //
  //h1_arr[0][0]->SetTitle("");
  //h1_arr[0][0]->SetName("0km");
  //h1_arr[1][0]->SetName("5km");
  //h1_arr[2][0]->SetName("10km");
  //h1_arr[3][0]->SetName("15km");
  //h1_arr[4][0]->SetName("20km");
  //h1_arr[5][0]->SetName("25km");
  //h1_arr[6][0]->SetName("30km");
  //h1_arr[0][0]->Draw();
  h1_wl_pde[0]->SetMaximum(0.002);
  h1_wl_pde[0]->Draw();
  for(Int_t jj = 1;jj<7;jj++)
    h1_wl_pde[jj]->Draw("sames");
  //h1_arr[0][0]->SetMaximum(0.02);
  //h1_arr[0][0]->SetMinimum(0.0);
  leg01->Draw();
  //h1_arr[0][0]->GetXaxis()->SetTitle("Photon wavelenght, nm");
  //

  
  //////////////////////////////////////////////////////
  TH1D *h1_r_pde[7];
  for(Int_t jj = 0;jj<7;jj++){
    h1_r_pde[jj] = new TH1D(*h1_arr[jj][1]);
    conv_with_const(h1_r_pde[jj],h1_arr[jj][1],h1_wl_pde[jj]->Integral("width"));
  }
  //--------------------------------------------------
  TCanvas *c9 = new TCanvas("c9","c9",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  h1_r_pde[0]->SetMaximum(200.0);
  h1_r_pde[0]->SetMinimum(0.001);
  h1_r_pde[0]->Draw();
  for(Int_t jj = 1;jj<7;jj++)
    h1_r_pde[jj]->Draw("sames");
  //h1_arr[0][0]->SetMaximum(0.02);
  //h1_arr[0][0]->SetMinimum(0.0);
  leg01->Draw();
  //h1_arr[0][0]->GetXaxis()->SetTitle("Photon wavelenght, nm");

  //
  //
  //
  compare_PDE_NUV_RGB();
  //
  //
  //
  
  
  //h1_arr[0][4]->GetXaxis()->SetTitle("Photon wavelenght, nm");
  /*
  //--------------------------------------------------
  TCanvas *c6 = new TCanvas("c6","c6",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogx();
  //
  h1_01_6->Draw();
  h1_02_6->Draw("sames");
  leg01->Draw();
  */


  /*
  //
  TCanvas *ctot = new TCanvas("ctot","ctot",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogx();
  h1_arr[6][4]->Draw();
  h1_time_integral[6]->Draw("sames");
  //h1_arr[0][0]->Draw();
  */
  
  //h1_02_2->GetXaxis()->SetLimits(0.0,200);
  //h1_02_2->GetXaxis()->SetRangeUser(0.0,200.0);

  //
  //h2_1->GetXaxis()->SetTitle("Primary position x, mm");
  //h2_1->GetYaxis()->SetTitle("Primary position y, mm");
  //h1_2->GetXaxis()->SetTitle("Primary #theta, deg");
  //h1_3->GetXaxis()->SetTitle("Primary #phi, deg");
  //h1_4->GetXaxis()->SetTitle("x in projection plane, mm");
  //
  //h2_1->GetXaxis()->SetRangeUser(-0.13,-0.12);

  //TString filePdfN = fileN;
  //TString fileEpsN = fileN;
  //TString filePngN = fileN;
  // filePdfN += ".pdf";
  //fileEpsN += ".eps";
  //filePngN += ".png";

  //c1->SaveAs(filePdfN.Data());
  //c1->SaveAs(fileEpsN.Data());
  //c1->SaveAs(filePngN.Data());
  
  /*
  for(i = 0;i<nChannels;i++){
    h1_Arr[i]->SetLineColor(colorArr[i]);
    h1_Arr[i]->SetLineWidth(3.0);
    if(i == 0){
      h1_Arr[i]->Draw();
      h1_Arr[i]->GetXaxis()->SetTitle("Value, Unit");
      //h1_1->GetXaxis()->SetRangeUser(-0.13,-0.12);
    }
    else
      h1_Arr[i]->Draw("same");
  }

  //h1_1->Fit("gaus");
  TString legInfo;
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  for(i = 0;i<nChannels;i++){
    legInfo = "ch ";legInfo += i;
    leg->AddEntry(h1_Arr[i], legInfo.Data(), "l");
  }
  leg->Draw();
  */


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
  Int_t i = 0;
  if(fileIn.is_open()){
    while(fileIn>>x>>y){
      xx[i] = x;
      yy[i] = y;
      i++;
    }
    fileIn.close();
  }
  else
    cout<<"Unable to open file"<<endl;
  nn = i;
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

  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_NUV, "NuV", "pl");
  leg->AddEntry(gr_RGB, "RGB", "pl");
  leg->Draw();
}
