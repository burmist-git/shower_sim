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

Int_t plots(){
  //
  TString fileN01;
  TString fileN02;
  fileN01 = "./hist/hist_Proton_100PeV_33km_85.root";
  fileN02 = "./hist/hist_Proton_100PeV_525km_67_7.root";
  TFile *f01 = new TFile(fileN01.Data());
  TFile *f02 = new TFile(fileN02.Data());
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
  //
  //--------------------------------------------------
  TLegend *leg01 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg01->AddEntry(h1_01_1, "@: 100 PeV,  33 km, 85.0^{o}", "l");
  leg01->AddEntry(h1_02_1, "@: 100 PeV, 525 km, 67.7^{o}", "l");
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  //
  h1_01_1->Draw();
  h1_02_1->Draw("sames");
  leg01->Draw();
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
  h1_02_2->Draw();
  h1_01_2->Draw("sames");
  h1_02_2->SetMaximum(100);
  leg01->Draw();
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
  h1_01_5->Draw();
  h1_02_5->Draw("sames");
  leg01->Draw();
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
