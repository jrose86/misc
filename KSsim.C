// josie 4 jan 2024
// simulation to test KS test in root

void KSsim(){

  int nSamples = 100;
  int nRepeats = 100;

  TRandom3* rand = new TRandom3();
  rand->SetSeed(0);
  // double = rand->Gaus(mean,sigma);

  TCanvas* c1 = new TCanvas("","",1400,600);
  c1->Divide(2,1);
  TH1D* KSdist = new TH1D("KSdist","distribution of KS scores;score;counts",50,0.0,1.0);
  TH1D* ADdist = new TH1D("ADdist","distribution of AD scores;score;counts",50,0.0,1.0);

  // results of KS and AD tests very inconsistent (although KS much more consistent than AD) so I am running each multiple times and making distrbutions of
the tests
  for (int j=0; j<nRepeats; j++){
    TH1D* hist1 = new TH1D("hist1","sample dist 1;value;counts",100,-5,5);
    TH1D* hist2 = new TH1D("hist2","sample dist 2;value;counts",100,-5,5); // histograms MUST have identical binning to do the KS test

    // fill both distributions with nSamples
    for (int i=0; i<nSamples; i++){
      hist1->Fill(rand->Gaus(0.0,1.0));
      hist2->Fill(rand->Gaus(0.0,1.0));
    }

    double KStest = hist1->KolmogorovTest(hist2);
    double ADtest = hist1->AndersonDarlingTest(hist2);
    KSdist->Fill(KStest);
    ADdist->Fill(ADtest);
    cout << j << "  KS: " << KStest << "  AD: " << ADtest << endl;
    //cout << "KS test: " << KStest << "   AD test: " << ADtest << endl;

    }
    c1->cd(1); KSdist->Draw();
    c1->cd(2); ADdist->Draw();

    //TCanvas* c1 = new TCanvas("","",1400,600);
    //c1->Divide(2,1);
    //c1->cd(1); hist1->Draw();
    //c1->cd(2); hist2->Draw();

}
