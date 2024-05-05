// josie 30 nov 2023
// calculate error bars from noise removal -- doing separately in a new macro bc CorrelationAnalysis removes each frequency separately and I need them within the loop

void noise(){

  TFile* analysis = new TFile("Analysis.root","READONLY");
  TProfile2D* cf = new TProfile2D; // this is the cf normalized and rebinned, what we feed into the first iteration of noise removal (which DOES have errorbars)

  TH1D* firstframe = new TH1D;
  TH1D* firstnoise = new TH1D; // noise wout err
  TH1D* secondnoise = new TH1D;
  TH1D* thirdnoise = new TH1D;

  analysis->GetObject("CFNormalized",cf);    cf->RebinY(256);
  analysis->GetObject("slice1",firstframe);
  analysis->GetObject("noiseModel1",firstnoise);
  analysis->GetObject("noiseModel2",secondnoise);
  analysis->GetObject("noiseModel3",thirdnoise);

  double freq[3] = {0.4991, 0.0628, 0.6754}; // 80, 10, 107 MHz

  TH1D* mynoise = new TH1D("mynoise","noise model w err",firstnoise->GetXaxis()->GetNbins(),firstnoise->GetXaxis()->GetXmin(),firstnoise->GetXaxis()->GetXmax()); // noise w errs
  double Jf(0.0);   double avgerrNoise(0.0);    double avgerrCF(0.0);   double sumerrNoise(0.0);   double sumerrCF(0.0); int nbinsOut(0); // for calculations later

  for (int k=1; k<=firstframe->GetXaxis()->GetNbins(); k++){
    double sumi(0.0);
    for (int i=1; i<=firstframe->GetXaxis()->GetNbins(); i++){
      double sumj(0.0);
      double temp(0.0); int ntemp(0);
      if(firstframe->GetBinCenter(i) < -100 || firstframe->GetBinCenter(i) > 100){
        for (int j=0; j<3; j++){ // 3 freq
          double cosnorm(0.0); double sinnorm(0.0);
          for (int m=1; m<=firstframe->GetXaxis()->GetNbins(); m++){
            if(firstframe->GetBinCenter(m) < -100 || firstframe->GetBinCenter(m) > 100){
              cosnorm+= cos(freq[j]*firstframe->GetBinCenter(m))*cos(freq[j]*firstframe->GetBinCenter(m));
              sinnorm+= sin(freq[j]*firstframe->GetBinCenter(m))*sin(freq[j]*firstframe->GetBinCenter(m));
            }
          }
          sumj += ((cos(freq[j]*firstframe->GetBinCenter(i))*cos(freq[j]*firstframe->GetBinCenter(k)))/cosnorm)
            + ((sin(freq[j]*firstframe->GetBinCenter(i))*sin(freq[j]*firstframe->GetBinCenter(k)))/sinnorm);
          if(k==1){ cout << "i " << i << " sumj " << sumj << "   i terms " << cos(freq[j]*firstframe->GetBinCenter(i)) << " " << sin(freq[j]*firstframe->GetBinCenter(i)) << "   k terms " << cos(freq[j]*firstframe->GetBinCenter(k)) << " " << sin(freq[j]*firstframe->GetBinCenter(k)) << "   " << cos(freq[j]*firstframe->GetBinCenter(i))*cos(freq[j]*firstframe->GetBinCenter(k)) << "  " << sin(freq[j]*firstframe->GetBinCenter(i))*sin(freq[j]*firstframe->GetBinCenter(k)) << "   " << (cos(freq[j]*firstframe->GetBinCenter(i))*cos(freq[j]*firstframe->GetBinCenter(k))) + (sin(freq[j]*firstframe->GetBinCenter(i))*sin(freq[j]*firstframe->GetBinCenter(k))) << endl;
          temp += (cos(freq[j]*firstframe->GetBinCenter(i))*cos(freq[j]*firstframe->GetBinCenter(k))) + (sin(freq[j]*firstframe->GetBinCenter(i))*sin(freq[j]*firstframe->GetBinCenter(k)));
          ntemp ++;}

        }// j
      }// if out
      if(k==1){ cout << "temp " << temp << "   avg temp " << temp/double(ntemp) << "  n " << ntemp << endl;}
      sumerrCF += firstframe->GetBinError(i);
      double ei = firstframe->GetBinError(i)*sumj;
      sumi += (ei*ei);
      nbinsOut++;
    }// i
    mynoise->SetBinContent(k, firstnoise->GetBinContent(k)+secondnoise->GetBinContent(k)+thirdnoise->GetBinContent(k)); // note: secondnoise, thirdnoise << firstnoise
    mynoise->SetBinError(k, sqrt(sumi));
    //cout << k << "  " << sqrt(sumi) << endl;
  }// k

  mynoise->Draw();

  // some quick calculations for the J factor so I don't need to do them by hand

  for (int n=1; n<=firstframe->GetXaxis()->GetNbins(); n++){
    sumerrNoise += mynoise->GetBinError(n);
    //sumerrCF += firstframe->GetBinError(n);
  }

  avgerrNoise = sumerrNoise / mynoise->GetXaxis()->GetNbins();
  //avgerrCF = sumerrCF / firstframe->GetXaxis()->GetNbins();
  avgerrCF = sumerrCF / nbinsOut; // for this first run at least - the inside and outside errorbars calculation is identical


  Jf = avgerrNoise / avgerrCF; // "J factor"
  Jf +=1;

  cout << "avg error radio noise model: " << avgerrNoise << endl;
  cout << "avg err correlation function: " << avgerrCF << endl;
  cout << "J factor: " << Jf << "   sqrt(Jf): " << sqrt(Jf) << endl;

  // copied from corr analysis - how we call the noise removal w each freq
  //CF = NoiseRemoveExactFreq(CF, 0.4991, 1); //80 MHz //Put how many times you call it at the end. Start with 1.
  //CF = NoiseRemoveExactFreq(CF, 0.0628, 2); //10 MHz
  //CF = NoiseRemoveExactFreq(CF, 0.6754, 3); //107MHz

  // big loop over each bin in cf (1D) = k
  // sqrt (loop over each bin outside peak = i)
  // squared (loop over each freq * err on CF(i))
  // each cos(wt) term ...

  // mackenzie's noise removal function:
  /*
  TProfile2D * NoiseRemoveExactFreq(TProfile2D *CF, double FFTFreq, int times){

  TProfile2D* CFMinusNoise = (TProfile2D*)CF->Clone("CFRemoveNoise");
  CFMinusNoise->Reset();

  //Define graphs to save parameters to
  TGraph * HeightGraph = new TGraph(); HeightGraph->SetTitle("DC Component; Time (Seconds); Normalized Counts");
  TGraph * AmpGraph    = new TGraph(); AmpGraph->SetTitle("Amplitude of Noise; Time (Seconds); Amplitude");
  TGraph * FreqGraph   = new TGraph(); FreqGraph->SetTitle("Frequency of Noise; Time (Seconds); Frequency (radians per ns)");
  TGraph * PhaseGraph  = new TGraph(); PhaseGraph->SetTitle("Phase of Noise; Time(Seconds); Phase (Radians)");

  for(int TimeSlice = 1; TimeSlice<=CF->GetYaxis()->GetNbins() ; TimeSlice++){
    TH1D * CFy = CF->ProjectionX("temp", TimeSlice, TimeSlice);
    if(TimeSlice == 1){ CFy->Write(Form("slice%d", times));}
    TH1D* noisefit = new TH1D("noisefit","g^2 radio",CFy->GetXaxis()->GetNbins(),CFy->GetXaxis()->GetXmin(),CFy->GetXaxis()->GetXmax());
    double height = 0.0;
    if (times == 1){
        CFy->Fit("pol0", "S0Q");
        height = CFy->GetFunction("pol0")->GetParameter(0);
        //cout << times << " height " << height << endl;
    }

    double AmpCos(0), CosNorm(0), AmpSin(0), SinNorm(0);
    for(int ix = 1; ix <= CFy->GetXaxis()->GetNbins(); ++ix){
      if(CFy->GetBinCenter(ix) < -100 || CFy->GetBinCenter(ix) > 100){
        AmpCos += cos(FFTFreq*CFy->GetBinCenter(ix))*(CFy->GetBinContent(ix)-height);
        CosNorm += pow(cos(FFTFreq*CFy->GetBinCenter(ix)), 2);
        AmpSin += sin(FFTFreq*CFy->GetBinCenter(ix))*(CFy->GetBinContent(ix)-height);
        SinNorm += pow(sin(FFTFreq*CFy->GetBinCenter(ix)), 2);
      }
    }

    AmpCos /= CosNorm; AmpSin /= SinNorm;

    double Amp = sqrt(pow(AmpCos,2)+pow(AmpSin,2));
    double Phi = atan2(AmpSin, AmpCos);

    HeightGraph->AddPoint(CF->GetYaxis()->GetBinCenter(TimeSlice), height);
    AmpGraph->AddPoint(CF->GetYaxis()->GetBinCenter(TimeSlice), Amp);
    FreqGraph->AddPoint(CF->GetYaxis()->GetBinCenter(TimeSlice), 0.0);
    PhaseGraph->AddPoint(CF->GetYaxis()->GetBinCenter(TimeSlice), Phi);

    for (int ix=1; ix<=CF->GetXaxis()->GetNbins(); ix++){
      CFMinusNoise->Fill(CF->GetXaxis()->GetBinCenter(ix),CF->GetYaxis()->GetBinCenter(TimeSlice), CF->GetBinContent(ix, TimeSlice) - (height+Amp*cos(FFTFreq*CF->GetXaxis()->GetBinCenter(ix)-Phi)));
      noisefit->SetBinContent(ix,height+Amp*cos(FFTFreq*CF->GetXaxis()->GetBinCenter(ix)-Phi));
    }
    if(TimeSlice == 1){ noisefit->Write(Form("noiseModel%d",times));}
  }

  //Save Parameter Graphs to a canvas and write to output file
  TCanvas * AllParams = new TCanvas(Form("NoiseParameters%d", times), "AllParams", 1600, 800);
  AllParams->Divide(2,2);
  AllParams->cd(1); HeightGraph->Draw("A*");
  AllParams->cd(2); AmpGraph->Draw("A*");
  AllParams->cd(3); FreqGraph->Draw("A*");
  AllParams->cd(4); PhaseGraph->Draw("A*");
  AllParams->Write(Form("ParameterGraphs%d", times));

  //Write and return Correlation Functions without noise
  CFMinusNoise->SetTitle("Normalized Correlation Function Without Noise; Relative Time (ns); Time");
  CFMinusNoise->Write(Form("CFMinusNoise%d", times));

  return CFMinusNoise;
  }*/

}//end of macro
