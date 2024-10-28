// josie 16 oct 2024
// this is a prototype of the function to calculate the signal to noise "significance threshold" to justify which peaks we throw out

//double calcExcessErr(TProfile* cf, double area, double sigma, int reps);
TH1D* simpeak(double area, double tau, double sigma, int windowsize);


void sigThresh(TString filename, TString pair){

  // some peak parameters etc
  int nsizes(80); // number of loops of size
  double startpeak(0.0);
  double incpeak(0.05e-6);
  int reps(30);
  //cout << incpeak << endl;

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  TFile* rootfile = new TFile(filename.Data(),"READONLY");
  TProfile* cf = new TProfile;   rootfile->GetDirectory(pair.Data())->GetObject("projectedCF",cf);

  TRandom3* tr = new TRandom3();
  tr->SetSeed(0);

  // set up parameters for peaks
  double simtau(0.0), simsigma(4.0);
  double taumin(-10), taumax(10), sigmamin(2.0), sigmamax(7.0);
  int nwindows(16), windowsize(40); // nwindows(18)
  double thisarea(0.0);

  // fit function
  TF1* areafit = new TF1("areafit","([0]*exp(-pow((x-[1])/[2],2)/2.0))/([2]*sqrt(2*pi))",-300,300);
  areafit->SetParName(0,"A");          areafit->SetParameter(0,0.0);
  areafit->SetParName(1,"#tau_{0}");   areafit->SetParameter(1, simtau);        areafit->SetParLimits(1, taumin, taumax);
  areafit->SetParName(2,"#sigma");     areafit->SetParameter(2, simsigma);      areafit->SetParLimits(2, sigmamin, sigmamax);

  TCanvas* c1 = new TCanvas;   c1->Divide(3,2);
  c1->Print("distcan.pdf[");
  int ctc1(1);

  TCanvas* c2 = new TCanvas("","",1500,500);   c2->Divide(3,1);
  TGraph* taudev = new TGraph;    taudev->SetMarkerStyle(20); // st dev of tau dists vs area
  TGraph* pcthresh = new TGraph;  pcthresh->SetMarkerStyle(20); // percent of taus w/in threshold (start w \pm 3)
  TGraph* pcthresh5 = new TGraph; pcthresh5->SetMarkerStyle(20); // pc taus w/in threshold \pm 5
  taudev->SetTitle("std dev of tau dists;peak area;standard dev of dist");
  pcthresh->SetTitle("% of pts within threshold of +/- 3;peak area;percentage of dist within threshold");
  pcthresh5->SetTitle("% of pts within threshold of +/- 5;peak area;percentage of dist within threshold");

  TCanvas* junk = new TCanvas;
  junk->cd();

  // loop over different peak sizes
  for(int i=0; i<nsizes; i++){
    int ngood(0); // count number of fits that find the correct peak
    int nbad(0);
    int ngood5(0);
    int nbad5(0);
    startpeak = startpeak+incpeak;
    cout << i << "  " << startpeak << endl;
    thisarea = startpeak;

    TH1D* taudist = new TH1D("taudist","tau dist",30,-15,15);
    taudist->SetTitle(Form("area = %f e-6", thisarea/1.0e-6));
    
    // loop over number of reps for each 
    for(int i=0; i<reps; i++){
        int startbin(21), endbin(40); // startbin(1)
        
        // loop over off peak region "windows"
        for(int iw=0; iw<nwindows; iw++){
	  
	  double taushift = simtau - ((tr->Rndm()*10.0) - 5.0);
	  TH1D* fakepeak = simpeak(thisarea, taushift, simsigma, windowsize);

	  int flag(0);
          int thisbin = startbin;
          TH1D* thiswindow = new TH1D("thiswindow",Form("window %d",iw+1), windowsize, -(windowsize/2), (windowsize/2));
            
          // fill the window with off-peak noise plus fake peak
          for(int ix=1; ix<=windowsize; ix++){
	    thiswindow->SetBinContent(ix, cf->GetBinContent(thisbin) + fakepeak->GetBinContent(ix));
	    thiswindow->SetBinError(ix, cf->GetBinError(thisbin));
            thisbin++;
	  }
          //tempwindows->cd(iw+1);
          thiswindow->Draw();
            
          areafit->SetParameter(0,0.0);        areafit->SetParameter(1, simtau);        areafit->SetParameter(2, simsigma);
          thiswindow->Fit("areafit","Q"); //cout << areafit->GetParameter(0) << endl;

          // quality cuts as if this was a real peak in the analysis
          if(abs(areafit->GetParameter(1) - taumin) < 0.001 || abs(areafit->GetParameter(1) - taumax) < 0.001){ flag = 2; nbad++;}
          else if(abs(areafit->GetParameter(2) - sigmamin) < 0.001 || abs(areafit->GetParameter(2) - sigmamax) < 0.001){ flag = 3; nbad++;}
            
          if(flag < 1){  cout << "flag good" << endl; } //areadist->Fill(simarea - areafit->GetParameter(0)); }

	  if(flag < 1){
	  // check if we found the "right" peak
	  taudist->Fill(areafit->GetParameter(1) - taushift);
	  if(abs(areafit->GetParameter(1) - taushift) > 3.0){ nbad++; cout << "big dif " << areafit->GetParameter(1) - taushift << endl; }
	  else{ ngood++; }
	  if(abs(areafit->GetParameter(1) - taushift) > 5.0){ nbad5++; }
	  else {ngood5++; }
	  }
            
            
          if(i!=nwindows/2){ startbin = thisbin - 20; } 
          else{ startbin = thisbin + 90; }
            
          fakepeak->Delete();
          thiswindow->Delete();
            
        } // end of loop over windows
        //tempwindows->Print("tempwindows.pdf");
        
    } // end of loop over reps

    c1->cd(ctc1);
    taudist->Draw();
    if(ctc1 == 6){ c1->Print("distcan.pdf"); ctc1 = 0;}
    ctc1++;

    taudev->AddPoint(thisarea,taudist->GetStdDev());
    pcthresh->AddPoint(thisarea,double(ngood)/double(nbad+ngood));
    pcthresh5->AddPoint(thisarea,double(ngood5)/double(nbad5+ngood5));

    junk->cd();
    
  } // end of loop over peak sizes

  c1->Print("distcan.pdf");
  c1->Print("distcan.pdf]");

  c2->cd(1); taudev->Draw("AP");
  c2->cd(2); pcthresh->Draw("AP");
  c2->cd(3); pcthresh5->Draw("AP");

  double thresh(0);
  //double keeppt(0);
  for(int a=0; a<=pcthresh->GetN(); a++){
    if((pcthresh->GetPointY(a) - 0.5) >= 0){ thresh = pcthresh->GetPointX(a); break;}
  }

  cout << "threshold for +/- 3: " << thresh << endl;


}// end of macro



