// josie 18 may 2024
// draw visibility curve for expected star size and normalization, predict at what baselines visibility goes to zero

// return the expected visibility at given baseline
double calcVis(double baseline, double starsize, double cnorm){
    double vis = fabs(cnorm)*pow(2.0*TMath::BesselJ1(TMath::Pi()*baseline*starsize*1e-3/(4157e-10*206265))/(TMath::Pi()*baseline*starsize*1e-3/(4157e-10*206265)),2);
    return vis;
}

void sampleVisCurve(){

  // change these to be the size you want for your star
  double cnorm = 1e-5;
  double starsize = 0.8; // mas

  // draw the expected curve
  TCanvas* c1 = new TCanvas();
  //string sourcestr = source;
  TGraph* viscurve = new TGraph;    viscurve->SetTitle(Form("sample curve for C_{UD} = %1.1e, angular diameter = %3.2f mas;baseline (m);g^{2}", cnorm, starsize));
  viscurve->SetMarkerStyle(9);      viscurve->SetMarkerColor(0);
  viscurve->AddPoint(0,0);          viscurve->AddPoint(180, cnorm);
  TF1* visfunc = new TF1("udfit","fabs([0])*pow(2.0*TMath::BesselJ1(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265))/(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265)),2)", 0, 200);
  visfunc->SetParName(0, "C_{UD}");               visfunc->SetParameter(0, cnorm);
  visfunc->SetParName(1, "#theta_{UD} (mas)");    visfunc->SetParameter(1, starsize);
  viscurve->Draw("AP");
  visfunc->Draw("SAME");

  // calculate when baselines are at 0
  for (int ib=0; ib<=200; ib++){
    double vis = calcVis(ib, starsize, cnorm);
    if(vis < cnorm*0.01){ cout << "visibility < 1% of predicted zero baseline correlation at " << ib << " m baseline" << endl; break;}
  }
  for (int ib=0; ib<=200; ib++){
    double vis = calcVis(ib, starsize, cnorm);
    if(vis < 1e-9){ cout << "baseline hits zero visibility at " << ib << " m" << endl; break;}
  }

}
