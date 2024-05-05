// this is a separate macro to learn how to do the global fit with shared parameters for 2 sets of data in one fit

// - read in points for bet cma march 1 and 6
// - define the special function and fit!

// NOTE: if you update the points in the graph - you must check/change the number of pts per night
/*
double multiBess(double x, double* par){
  //"fabs([0])*pow(2.0*TMath::BesselJ1(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265))/(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265)),2)"
  double g2 = par[0];
  double theta = par[1];
  double f;
  double C = (TMath::Pi()*1e-3)/(4157e-10*206265);

  f = abs(g2)*pow((2.0*TMath::BesselJ1(C*x*theta)/(C*x*theta)),2.0);

  return g2;
*/

void besselglobalfit(){

  // placeholders for x,y, and xy errors of points
  double ptx;
  double pty;
  double ex;
  double ey;

  // number of points for both nights
  const int nmar1 = 7;
  const int nmar6 = 12;

  // arrays to store x,y, and errors for both night
  double march1x[nmar1];  // prev: 10
  double march1y[nmar1];
  double march1ex[nmar1];
  double march1ey[nmar1];

  double march6x[nmar6]; // prev: 13
  double march6y[nmar6];
  double march6ex[nmar6];
  double march6ey[nmar6];

  // read in file made from UniformDiskFit and fill arrays with each point
  std::ifstream marchpts;
  marchpts.open("march1and6pointswbkgsubt.txt",std::ifstream::in);

  string str;
  int i(0);
  int j = 0;

  while (getline(marchpts,str)){
    if (i<19){
    marchpts >> ptx >> pty >> ex >> ey;
    cout << ptx << " " << pty << " " << ex << " " << ey << endl;
    if(i<7){
      march1x[i] = ptx;
      march1y[i] = pty;
      march1ex[i] = ex;
      march1ey[i] = ey;
      cout << "for i = " << i << endl;
      cout << march1x[i] << " " << march1y[i] << " " << march1ex[i] << " " << march1ey[i] << endl;
    }
    else{
      march6x[j] = ptx;
      march6y[j] = pty;
      march6ex[j] = ex;
      march6ey[j] = ey;
      cout << "for i = " << i << " j = " << j << endl;
      cout << march6x[j] << " " << march6y[j] << " " << march6ex[j] << " " << march6ey[j] << endl;
      j+=1;
    }
    i++;
    cout << endl;
    }
    //cout << "test!! " << i << endl;
  }
  cout << "test after loop!" << endl;
  // something is going wrong right here after this loop!!!!

  for (int j=0; j<7; j++){
    cout << march1x[j] << " " << march1y[j] << " " << march1ex[j] << " " << march1ey[j] << endl;
  }
  for (int j=0; j<12; j++){
    cout << march6x[j] << " " << march6y[j] << " " << march6ex[j] << " " << march6ey[j] << endl;
    }

  // add points to tgraphs for both nights and draw
  TGraphErrors* march1 = new TGraphErrors();
  TGraphErrors* march6 = new TGraphErrors();
  TGraphErrors* bothnights = new TGraphErrors();

  for (int j=0; j<7; j++){
    march1->AddPoint(march1x[j],march1y[j]);
    // bothnights->AddPoint(march1x[j],march1y[j]);
    //march1->SetPointError(j,march1ex[j],march1ey[j]);
    cout << march1x[j] << " " << march1y[j] << " " << march1ex[j] << " " << march1ey[j] << endl;
  }
  for (int j=0; j<12; j++){
    march6->AddPoint(march6x[j],march6y[j]);
    // bothnights->AddPoint(march6x[j],march6y[j]);
    // march6->SetPointError(j,march6ex[j],march6ey[j]);
    cout << march6x[j] << " " << march6y[j] << " " << march6ex[j] << " " << march6ey[j] << endl;
    }
  cout << "TEST: march1n = " << march1->GetN() << endl;
  cout << "TEST: march6n = " << march6->GetN() << endl;
     for (int j=0; j<nmar1; j++){
    march1->SetPointError(j,march1ex[j],march1ey[j]);
    // bothnights->SetPointError(j,march1ex[j],march1ey[j]);
  }
  for (int j=0; j<nmar6; j++){
    march6->SetPointError(j,march6ex[j],march6ey[j]);
    //bothnights->SetPointError(j+10,march6ex[j],march6ey[j]);
  }

  for (int v=0; v<march1->GetN(); v++){
        bothnights->AddPoint(march1->GetPointX(v), march1->GetPointY(v));
        bothnights->SetPointError(v,march1->GetErrorX(v),march1->GetErrorY(v));
  }
  for (int v=0; v<march6->GetN(); v++){
        bothnights->AddPoint(march6->GetPointX(v), march6->GetPointY(v));
        bothnights->SetPointError(v+march1->GetN(),march6->GetErrorX(v),march6->GetErrorY(v));
  }

  TCanvas* c1 = new TCanvas("","",1000,600);
  TLine* zero = new TLine(0,0,170,0);
  zero->SetLineWidth(2);
   march1->SetMarkerStyle(20);
   march6->SetTitle("Visibility curves for March 1 and 6;baseline;g^2");
   march1->SetMarkerColor(2);
  march6->SetMarkerStyle(20);
  march6->SetMarkerColor(4);
  //march6->SetMinimum(0);
  march6->Draw("AP");
  march1->Draw("PSAME");
  TCanvas* c2 = new TCanvas("","",1000,600);
  bothnights->SetMarkerStyle(20);
  bothnights->SetTitle("both nights together to fit zero baseline normalization parameter");
  bothnights->SetMinimum(0);
  bothnights->Draw("AP");

  TCanvas* c3 = new TCanvas("","",1600,600);
  c3->Divide(2,1);
  c3->cd(1);
  c3->DrawFrame(0,-5e-6,190,1.3e-5);
  march1->SetTitle("March 1;baseline;g^2");
  //march1->SetMinimum(0);
  //march1->GetXaxis->SetRange(0,190);
  //march1->GetYaxis()->SetRange(-5e-6,13e-6);
  march1->Draw("AP");
  zero->Draw("SAME");
  c3->cd(2);
  //march6->SetTitle("March 6;baseline;g^2");
  march6->Draw("AP");
  zero->Draw("SAME");

  TCanvas* cmulti = new TCanvas("","",1000,600);
  TMultiGraph* mg = new TMultiGraph();
  mg->Add(march1);
  mg->Add(march6);

  //=====================================================================================================================
  // now I am going to try the fitting

  // thought: why wouldn't it work to fit the bessel curve to a combined graph of points from both nights,
  // take the zero baseline parameter from that fit, and then use it to fit each night for g2?
  // -> ok - it IS different and not quite correct

  // first fit to both nights together - just to determine the zero baseline parameter
  TF1* BessFit = new TF1("Bess","fabs([0])*pow(2.0*TMath::BesselJ1(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265))/(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265)),2)",0,200);
    BessFit->SetParName(0,"g^{2}(0)-1");
    BessFit->SetParName(1,"#theta_{UD} (mas)");
    BessFit->SetParameter(0,1e-5);
    BessFit->SetParameter(1,0.5);
    bothnights->Fit(BessFit);
    cout << "zero baseline norm/par0 = " << BessFit->GetParameter(0) << endl;

    // second fit to each night individually - to get angular diameter with fixed g^2 norm
    TF1* bess2 = new TF1("bess2","fabs([0])*pow(2.0*TMath::BesselJ1(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265))/(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265)),2)",0,200);
    bess2->SetParName(0,"g^{2}(0)-1");
    bess2->SetParName(1,"#theta_{UD} (mas)");
    bess2->FixParameter(0,BessFit->GetParameter(0));
    bess2->SetParameter(1,0.5);
    march1->Fit(bess2);
    cout << "#theta_{UD} night 1: " << bess2->GetParameter(1) << endl;
    cout << "X^2/ndf night 1: " << bess2->GetChisquare() << " / " << bess2->GetNDF() << endl;
     march6->Fit(bess2);
    cout << "#theta_{UD} night6: " << bess2->GetParameter(1) << endl;
    cout << "X^2/ndf night 6: " << bess2->GetChisquare() << " / " << bess2->GetNDF() << endl;

    // ==============================================================================================

    // now with the combined fit!

    /*  TF1* special = new TF1("special",multiBess,0,200);
    multiBess->SetParameter(0,1e-5);
    multiBess->SetParameter(1,0.5);
    march1->Fit(special);
    */

}