/*
  // calculate excess errorbars that come from RMS of fits to simulated peaks outside peak region
double calcExcessErr(TProfile* cf, double area, double sigma, int reps){
    
    //TH1::AddDirectory(kFALSE);
    
    //TCanvas* tempwindows = new TCanvas;     tempwindows->Divide(6,3);       //int iwindow(0);
    //tempwindows->Print("tempwindows.pdf["); 
    
    double simarea = area;//cf->GetFunction("hbtFit")->GetParameter(0);
    //double simsigma = sigma;
    
    // set up parameters for simulation peaks
    double simtau(0.0), simsigma(4.0);
    double taumin(-10), taumax(10), sigmamin(2.0), sigmamax(7.0);
    int nwindows(16), windowsize(40); // nwindows(18)
    
    // fit function
    TF1* areafit = new TF1("areafit","([0]*exp(-pow((x-[1])/[2],2)/2.0))/([2]*sqrt(2*pi))",-300,300);
    areafit->SetParName(0,"A");          areafit->SetParameter(0,0.0);
    areafit->SetParName(1,"#tau_{0}");   areafit->SetParameter(1, simtau);        areafit->SetParLimits(1, taumin, taumax);
    areafit->SetParName(2,"#sigma");     areafit->SetParameter(2, simsigma);      areafit->SetParLimits(2, sigmamin, sigmamax);
    
    TH1D* areadist = new TH1D("areadist",Form("difference between fit and real area, area = %f ns;input area - fitted area;counts", simarea), 50, -1e-5, 1e-5);
    
    // big loop to run "simulation peaks" more times and fill dist with more points --> IS THIS NEEDED?? you get about the same value only doing it once over each window, but it fluctuates
    for(int i=0; i<reps; i++){
        int startbin(21), endbin(40); // startbin(1)
        
        // loop over off peak region "windows"
        for(int iw=0; iw<nwindows; iw++){
            
            TH1D* fakepeak = simpeak(simarea, simtau, simsigma, windowsize);
            
            int flag(0);
            int thisbin = startbin;
            TH1D* thiswindow = new TH1D("thiswindow",Form("window %d",iw+1), windowsize, -(windowsize/2), (windowsize/2));
            
            // fill the window with off-peak noise plus fake peak
            for(int ix=1; ix<=windowsize; ix++){
                thiswindow->SetBinContent(ix, cf->GetBinContent(thisbin) + fakepeak->GetBinContent(ix));
                thiswindow->SetBinError(ix, cf->GetBinError(thisbin));
                thisbin++;
            }
            //tempwindows->cd(iw+1);
            thiswindow->Draw();
            
            //hbtFit->SetParameter(0,0.0);        hbtFit->SetParameter(1, simtau);        hbtFit->SetParameter(2, simsigma);
            thiswindow->Fit("areafit","Q"); //cout << areafit->GetParameter(0) << endl;
            
            // quality cuts as if this was a real peak in the analysis
            if(abs(areafit->GetParameter(1) - taumin) < 0.001 || abs(areafit->GetParameter(1) - taumax) < 0.001){ flag = 2; }
            if(abs(areafit->GetParameter(2) - sigmamin) < 0.001 || abs(areafit->GetParameter(2) - sigmamax) < 0.001){ flag = 3; }
            
            if(flag < 1){   areadist->Fill(simarea - areafit->GetParameter(0)); }
            
            if(i!=nwindows/2){ startbin = thisbin - 20; } 
            else{ startbin = thisbin + 90; }
            
            fakepeak->Delete();
            thiswindow->Delete();
            
        } // end of loop over windows
        //tempwindows->Print("tempwindows.pdf");
        
    } // end of loop over reps
    
    //tempwindows->Print("tempwindows.pdf]");
    
    double distRMS = areadist->GetRMS();
    
    return distRMS;
    }*/

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// create simulated peaks for function to calculate excess errorbars
TH1D* simpeak(double area, double tau, double sigma, int windowsize){
    // get random tau shift for this fake peak
    //TRandom3* tr = new TRandom3();          tr->SetSeed(0);
    //double taushift = tau - ((tr->Rndm()*10.0) - 5.0);
    
    TH1D* thepeak = new TH1D("thepeak",Form("peak area %f",area), windowsize, -(windowsize/2), (windowsize/2));
    
    for(int i=1; i<=windowsize; i++){
        double x = i-1-(windowsize/2);
        double val = (area*exp(-pow((x-(tau))/sigma,2)/2.0))/(sigma*sqrt(2*TMath::Pi()));
        thepeak->SetBinContent(i,val); // is there an extra assoc errorbar with the peak?
    }
    
    return thepeak;
}
