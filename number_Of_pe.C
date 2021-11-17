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

Int_t number_Of_pe(){

  Double_t photonsPerM2 = 6.0;
  Double_t R = 1.0;
  Double_t PDE = 0.5;
  Double_t fillFactor  = 0.9;
  Double_t lam = photonsPerM2*R*R*TMath::Pi()*PDE*fillFactor;

  cout<<lam<<endl;
  
  TH1D *h1_r1 = new TH1D("h1_r1","r1",30,-0.5,29.5);

  TRandom3 *rnd = new TRandom3(11231231);
  
  for(Int_t i = 0;i<10000;i++){
    h1_r1->Fill(rnd->Poisson(lam));
  }
  
  h1_r1->Draw();
  
  return 0;
}
