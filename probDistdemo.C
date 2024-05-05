// Gaussian simulation - sample 2, 3, 10 pts and add them together, make hist of distribution

void probDistdemo(){
  TRandom3* tr = new TRandom3;
  tr->SetSeed(0);

  int numFill(1000000); // fill milpts 1 mil times

  //gaussian dist

  TCanvas* tc1 = new TCanvas;
  tc1->Divide(2,2);
  tc1->cd(1);
  TH1D* milpts = new TH1D("milpts","million pts",200,-100,100);
  for(int i=0; i<numFill; i++){
  milpts->Fill(tr->Gaus(0,10));}
  milpts->Draw();

  tc1->cd(2);
  TH1D* twopts = new TH1D("twopts","2 pts added",200,-100,100); //change width/bins??
  for (int j=0; j<numFill; j++){
    double x1 = tr->Gaus(0,10);
    double x2 = tr->Gaus(0,10);
    twopts->Fill(x1+x2);}
  twopts->Draw();

  tc1->cd(3);
  TH1D* threepts = new TH1D("threepts","3 pts added",200,-100,100);
  for (int jj=0; jj<numFill; jj++){
    double xp1 = tr->Gaus(0,10);
    double xp2 = tr->Gaus(0,10);
    double xp3 = tr->Gaus(0,10);
    threepts->Fill(xp1+xp2+xp3);}
  threepts->Draw();

  tc1->cd(4);
  TH1D* tenpts = new TH1D("tenpts","10 pts added",200,-100,100);
  for (int jjj=0; jjj<numFill; jjj++){
    double x10(0.0);
    for(int ii=0; ii<10; ii++){
      x10 = x10 + tr->Gaus(0,10);}
    tenpts->Fill(x10);}
  tenpts->Draw();

  // as you increase sample size -- width should get smaller? (by sqrt(n)?)
  // as you increase # pts added -- width gets LARGER
  // understand width = unc/error??

  // for red predicted line - you are ADDING the splits - more splits = more pts added -> so YES it SHOULD get LARGER

  // uniform square dist

  TCanvas* tc2 = new TCanvas;
  tc2->Divide(2,2);
  tc2->cd(1);
  TH1D* milptsSq = new TH1D("milptsSq","million pts",200,-100,100);
  for(int i=0; i<numFill; i++){
  milptsSq->Fill(tr->Uniform(-5,5));}
  milptsSq->Draw();

  tc2->cd(2);
  TH1D* twoptsSq = new TH1D("twoptsSq","2 pts added",200,-100,100); //change width/bins??
  for (int j=0; j<numFill; j++){
    double x1 = tr->Uniform(-5,5);
    double x2 = tr->Uniform(-5,5);
    twoptsSq->Fill(x1+x2);}
  twoptsSq->Draw();

  tc2->cd(3);
  TH1D* threeptsSq = new TH1D("threeptsSq","3 pts added",200,-100,100);
  for (int jj=0; jj<numFill; jj++){
    double xp1 = tr->Uniform(-5,5);
    double xp2 = tr->Uniform(-5,5);
    double xp3 = tr->Uniform(-5,5);
    threeptsSq->Fill(xp1+xp2+xp3);}
  threeptsSq->Draw();

  tc2->cd(4);
  TH1D* tenptsSq = new TH1D("tenptsSq","10 pts added",200,-100,100);
  for (int jjj=0; jjj<numFill; jjj++){
    double x10(0.0);
    for(int ii=0; ii<10; ii++){
      x10 = x10 + tr->Uniform(-5,5);}
    tenptsSq->Fill(x10);}
  tenptsSq->Draw();

}
