//fit noise w cosine function - read in T3T4 "HBTPeakWithFit" TProfile

void NoiseFits(){

//read in existing file from Analysis.root
//TFile *f1 = new TFile("../../../Analysis.root", "READONLY");  // <- from Mackenzie's code

/*
 TFile *f1 = TFile::Open("../../../Analysis.root");    // <-from google- root forums
 TProfile2D *CFPeak = nullptr;
if (f1) f1->GetObject("HBTPeakWithFit", CFPeak);
if (CFPeak) {
   CFPeak->Draw();
}
//f1->GetObject("HBTPeakWithFit", CFPeak);

  */

  TCanvas* tc = new TCanvas();
  tc->Divide(4,2);
  tc->cd(1);
  gStyle->SetOptFit(1);

  //Make histograms with random gaussian and background noise
  TRandom2 *randoms = new TRandom2();

  TH1D *histwGaus = new TH1D("histwGaus", "Noise Fit With Gaussian;Relative Time (ns);'magnitude'", 240, -120, 120);
  TH1D *histnoGaus = new TH1D("histnoGaus", "Noise Fit Excluding Gaussian;Relative Time (ns);'magnitude'", 240, -120, 120);
  TH1D *histnoNoise = new TH1D("histnoNoise", "No Noise Inserted;Relative Time (ns);'magnitude'", 240, -120, 120);
  TH1D *noisecf1 = new TH1D("noisecf1", "", 240, -120, 120);
  TH1D *noisecf2 = new TH1D("noisecf2", "", 240, -120, 120);
  TH1D *noisecf3 = new TH1D("noisecf3", "", 240, -120, 120);
  TH1D *fourierHist = new TH1D("fourierHist", "Fourier Transforms", 240, -120, 120);
  TH1D *noiseFourier = new TH1D("noiseFourier", "", 240, -120, 120);

  //Fill (Eval) histogram w cosine
  TF1 *cosdraw = new TF1("cosdraw", "[0]*cos([1]*x+[2])", -120, 120);
  cosdraw->SetParameter(0, 5.0);
  cosdraw->SetParameter(1, 0.05*TMath::Pi());
  cosdraw->SetParameter(2, TMath::Pi());

  histwGaus->Eval(cosdraw);
  histnoGaus->Eval(cosdraw);
  fourierHist->Eval(cosdraw);

  //Fill w added random background noise
  for (int i=1; i<=3000; i++){
   double rpos = randoms->Rndm()*120;
   histwGaus->Fill(rpos);
   histnoGaus->Fill(rpos);
   histnoNoise->Fill(rpos);
   fourierHist->Fill(rpos);
   double rneg = randoms->Rndm()*-120;
   histwGaus->Fill(rneg);
   histnoGaus->Fill(rneg);
   histnoNoise->Fill(rneg);
   fourierHist->Fill(rneg);
  }

   //Fill w random gaussian
   for (int j=1; j<=500; j++){
    double rgaus = randoms->Gaus(0, 5.0);
    histwGaus->Fill(rgaus);
    histnoGaus->Fill(rgaus);
    histnoNoise->Fill(rgaus);
    fourierHist->Fill(rgaus);
  }

  //Copy each histogram to subtract noise from these
  TH1D *noiseSubtwGaus = new TH1D("noiseSubtwGaus", "Subtraction of Noise Fit With Gaussian;Relative Time (ns);'magnitude'", 240, -120, 120);
  TH1D *noiseSubtnoGaus = new TH1D("noiseSubtnoGaus", "Subtraction of Noise Fit Excluding Gaussian;Relative Time (ns);'magnitude'", 240, -120, 120);
  TH1D *noiseSubtnoNoise = new TH1D("noiseSubtnoNoise", "Subtraction of Fit Without Noise;Relative Time (ns);'magnitude'", 240, -120, 120);
  TH1D *noiseSubtFourier = new TH1D("noiseSubtFourier", "Subtraction of Fourier Series Fit;Relative Time (ns);'magnitude'", 240, -120, 120);

   for (int k=-120; k<=histwGaus->GetXaxis()->GetNbins(); k++) {
     noiseSubtwGaus->SetBinContent(k,histwGaus->GetBinContent(k));
   }
    for (int ki=-120; ki<=histnoGaus->GetXaxis()->GetNbins(); ki++) {
     noiseSubtnoGaus->SetBinContent(ki,histnoGaus->GetBinContent(ki));
   }
    for (int kj=-120; kj<=histnoNoise->GetXaxis()->GetNbins(); kj++) {
    noiseSubtnoNoise->SetBinContent(kj,histnoNoise->GetBinContent(kj));
   }
    for (int kk=-120; kk<=fourierHist->GetXaxis()->GetNbins(); kk++) {
      noiseSubtFourier->SetBinContent(kk,fourierHist->GetBinContent(kk));
    }

   //----------------------------- Noise Fitting ----------------------------------------------

  //Define cosine fit function
     //for some reason, fitting both histograms with the same function messed up the second fit, regardless of which graph was first, so cosfit1 and cosfit2(and cosfit3) are identical, just separate
  TF1 *cosfit1 = new TF1("cosfit1","[0]+[1]*cos([2]*x+[3])");
  double freq = 0.05*TMath::Pi();
  cosfit1->SetRange(histwGaus->GetXaxis()->GetXmin(), histwGaus->GetXaxis()->GetXmin());
  //cosfit1->SetParameter(0,1.0);
  //cosfit1->SetParName(0, "vertical shift");
  cosfit1->SetParameter(1,5.0);
  cosfit1->SetParName(1, "amplitude");
  // cosfit1->SetParLimits(1,5.0+1.0, 5.0-1.0);
  cosfit1->SetParameter(2,freq);
  cosfit1->SetParName(2, "frequency");
  //cosfit1->SetParLimits(2,freq-0.01,freq+0.01);
  cosfit1->SetParameter(3,TMath::Pi());
  cosfit1->SetParName(3, "phase shift");
  cosfit1->SetParLimits(3,-0.1,2.0*TMath::Pi()+0.1);

   TF1 *cosfit2 = new TF1("cosfit2","[0]+[1]*cos([2]*x+[3])");
  cosfit2->SetRange(histwGaus->GetXaxis()->GetXmin(), histwGaus->GetXaxis()->GetXmin());
  //cosfit2->SetParameter(0,1.0);
  //cosfit2->SetParName(0, "vertical shift");
  cosfit2->SetParameter(1,5.0);
  cosfit2->SetParName(1, "amplitude");
  // cosfit2->SetParLimits(1,5.0+1.0, 5.0-1.0);
  cosfit2->SetParameter(2,freq);
  cosfit2->SetParName(2, "frequency");
  //cosfit2->SetParLimits(2,freq-0.01,freq+0.01);
  cosfit2->SetParameter(3,TMath::Pi());
  cosfit2->SetParName(3, "phase shift");
  cosfit2->SetParLimits(3,-0.1,2.0*TMath::Pi()+0.1);

  TF1 *cosfit3 = new TF1("cosfit3","[0]+[1]*cos([2]*x+[3])");
  cosfit3->SetRange(histwGaus->GetXaxis()->GetXmin(), histwGaus->GetXaxis()->GetXmin());
  //cosfit3->SetParameter(0,1.0);
  //cosfit3->SetParName(0, "vertical shift");
  cosfit3->SetParameter(1,5.0);
  cosfit3->SetParName(1, "amplitude");
  // cosfit3->SetParLimits(1,5.0+1.0, 5.0-1.0);
  cosfit3->SetParameter(2,freq);
  cosfit3->SetParName(2, "frequency");
  //cosfit3->SetParLimits(2,freq-0.01,freq+0.01);
  cosfit3->SetParameter(3,TMath::Pi());
  cosfit3->SetParName(3, "phase shift");
  cosfit3->SetParLimits(3,-0.1,2.0*TMath::Pi()+0.1);

  //Define Fourier Transforms
  double Acos = 0;
  double cosnorm = 0;
  double Asin = 0;
  double sinnorm = 0;
  double A;
  double phi;
  int Nbins = fourierHist->GetXaxis()->GetNbins();

  for (int l=0; l<=Nbins; l++){
    if (l<101 || l>140){
      Acos += cos(freq * fourierHist->GetBinCenter(l)) * fourierHist->GetBinContent(l);
      Asin += sin(freq * fourierHist->GetBinCenter(l)) * fourierHist->GetBinContent(l);
      cosnorm += cos(freq * fourierHist->GetBinCenter(l)) * cos(freq*fourierHist->GetBinCenter(l));
      sinnorm += sin(freq*fourierHist->GetBinCenter(l)) * sin(freq*fourierHist->GetBinCenter(l));
    }
  }

  cout << "Acos = " << Acos << endl;
  cout << "Asin = " << Asin << endl;
  Acos /= cosnorm;
  Asin /= sinnorm;

  A = sqrt(pow(Asin, 2)+pow(Acos, 2));
  cout << "A = " << A << endl;
  phi = atan2(Asin,Acos); // atan2 accts for the quadrant- better phase
  cout << "phi = " << phi << endl;

  TF1 *fourierfit = new TF1("fourierfit", "11+[0]*-(cos([1]*x) + [2])",-120, 120); //there's a negative here that I added bc the fit function was negative without it- why do we need this?
  fourierfit->SetParameter(0, A);
  fourierfit->SetParameter(1, freq);
  // fourierfit->SetParameter(2, fourierHist->GetBin);
  fourierfit->SetParameter(2, phi);

  tc->cd(4);

  fourierHist->Draw();

  noiseFourier->Eval(fourierfit);
  //noiseFourier->Draw("SAME");
  fourierfit->Draw("SAME");

  //Fit and draw graphs, fill noise histograms with noise fits
   tc->cd(1);
   histwGaus->Fit(cosfit1, "W");
   histwGaus->Draw();
   noisecf1->Eval(cosfit1);

  //Remove gaussian from the fit
  for (int j=101; j<=140; j++) {
    histnoGaus->SetBinContent(j, 0);
    histnoNoise->SetBinContent(j, 0);
  }

  tc->cd(2);
  histnoGaus->Fit(cosfit2, "W");
  histnoGaus->Draw();
  noisecf2->Eval(cosfit2);

  tc->cd(3);
  histnoNoise->Fit(cosfit3, "W");
  histnoNoise->Draw();
  noisecf3->Eval(cosfit3);

  //Subtract noise from histograms and draw
  tc->cd(5);
  noiseSubtwGaus->Add(noisecf1, -1);
  noiseSubtwGaus->Draw();

  tc->cd(6);
  noiseSubtnoGaus->Add(noisecf2, -1);
  noiseSubtnoGaus->Draw();

  tc->cd(7);
  noiseSubtnoNoise->Add(noisecf3, -1);
  noiseSubtnoNoise->Draw();

  tc->cd(8);
  noiseSubtFourier->Add(noiseFourier, -1);
  noiseSubtFourier->Draw();

  /*
 TFile* outputFile = new TFile("NoiseFitting.root","RECREATE");
 //CFPeak->Write("CFPeak");

 //TCanvas *graph = new TCanvas();
  hist->Write("histogram");
  //CFPeak->Draw();

 outputFile->Close(); */

  tc->SaveAs("NoiseFitsPic.png");
}
