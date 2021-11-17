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

Double_t ozone_crossection(Double_t *x, Double_t *par){
  //
  Double_t A1   = par[0];
  Double_t x01  = par[1];
  Double_t sig1 = par[2];
  //
  Double_t A2   = par[3];
  Double_t x02  = par[4];
  Double_t sig2 = par[5];
  //
  Double_t A3   = par[6];
  Double_t x03  = par[7];
  Double_t sig3 = par[8];
  //
  Double_t A4   = par[9];
  Double_t x04  = par[10];
  Double_t sig4 = par[11];
  //
  Double_t K    = par[12];
  Double_t C    = par[13];
  //
  Double_t val = A1*TMath::Exp(-1.0/2.0/sig1/sig1*(x[0]-x01)*(x[0]-x01)) +
    A2*TMath::Exp(-1.0/2.0/sig2/sig2*(x[0]-x02)*(x[0]-x02)) +
    A3*TMath::Exp(-1.0/2.0/sig3/sig3*(x[0]-x03)*(x[0]-x03)) +
    A4*TMath::Exp(-1.0/2.0/sig4/sig4*(x[0]-x04)*(x[0]-x04)) + x[0]*K + C;
  return val;
}

Double_t one_gauss(Double_t *x, Double_t *par){
  //
  Double_t A1   = par[0];
  Double_t x01  = par[1];
  Double_t sig1 = par[2];
  return A1*TMath::Exp(-1.0/2.0/sig1/sig1*(x[0]-x01)*(x[0]-x01));
}
  
