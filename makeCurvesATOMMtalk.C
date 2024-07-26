// josie 25 july 2024
// making a round star vis curve and non-round star vis curve for ATOMM talk

double calcVis(double baseline, double starsize, double cnorm){
    double vis = fabs(cnorm)*pow(2.0*TMath::BesselJ1(TMath::Pi()*baseline*starsize*1e-3/(4157e-10*206265))/(TMath::Pi()*baseline*starsize*1e-3/(4157e-10*206265)),2);
    return vis;
}

void makeCurvesATOMMtalk(){
  
  TCanvas* cround = new TCanvas;
  TCanvas* cnround = new TCanvas;

  string sourcestr = "gam cas";

  double starsize(0.5);
  double cnorm(1e-5);

  const int n=2000;
  double x[n], y[n], ylow[n], yhi[n];
  for(int i=0; i<n; i++){
    x[i] = 0.1+i*0.1;
    ylow[i] = calcVis(x[i], 0.4, 1e-5);
    yhi[i] = calcVis(x[i], 0.6, 1e-5);
    y[i] = calcVis(x[i], 0.5, 1e-5);
  }

  TGraph* top = new TGraph(n,x,ylow);
  TGraph* bottom = new TGraph(n,x,yhi);
  TGraph* shading = new TGraph(2*n);
  for(int i=0; i<n; i++){
    shading->SetPoint(i,x[i],yhi[i]);
    shading->SetPoint(n+i,x[n-i-1], ylow[n-i-1]);
  }
  shading->SetFillStyle(3003);
  shading->SetFillColor(2);

  TGraph* viscurve = new TGraph;      //viscurve->SetTitle(Form("%s, C_{UD} = %f, size = %f mas;baseline (m);g^{2}", sourcestr.c_str(), cnorm, starsize));  
  viscurve->SetTitle(";baseline (m);visibility^{2}");
  viscurve->SetMarkerStyle(9);    viscurve->SetMarkerColor(0);
  viscurve->AddPoint(0,0);    viscurve->AddPoint(180, cnorm);
  TF1* visfunc = new TF1("udfit","fabs([0])*pow(2.0*TMath::BesselJ1(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265))/(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265)),2)", 0, 200);
  visfunc->SetParName(0, "C_{UD}");               visfunc->SetParameter(0, cnorm);
  visfunc->SetParName(1, "#theta_{UD} (mas)");    visfunc->SetParameter(1, starsize);
  cround->cd();
  viscurve->Draw("AP");
  visfunc->Draw("SAME");

  cnround->cd();
  viscurve->Draw("AP");

  TF1* smallfunc = new TF1("udfit","fabs([0])*pow(2.0*TMath::BesselJ1(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265))/(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265)),2)", 0, 200);
  smallfunc->SetParName(0, "C_{UD}");               smallfunc->SetParameter(0, cnorm);
  smallfunc->SetParName(1, "#theta_{UD} (mas)");    smallfunc->SetParameter(1, 0.4);

  TF1* largefunc = new TF1("udfit","fabs([0])*pow(2.0*TMath::BesselJ1(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265))/(TMath::Pi()*x*[1]*1e-3/(4157e-10*206265)),2)", 0, 200);
  largefunc->SetParName(0, "C_{UD}");               largefunc->SetParameter(0, cnorm);
  largefunc->SetParName(1, "#theta_{UD} (mas)");    largefunc->SetParameter(1, 0.6);

  cnround->cd();
  shading->Draw("f");
  //bottom->Draw("L");
  //top->Draw("L");
  smallfunc->Draw("SAME");
  largefunc->Draw("SAME");
  

}
