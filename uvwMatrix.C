// josie 1 june 2023
// calculate the uvw matrix instead of doing it by hand with a calculator - but still manually inputting angles

void uvwMatrix(){

  // separation of telescopes in (N, E, up)
  double N = -48.8; // this is for T3T4
  double E = -65.3;
  double up = -2.8;

  // latitude, hour angle, and declination in radians
  double lat = 0.553;  // 31.675
  double ha =  4.977;  //-1.315;          //4.977;   // 285.2
  double dec = 0.984;  // 56.38

  // declare uvw
  double u(0.0);
  double v(0.0);
  double w(0.0);

  // test alt/az/dec calculation of hour angle
  double ha2(0.0);



  // matrix transformations
  u = (N * -sin(lat)*sin(ha)) + (E * cos(ha)) + (up * cos(lat)*sin(ha));
  v = (N * sin(lat)*cos(ha)*sin(dec)) + (N * cos(lat)*cos(dec)) + (E * sin(ha)*sin(dec)) + (up * -cos(lat)*cos(ha)*sin(dec)) + (up * sin(lat)*cos(dec));
  w = (N * -sin(lat)*cos(ha)*cos(dec)) + (N * cos(lat)*sin(dec)) + (E * -sin(ha)*cos(dec)) + (up * cos(lat)*cos(ha)*cos(dec)) + (up * sin(lat)*sin(dec));

  cout << "(u,v,w):  (" << u << "," << v << "," << w << ")" << endl;

  double pb = (u*u) + (v*v);
  pb = sqrt(pb);

  cout << "projected baseline: " << pb << endl;

}
