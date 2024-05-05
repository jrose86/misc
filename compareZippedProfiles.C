// josie 8 may 2023

// a very simple macro to compare correlations made by versii to check that they're identical

void compareZippedProfiles(){

  // read in the two ZippedFrames.root files (must have different names/paths)
  TProfile2D* firstprof;
  TProfile2D* secondprof;

  //CorrelationFile->GetObject("/Pair0/Header",header);

  TFile* corrfile1 = new TFile("ZippedFrames.root","READONLY");
  TFile* corrfile2 = new TFile("ZippedFrames_osc.root","READONLY");
  //TFile* corrfile2 = new TFile("ZippedFrames.root","READONLY");

  corrfile1->GetObject("/Pair0/CF12",firstprof);
  corrfile2->GetObject("CF12",secondprof);

  TFile* outfile = new TFile("testfile.root","RECREATE"); // it's easier to write to a root file and then draw bc the TProfile2Ds are so hefty - but these could be just drawn instead, if needed

  firstprof->Write("versiiProfile");
  secondprof->Write("otherProfile");

  TProfile2D* leftover = (TProfile2D*)secondprof->Clone("test");

  // divide the two profiles to check that it's 1
  leftover->Divide(firstprof);
  leftover->Write("leftover");

  // now - check that EACH bin is really 1 (or 0) and doesn't just look like it
  for (int i=1; i<leftover->GetNumberOfBins(); i++){
    if (abs(leftover->GetBinContent(i) - 1.00000) > 0.000000001){
      if (leftover->GetBinContent(i) != 0){
        //cout << abs(leftover->GetBinContent(i) - 1.00000) << endl;
        //cout << "AHH! not the same!" << endl;
      }
    }
  }
  cout << "All done!" << endl;
}