Int_t plots_ozone(){
  //
  TString fileN;
  fileN = "./ozone/ozone_crossection_02.csv";
  //
  Double_t wl_min  = 200;
  Double_t wl_max  = 1100;
  Double_t fit_gauss_01_min = 200;
  Double_t fit_gauss_01_max = 320;
  const Int_t npar = 14;
  //
  TGraph *gr1 = new TGraph();
  TGraph *gr2 = new TGraph();
  TGraph *gr3 = new TGraph();
  TGraph *gr4 = new TGraph();
  TGraphErrors *grall = new TGraphErrors();
  TGraph *gr_nofit = new TGraph();
  gr1->SetName("");
  gr2->SetName("");
  gr3->SetName("");
  gr4->SetName("");
  grall->SetName("");
  gr_nofit->SetName("");
  Double_t x,y;
  ifstream fileIn(fileN.Data());
  if (fileIn.is_open()) {
    while ( fileIn>>x>>y ) {
      if(x>=fit_gauss_01_min && x<=fit_gauss_01_max)
	gr1->SetPoint(gr1->GetN(),x,y);
      gr2->SetPoint(gr2->GetN(),x,y);
      gr3->SetPoint(gr3->GetN(),x,y);
      gr4->SetPoint(gr4->GetN(),x,y);
      Int_t ii = grall->GetN();
      grall->SetPoint(ii,x,y);
      grall->SetPointError(ii,1,(y*0.03 + 1.0e-18*0.00001));
      gr_nofit->SetPoint(gr_nofit->GetN(),x,y);
    }
    fileIn.close();
  }
  else cout<<"Unable to open file"<<endl; 
  ///////////////////////////////////////
  //
  gr1->Fit("gaus","","",fit_gauss_01_min, fit_gauss_01_max);
  TF1 *f_git_gaus1 = (TF1*)gr1->GetListOfFunctions()->FindObject("gaus");
  gr2->Fit("gaus","","",400, 650);
  TF1 *f_git_gaus2 = (TF1*)gr2->GetListOfFunctions()->FindObject("gaus");
  gr3->Fit("gaus","","",700, 1000);
  TF1 *f_git_gaus3 = (TF1*)gr3->GetListOfFunctions()->FindObject("gaus");
  gr4->Fit("gaus","","",900, 1100);
  TF1 *f_git_gaus4 = (TF1*)gr4->GetListOfFunctions()->FindObject("gaus");
  //
  Double_t inParameters[npar];
  f_git_gaus1->GetParameters(&inParameters[0]);
  f_git_gaus2->GetParameters(&inParameters[3]);
  f_git_gaus3->GetParameters(&inParameters[6]);
  f_git_gaus4->GetParameters(&inParameters[9]);
  inParameters[12] = 0;
  inParameters[13] = 0;
  //
  TF1 *f_ozone_crossection = new TF1("f_ozone_crossection",ozone_crossection,wl_min,wl_max,npar);
  TF1 *f_one_gauss01 = new TF1("f_one_gauss01",one_gauss,wl_min,wl_max,npar);
  TF1 *f_one_gauss02 = new TF1("f_one_gauss02",one_gauss,wl_min,wl_max,npar);
  TF1 *f_one_gauss03 = new TF1("f_one_gauss03",one_gauss,wl_min,wl_max,npar);
  TF1 *f_one_gauss04 = new TF1("f_one_gauss04",one_gauss,wl_min,wl_max,npar);
  f_ozone_crossection->SetParameters(inParameters);
  Double_t aa = 0.0;
  //f_ozone_crossection->SetParameter(0,);
  //f_ozone_crossection->FixParameter(0,inParameters[0]);
  //f_ozone_crossection->FixParameter(1,inParameters[1]);
  //f_ozone_crossection->FixParameter(2,inParameters[2]);
  //f_ozone_crossection->FixParameter(3,inParameters[3]);
  //f_ozone_crossection->FixParameter(4,inParameters[4]);
  //f_ozone_crossection->FixParameter(5,inParameters[5]);
  //f_ozone_crossection->FixParameter(6,inParameters[6]);
  //f_ozone_crossection->FixParameter(7,inParameters[7]);
  //f_ozone_crossection->FixParameter(8,inParameters[8]);
  //f_ozone_crossection->FixParameter(9,inParameters[9]);
  //f_ozone_crossection->FixParameter(10,inParameters[10]);
  //f_ozone_crossection->FixParameter(11,inParameters[11]);
  f_ozone_crossection->FixParameter(12,inParameters[12]);
  f_ozone_crossection->FixParameter(13,inParameters[13]);
  grall->Fit("f_ozone_crossection","","",wl_min,wl_max);
  TF1 *f_fit_all = (TF1*)grall->GetListOfFunctions()->FindObject("f_ozone_crossection");
  //
  f_one_gauss01->SetParameter(0,f_fit_all->GetParameter(0));
  f_one_gauss01->SetParameter(1,f_fit_all->GetParameter(1));
  f_one_gauss01->SetParameter(2,f_fit_all->GetParameter(2));
  f_one_gauss02->SetParameter(0,f_fit_all->GetParameter(3));
  f_one_gauss02->SetParameter(1,f_fit_all->GetParameter(4));
  f_one_gauss02->SetParameter(2,f_fit_all->GetParameter(5));
  f_one_gauss03->SetParameter(0,f_fit_all->GetParameter(6));
  f_one_gauss03->SetParameter(1,f_fit_all->GetParameter(7));
  f_one_gauss03->SetParameter(2,f_fit_all->GetParameter(8));
  f_one_gauss04->SetParameter(0,f_fit_all->GetParameter(9));
  f_one_gauss04->SetParameter(1,f_fit_all->GetParameter(10));
  f_one_gauss04->SetParameter(2,f_fit_all->GetParameter(11));
  //
  //grall->Fit("f_ozone_crossection","","",200,400);
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
  f_one_gauss01->SetLineColor(kBlue);
  f_one_gauss01->Draw("same");
  f_one_gauss02->SetLineColor(kMagenta);
  f_one_gauss02->Draw("same");
  f_one_gauss03->SetLineColor(kGreen+2);
  f_one_gauss03->Draw("same");
  f_one_gauss04->SetLineColor(kRed+2);
  f_one_gauss04->Draw("same");
  //
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_nofit, "Data", "lp");
  leg->AddEntry(f_fit_all, "Total fit", "l");
  leg->AddEntry(f_one_gauss01, "Gauss 1", "l");
  leg->AddEntry(f_one_gauss02, "Gauss 2", "l");
  leg->AddEntry(f_one_gauss03, "Gauss 3", "l");
  leg->AddEntry(f_one_gauss04, "Gauss 4", "l");
  leg->Draw();
  //
  FILE *fp;
  fp = fopen("./ozon_abs_model_four_gauss.dat", "w+");
  for(Int_t ii = 0;ii<npar;ii++)
    fprintf(fp,"%d %100.90f \n",ii, f_fit_all->GetParameter(ii));
  fclose(fp);
  //
  return 0;
}
