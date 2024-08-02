// josie 31 july 2024
// testing array as a function

double* thefunc(int rep){
  static double arr[4];
  //arr = {1.0, 2.0, 3.0, 4.0};
  for(int i=0; i<4;i++){
    arr[i] = i*rep;
  }

  return arr;
}

void testArrayFunc(){

  TGraph* graph = new TGraph;  graph->SetMarkerStyle(20);
  for(int r=0; r<3; r++){
    double* myarr;
    myarr = thefunc(r+1);
    for(int i=0; i<4; i++){
      cout << myarr[i] << endl;
    }
    graph->AddPoint(myarr[1], myarr[2]);
  }
  graph->Draw("AP");

}
