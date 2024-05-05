// macro for john to make ADC distributions

void ADCdists(){

  // ==================== read in the correlation function and ADCs from the zipped frames root file ================================================
  TFile *File = new TFile("ZippedFrames.root","READONLY"); // check that this matches the file name (the new versions are named by source and date)
  TProfile2D* CF;
  TH2D* ADC1;
  TH2D* ADC2;

  File->GetObject("/Pair0/CF12", CF); // this takes the object "CF12" from within the directory "Pair0" and it's named "CF" in this macro
  File->GetObject("/Pair0/singles1", ADC1);
  File->GetObject("/Pair0/singles2", ADC2);

  // ================================================================================================================================================

  // here is where you put your code

  ADC1->Draw("COLZ"); // this just draws the first ADC - you can comment this out

  // some random useful things

  // this is an example of a for loop in c++ (you will probably need one) - you can also comment this out or delete it
  for (int i=0; i<10; i++){
    cout << "i: " << i << endl;
  }

  // projection of ADC1 along x axis (collapses y axis) for all bins in ADC1
  TH1D* ADC1Projection = ADC1->ProjectionX("",1,-1);
  // ADC1Projection->Draw();

  // get number of bins along an axis
  int numFrames = ADC1->GetYaxis()->GetNbins();
  cout << "ADC1 number of frames = " << numFrames << endl;

  // a new TCanvas so you can draw more than one graph at once
  TCanvas* c2 = new TCanvas("","",800,600);

  // putting data into a histogram
  TH1D* exampleHist = new TH1D("exampleHist","example",10,-5,5);
  exampleHist->SetBinContent(1,2);     exampleHist->SetBinContent(9,3);
  exampleHist->Fill(1);
  exampleHist->Draw();

  // getting data from a histogram
  double oneBinADC1 = ADC1->GetBinContent(10);
  cout << "content of bin 10 from ADC1: " << oneBinADC1 << endl;

}
