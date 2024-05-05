// simple graphs of changing run splits vs size of the muck

void mucksize(){

  // these are the old graphs for when I changed how many times the run is split (over ALL runs of Beta UMa)

  /*double splitNum[4] = {1.0, 2.0, 3.0, 4.0};
  double muck[4] = {0.795204, 1.22301, 1.56227, 1.83644};
  double muckpredicted[4] = {0.795204, 1.12, 1.38, 1.59};
  double muck2[2] = {0.747505, 1.16121}; // this is muck for truly only split 1, split 2, etc

  TGraph * muckgraph = new TGraph(4, splitNum, muck);
  muckgraph->SetTitle("Number of splits vs size of muck;number of splits;muck *10^-6");
  muckgraph->SetLineWidth(2);
  muckgraph->SetMinimum(0);
  muckgraph->Draw("AL*");

  TGraph * muckpredictedgraph = new TGraph(4, splitNum, muckpredicted);
  muckpredictedgraph->SetLineWidth(2);
  muckpredictedgraph->SetLineColor(2);
  muckpredictedgraph->Draw("SAME");

  TGraph * muckgraph2 = new TGraph(2,splitNum, muck2);
  muckgraph2->Draw("SAME");*/

  //these are the NEW graphs changing number of frames for several runs -- one run at a time

  // for run /fs/ess/PAS1977/StellarAnalysis/betUMa/UTC20211217/m12d17h01/T3T4Nolan:
  //max frames: 56702

  const int npts(5);
  double frames[npts] = {56702, 28351, 18901, 14176, 1000};
  double muck[npts] = {0.842982, 1.69106, 2.54414, 3.40232, 56.5393}; // *10^-9
  double muckmodel[npts] = {0.842982, 1.19216, 1.46009, 1.68596, 6.3487}; //also *10^-9

  TGraph* muckgraph = new TGraph(npts, frames, muck);
  muckgraph->SetTitle("Number of frames vs size of muck (red=predicted);number of frames;muck *10^-9");
  muckgraph->SetLineWidth(2);
  muckgraph->SetMinimum(0);
  muckgraph->Draw();

  TGraph* muckpredgraph = new TGraph(npts, frames, muckmodel);
  muckpredgraph->SetLineWidth(2);
  muckpredgraph->SetLineColor(2);
  muckpredgraph->Draw("SAME");
  /*
  const int npts2(3);
  double frames2[npts2] = {56702, 28351, 18901};
  double newmuck[npts2] = {0.815434, 0.815435, 0.815436};*/

  // 8.15434e-08  8.15435e-08 8.15436e-08

    //28351); // max = 56702 2.54414e-09  3.40232e-09

  // MUCK: 5.65393e-08  NEW MUCK: 8.16431e-08 1000 frames

  //MUCK: 7.63437e-10  NEW MUCK: 8.15434e-08  STD DEV: 5.97192e-08

  // MUCK: 8.42982e-10 NEW MUCK: 8.15434e-08 STD DEV: 5.97171e-08  56702 frames
  // MUCK: 1.69106e-09 NEW MUCK: 8.15435e-08 STD DEV: 5.96944e-08  28351 frames
  // MUCK: 3.40232e-09 NEW MUCK: 8.15437e-08 STD DEV: 5.96488e-08  14176 frames

  //for run  /fs/ess/PAS1977/StellarAnalysis/betUMa/UTC20211217/m12d17h05/T2T4Nolan:
  //max frames: 14176
  //for 1000 frames: MUCK: 1.7612e-08 NEW MUCK: 1.63044e-07
  //for max 14176 frames: MUCK: 1.1679e-09 NEW MUCK: 1.63038e-07
  //for 7088 frames: MUCK: 2.34199e-09 NEW MUCK: 1.63038e-07

  const int npts2(3);
  double frames2[npts] = {14176, 7088, 1000};
  double muck2[npts] = {1.1679, 2.34199, 17.612};
  double muckmodel2[npts] = {1.1679, 1.6517, 4.3973};

  TGraph* muckgraph2 = new TGraph(npts2, frames2, muck2);
  //muckgraph2->SetTitle("Number of frames vs size of muck (red=predicted);number of frames;muck *10^-9");
  muckgraph2->SetLineWidth(2);
  //muckgraph2->SetMinimum(0);
  muckgraph2->Draw("SAME");

  TGraph* muckpredgraph2 = new TGraph(npts2, frames2, muckmodel2);
  muckpredgraph2->SetLineWidth(2);
  muckpredgraph2->SetLineColor(2);
  muckpredgraph2->Draw("SAME");

  //for run /fs/ess/PAS1977/StellarAnalysis/betUMa/UTC20220313/m03d12h22/T3T4OSU:
  //max frames: 62592
  //for 7088 frames: MUCK: 5.02236e-09 NEW MUCK: 8.21616e-08
  //for max 62592 frames: MUCK: 5.34759e-10 NEW MUCK: 8.21609e-08

  //MUCK: 8.42982e-10 max num frames
  //1.69106e-09 half frames

}
