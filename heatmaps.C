// testing heatmaps binning and color schemes -- specific for bet UMa

void heatmaps(){

  TCanvas *c2  = new TCanvas("c2","c2",0,0,600,400);

  TFile *CorrelationFile = new TFile("Analysis.root","READONLY");
  TProfile2D * Correlations(0);
  CorrelationFile->GetObject("CFMinusNoise3", Correlations);

  TF2 *f2 = new TF2("f2","0.1+(1-(x-2)*(x-2))*(1-(y-2)*(y-2))",1,3,1,3);
  /* const Int_t Number = 3;
  double red[3]   = {0,1,1};
  double green[3] = {0,1,0};
  double blue[3]  = {1,1,0};
  double Levels[3] = {0.0,0.5,1.0};
  int nLevels = 3;

  TColor::CreateGradientColorTable(nLevels,Levels,red,green,blue,100);*/
    const int nLevels2=11;  // make it an odd number

  double Levels2[nLevels2] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
  double red2[nLevels2]    = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double green2[nLevels2]  = {0.0, 0.7, 0.85, 0.9, 1.0, 1.0, 0.3, 0.25, 0.2, 0.1, 0.0};
  double blue2[nLevels2]   = {0.9, 0.8, 0.7, 0.6, 0.5, 1.0, 0.3, 0.2, 0.1, 0.0, 0.0};

  /* double Levels2[nLevels2] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
  double red2[nLevels2]    = {0.0, 0.1, 0.2, 0.5, 0.7, 0.8, 0.8, 0.9, 0.9, 1.0, 1.0};
  double green2[nLevels2]  = {0.0, 0.7, 0.85, 0.9, 1.0, 1.0, 0.3, 0.25, 0.2, 0.1, 0.0};
  double blue2[nLevels2]   = {0.9, 0.8, 0.7, 0.6, 0.5, 1.0, 0.3, 0.2, 0.1, 0.0, 0.0};*/
  int nContours = 200;
  TColor::CreateGradientColorTable(nLevels2,Levels2,red2,green2,blue2,nContours);
  gStyle->SetNumberContours(nContours);
  Correlations->SetContour(nContours);
  Correlations->SetLineWidth(1);
  Correlations->SetLineColor(kBlack);
  //gStyle->SetPalette(kDarkBodyRadiator);
  //TColor::InvertPalette();
  Correlations->Draw("COLZ");
}
