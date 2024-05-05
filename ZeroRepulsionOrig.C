// the idea here is to generate a distribution of pure noise
// then fit a Gaussian to it.
// We *should* get a distribution of fitted peak amplitudes **centered** at zero.
// But will that distribution be **peaked** at zero?  I suspect not.  I suspect
// that zero will be an UNLIKELY reported amplitude.

void ZeroRepulsionOrig(){

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  TRandom3* tr = new TRandom3();

  double Sigma=1.0;
  double binSize(1.0);    // nanoseconds
  int Nbins(100);

  TF1* myGaus = new TF1("myGaus","[0]*exp(-pow((x-[1])/[2],2)/2.0)",-(Nbins/2)*binSize,(Nbins/2)*binSize);
  myGaus->SetParName(0,"Amp");
  myGaus->SetParName(1,"#tau_{0}");    myGaus->SetParLimits(1,-100,100);   // <------- Josie, please play with these Limits.
  double SigmaMax(6.0),SigmaMin(3.0);
  myGaus->SetParName(2,"#sigma");      myGaus->SetParameter(2,4);   myGaus->SetParLimits(2,SigmaMin,SigmaMax);

  TCanvas* tc = new TCanvas("hi","hi",1600,800);
  tc->Divide(5,2);

  TGraphErrors* FitAmps = new TGraphErrors;
  FitAmps->SetMarkerStyle(20);

  int ntries=500;
  double signalAmp(0.0),signalSig(4.0),signalPos(10.0);
  for (int i=0; i<ntries; i++){
    TH1D* CFsim = new TH1D("JustNoise","JustNoise",Nbins,-(Nbins/2)*binSize,(Nbins/2)*binSize);
    for (int j=1; j<=CFsim->GetXaxis()->GetNbins(); j++){
      CFsim->SetBinContent(j,tr->Gaus(0.0,Sigma)
                           +signalAmp*exp(-(pow((CFsim->GetXaxis()->GetBinCenter(j)-signalPos)/signalSig,2)/2.0)));
      CFsim->SetBinError(j,Sigma);
    }
    myGaus->SetParameter(0,0.0);
    myGaus->SetParameter(1,0.0);
    if (i<10){
      tc->cd(i+1);
      CFsim->Fit(myGaus);;
    }
    else
      CFsim->Fit(myGaus,"0");
      FitAmps->SetPoint(i,i,CFsim->GetFunction("myGaus")->GetParameter(0));
      FitAmps->SetPointError(i,0,CFsim->GetFunction("myGaus")->GetParError(0));
  }


  TCanvas* tc2 = new TCanvas("amps","amps",1000,600);
  tc2->Draw();
  TH1D* Frame = new TH1D("AllAmps","All Amplitudes",1000,-0.5,ntries-0.5);
  Frame->SetMinimum(-6);  Frame->SetMaximum(6);
  Frame->Draw();
  FitAmps->Draw("P");
  TLine* redZero = new TLine(-0.5,0,ntries-0.5,0);
  redZero->SetLineColor(2);
  redZero->Draw();


  TH1D* AmpDistrib = new TH1D("AmpDist","Amplitude Distribution",100,-6,6);
  for (int i=0; i<FitAmps->GetN(); i++){
    double amp = FitAmps->GetPointY(i);
    double err = FitAmps->GetErrorY(i);
    AmpDistrib->Fill(amp);
  }
  TCanvas* tc3 = new TCanvas("AmpDistrib","Amplitude Distribution",500,500);
  tc3->Draw();
  AmpDistrib->Draw();

}
