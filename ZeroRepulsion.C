// the idea here is to generate a distribution of pure noise
// then fit a Gaussian to it.
// We *should* get a distribution of fitted peak amplitudes **centered** at zero.
// But will that distribution be **peaked** at zero?  I suspect not.  I suspect
// that zero will be an UNLIKELY reported amplitude.
//
// As tau limits -> 0, distribution becomes centered at zero

void ZeroRepulsion(){

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  TRandom3* tr = new TRandom3();
  tr->SetSeed(0);

  double Sigma=1.0; //this is NOT the width of the gaussian peaks- just the noise
  double binSize(1.0);    // nanoseconds (changed from 4 to 1)
  int Nbins(100); // real data = 512

  TF1* myGaus = new TF1("myGaus","[0]*exp(-pow((x-[1])/[2],2)/2.0)",-(Nbins/2)*binSize,(Nbins/2)*binSize);
  myGaus->SetParName(0,"Amp");         myGaus->SetParameter(0,0.0);
  myGaus->SetParName(1,"#tau_{0}");   /*myGaus->FixParameter(1,5.);*/       myGaus->SetParLimits(1,-100,100); // <------- Josie, please play with these Limits. (orig: -100,100)
  double SigmaMax(6.0),SigmaMin(3.0);
  myGaus->SetParName(2,"#sigma");      myGaus->SetParameter(2,4);   myGaus->SetParLimits(2,SigmaMin,SigmaMax);

  TCanvas* tc = new TCanvas("hi","hi",1600,800);
  tc->Divide(5,2);

  TGraphErrors* FitAmps = new TGraphErrors;
  FitAmps->SetMarkerStyle(20);
  TGraphErrors* FitAmpsFarOff = new TGraphErrors;  // the peak was "found" far from where we put it
  FitAmpsFarOff->SetMarkerStyle(20);
  FitAmpsFarOff->SetMarkerColor(4);
  TGraphErrors* FitAmpsFlagged = new TGraphErrors; // human flags, pts to be removed
  FitAmpsFlagged->SetMarkerStyle(20);
  FitAmpsFlagged->SetMarkerColor(2);
  TGraphErrors* FitAmpsGood = new TGraphErrors; // non flagged -- again clunky but can fix later


  double signalAmp(1.0),signalSig(4.0),signalPos(10.);
  int ntries=500;
  int numFarOff(0);
  int numFlag1(0);
  int numFlag2(0);
  int numGood(0);
  int numFarNotFlagged(0);
  for (int i=0; i<ntries; i++){
    TH1D* CFsim = new TH1D("JustNoise","JustNoise",Nbins,-(Nbins/2)*binSize,(Nbins/2)*binSize);
    for (int j=1; j<=CFsim->GetXaxis()->GetNbins(); j++){
      CFsim->SetBinContent(j,tr->Gaus(0.0,Sigma)
                           +
                           signalAmp*exp(-(pow((CFsim->GetXaxis()->GetBinCenter(j)-signalPos)/signalSig,2)/2.0)));
      CFsim->SetBinError(j,Sigma);
      //      CFsim->Fill(tr->Gaus(5.0,4.0));  // added peaks -Josie
    }
    myGaus->SetParameter(0,0.0);
    myGaus->SetParameter(1,0.0);    // <--- THIS was causing the problems where we didn't see the branching at 0 amp
    int Flags = 0;
    if (i<10){
      tc->cd(i+1);
      CFsim->Fit(myGaus);
    }
    else{
      CFsim->Fit(myGaus,"0");

    }
    // human flags
    /* if(CFsim->GetFunction("myGaus")->GetParameter(0) <0){
      Flags = 1;
      numFlag1+=1;
      }*/
    if(abs(CFsim->GetFunction("myGaus")->GetParameter(2) -SigmaMin) <0.01 || abs(CFsim->GetFunction("myGaus")->GetParameter(2) -SigmaMax) <0.01){
      Flags = 2;
      numFlag2+=1;
      }

    FitAmps->SetPoint(i,i,CFsim->GetFunction("myGaus")->GetParameter(0));
    FitAmps->SetPointError(i,0,CFsim->GetFunction("myGaus")->GetParError(0));
    if (abs(CFsim->GetFunction("myGaus")->GetParameter(1)-signalPos)>2.0*signalSig){
      numFarOff+=1;
      FitAmpsFarOff->SetPoint(i,i,CFsim->GetFunction("myGaus")->GetParameter(0));
      FitAmpsFarOff->SetPointError(i,0,CFsim->GetFunction("myGaus")->GetParError(0));
      if (Flags ==0){
        numFarNotFlagged+=1;
      }
    }
    if (Flags !=0){
      FitAmpsFlagged->SetPoint(i,i,CFsim->GetFunction("myGaus")->GetParameter(0));
      FitAmpsFlagged->SetPointError(i,0,CFsim->GetFunction("myGaus")->GetParError(0));
      }
     else{
       numGood = ntries - numFlag2;
       if(Flags == 0){
         FitAmpsGood->SetPoint(i,i,CFsim->GetFunction("myGaus")->GetParameter(0)); // this method is a little clunky- can go back and fix later
         FitAmpsGood->SetPointError(i,i,CFsim->GetFunction("myGaus")->GetParError(0));
       }
     }
  }
 cout << "FitAmpsGood N: " << FitAmpsGood->GetN() << endl;
 cout << "Num far NOT flagged: " << numFarNotFlagged << endl;


  TCanvas* tc2 = new TCanvas("amps","amps",1000,600);
  tc2->Draw();
  TH1D* Frame = new TH1D("AllAmps",Form("Amplitudes Input Amp=%f Noise=%f",signalAmp,Sigma),1000,-0.5,ntries-0.5); //original
  Frame->SetMinimum(-6);  Frame->SetMaximum(6);
  Frame->GetXaxis()->SetTitle("Simulation #");
  Frame->GetYaxis()->SetTitle("Fitted Gaussian Amplitude");
  Frame->Draw();
  FitAmps->Draw("P");
  TLine* redZero = new TLine(-0.5,0,ntries-0.5,0);
  FitAmpsFarOff->Draw("P");
  FitAmpsFlagged->Draw("P");
  redZero->SetLineColor(2);
  redZero->SetLineWidth(2);
   redZero->Draw();

  TLine* magentaTruth = new TLine(-0.5,signalAmp,ntries-0.5,signalAmp);
  magentaTruth->SetLineColor(6);
  magentaTruth->SetLineWidth(2);
  magentaTruth->Draw();

  TLine* greenNoisehi = new TLine(-0.5,Sigma/sqrt(2),ntries-0.5,Sigma/sqrt(2));    greenNoisehi->SetLineColor(3);  greenNoisehi->SetLineWidth(2);  greenNoisehi->Draw();
  TLine* greenNoiselo = new TLine(-0.5,-Sigma/sqrt(2),ntries-0.5,-Sigma/sqrt(2));  greenNoiselo->SetLineColor(3);  greenNoiselo->SetLineWidth(2);  greenNoiselo->Draw();

  TH1D* AmpDistrib = new TH1D("AmpDist",Form("Amplitude Distribution Input Amp=%f Noise=%f", signalAmp,Sigma),100,-8,8);
  for (int i=0; i<FitAmps->GetN(); i++){
    double amp = FitAmps->GetPointY(i);
    double err = FitAmps->GetErrorY(i);
    AmpDistrib->Fill(amp);
  }
  TH1D* AmpDistribNoFlag = new TH1D("AmpDistNF","Flagged Points Removed",100,-8,8);
  for (int ii=0; ii<FitAmpsGood->GetN(); ii++){
   double amp2 = FitAmpsGood->GetPointY(ii);
   AmpDistribNoFlag->Fill(amp2);
  }

  TCanvas* tc3 = new TCanvas("AmpDistrib","Amplitude Distribution",1000,500);
  tc3->Divide(2,1);
  tc3->cd(1);
  tc3->Draw();
  AmpDistrib->Draw();
  TLine* truthVert = new TLine(signalAmp,0.0,signalAmp,AmpDistrib->GetMaximum()*1.1);
  truthVert->SetLineColor(6);
  truthVert->SetLineWidth(2);
  truthVert->Draw();
  TLine* SigmaVertLo = new TLine(-Sigma/(2*sqrt(2)),0,-Sigma/(2*sqrt(2)),AmpDistrib->GetMaximum()*1.1);  SigmaVertLo->SetLineColor(3);  SigmaVertLo->SetLineWidth(2);  SigmaVertLo->Draw();
  TLine* SigmaVertHi = new TLine(Sigma/(2*sqrt(2)),0,Sigma/(2*sqrt(2)),AmpDistrib->GetMaximum()*1.1);    SigmaVertHi->SetLineColor(3);  SigmaVertHi->SetLineWidth(2);  SigmaVertHi->Draw();

  tc3->cd(2);
  AmpDistribNoFlag->Draw();
  cout << "Bin Content-why is this changing??: " << AmpDistribNoFlag->GetBinContent(AmpDistribNoFlag->GetXaxis()->GetNbins()/2+1) << endl;

  AmpDistribNoFlag->AddBinContent(AmpDistribNoFlag->GetXaxis()->GetNbins()/2+1,-numFlag2);
  AmpDistribNoFlag->AddBinContent(AmpDistribNoFlag->GetXaxis()->GetNbins()/2+1, numFarNotFlagged);
   truthVert->Draw();
   SigmaVertLo->Draw();
   SigmaVertHi->Draw();

   int BranchCount(0);
  TH1D* LBranchProj = new TH1D("LBranchProj","Left Branch Projection",100,-8,8);
  for (int h=AmpDistrib->GetXaxis()->GetNbins()*0.1875; h<=AmpDistrib->GetXaxis()->GetNbins()/2; h++){
    LBranchProj->SetBinContent(h, AmpDistrib->GetBinContent(h));
    BranchCount+=AmpDistrib->GetBinContent(h);
  }
  cout << "LBranch Mean: " << LBranchProj->GetMean() << endl;
  cout <<"1 / LBranch Mean: " << 1/LBranchProj->GetMean() << endl;

  TCanvas* tc4 = new TCanvas("BranchProj","Branch Projection",500,500);
  LBranchProj->Draw();

  cout << "Branching/Truth: " << numFarOff << "/" << ntries-numFarOff << endl;
  //cout << "% truth: " << double((ntries-numFarOff)/ntries) << endl;
  cout << "Flag 1: " << numFlag1 << endl;
  cout << "Flag 2: " << numFlag2 << endl;
  cout << "total good (ntries-flag) = " << ntries - numFlag2 << endl;
  cout << "2nd branch count: " << BranchCount << endl;
}
