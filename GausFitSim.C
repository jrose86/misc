//Simulate random noise and fit noise with gaussian

void GausFitSim() {

  TCanvas * tc = new TCanvas();
  tc->Divide(2, 1);
  tc->cd(1);
  gStyle->SetOptFit(1);

  TH1D * gausSim = new TH1D("gausSim", "Simulation", 256, -128, 128);
  TH1D * gausSimTEST = new TH1D("gausSimTEST", "TEST (actually has a gaussian)", 256, -128, 128);
  TRandom2 *randoms = new TRandom2();

  //Fill histograms with random noise
  for (int i=1; i<=3000; i++){
    double rpos = randoms->Rndm()*128;
    gausSim->Fill(rpos);
    gausSimTEST->Fill(rpos);
    double rneg = randoms->Rndm()*-128;
    gausSim->Fill(rneg);
    gausSimTEST->Fill(rneg);
  }

   for (int j=1; j<=100; j++){
     double rgaus = randoms->Gaus(0, 1.0); //amp = 0, sigma = 1 bin
    gausSimTEST->Fill(rgaus);
  }

   //Fit histograms with gaussian function
   //TF1* PeakFit = new TF1("HBTpeak","([0]*exp(-pow((x-[1])/[2],2)/2.0))",-100,100); <-- Mackenzie's code from CorrelationAnalysis

  TF1 *gausfit = new TF1("gausfit", "[2]+[0]*exp(-pow((x/([1]*sqrt(2))),2.0)/2.0)");
  gausfit->SetParameter(0, 0);
  gausfit->SetParameter(1, 4.0);
  gausfit->SetParameter(2, 20.0);
  //gausfit->SetParameter(3, 0);
  TF1 *gausfit2 = new TF1("gausfit2", "[2]+[0]*exp(-pow((x/([1]*sqrt(2))),2.0)/2.0)");
  gausfit2->SetParameter(0, 0);
  gausfit2->SetParameter(1, 4.0);
  gausfit2->SetParameter(2, 20.0);
  // gausfit2->SetParameter(3, 0);

  gausSim->Fit("gausfit");
  gausSim->Draw();

  tc->cd(2);
  gausSimTEST->Fit("gausfit2");
  gausSimTEST->Draw();

}
