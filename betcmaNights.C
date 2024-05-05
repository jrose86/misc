// very simple plots of angular diameter changing vs night - for bet CMa

// for feb 2022 and march 2022 data

void betcmaNights(){

  /* feb night 1 UD: 0.49245
feb night 3 UD: 0.574385
feb night 4 UD: 0.697743
march night 1 UD: 0.577639
march night 2 UD: 0.473602
march night 3 UD: 1.38667
march night 4 UD: 0.505696
march night 6 UD: 0.497139*/

  //UD:
  /* feb1: 0.492451
feb3: 0.574388
mar1: 0.577639
mar4: 0.505689
mar6: 0.497136*/
  //unc:
  /* feb1: 0.0744916
feb3: 0.0216931
mar1: 0.033538
mar4: 0.105071
mar6: 0.0298958*/

  double febnight[2] = {1,3};
  double febUD[2] = {0.492451, 0.574388};                               //{0.49245, 0.574385, 0.697743};
  double febUDunc[2] = {0.0744916, 0.0216931};
  double marnight[3] = {1,4,6};
  double marUD[3] = {0.577639, 0.505689, 0.497136};                       //{0.577639, 0.473602, 1.38667, 0.505696, 0.497139};
  double marUDunc[3] = {0.033538, 0.105071, 0.029895};


  TCanvas* febcv = new TCanvas("","",900,600);
  TGraphErrors* feb2022 = new TGraphErrors(2,febnight,febUD, 0, febUDunc);
  feb2022->SetTitle("feb 2022 by night;night;angular diameter");
  feb2022->SetMarkerStyle(20);
  //feb2022->SetMinimum(0);
  feb2022->Draw();


  TCanvas* marcv = new TCanvas("","",900,600);
  TGraphErrors* mar2022 = new TGraphErrors(3,marnight,marUD, 0, marUDunc);
  mar2022->SetTitle("march 2022 by night;night;angular diameter");
  mar2022->SetMarkerStyle(20);
  //mar2022->SetMinimum(0);
  mar2022->Draw();

}
