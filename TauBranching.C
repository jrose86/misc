// graphs of Tau window and delta Tau start vs % branching for A/sigma 2,1,0.5

void TauBranching(){

  //Percent Branched for Tau Start WITHOUT flags cut
  double pcbST_as2[21] =   {17.212, 8.508, 3.652, 1, 0.208, 0.052, 0.012, 0.012, 0.012, 0.004, 0.012, 0.004, 0.012, 0.004, 0.016, 0.036, 0.288, 1.136, 3.764, 8.8, 17.308};
  double pcbST_as1[21] =   {42.236, 29.98, 22.02, 14.312, 8.644, 5.136, 3.232, 2.372, 2.088, 2.096, 2.128, 2.016, 2.048, 2.364, 3.232, 5.036, 8.808, 14.796, 22.328, 29.756, 42.468};
  double pcbST_as0p5[21] = {62.116, 49.2, 41.604, 31.98, 24.008, 17.272, 12.42, 9.492, 7.76, 7.052, 7.024, 7.184, 7.852, 9.092, 12.64, 16.924, 23.936, 31.772, 41.4, 49.384, 62.516};

  //Percent Branched for Tau Start WITH flags cut
  double pcbSTNF_as2[21] = {1.12093, 0.692514, 0.389829, 0.129757, 0.0278286, 0.0281536, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0170492, 0.0225274, 0.136173, 0.375571, 0.717492, 1.15093};
  double pcbSTNF_as1[21] = {10.2137, 10.3037, 7.51784, 5.45536, 3.95467, 2.70087, 1.79545, 1.21883, 1.10715, 0.837662, 1.01353, 0.831641, 1.07787, 1.22881, 1.63151, 2.65318, 4.0337, 5.45517, 6.98345, 9.18644, 10.2421};
  double pcbSTNF_as0p5[21] = {31.3921, 33.4428, 31.5179, 25.5357, 22.1124, 19.1247, 16.3972, 12.7177, 11.3602, 10.2603, 10.3501, 10.5302, 11.1723, 12.8644, 16.5175, 19.0548, 22.2059, 25.958, 30.6864, 33.7225, 32.5473};

  //Percent Branched for delta Tau WITHOUT flags cut
  double pcbDT_as2[26] =// {0, 0, 0, 0, 0.04, 0.216, 1.072, 3.616, 9.308, 16.948, 16.14, 16.616, 17.292, 17.732, 17.6, 18.14, 18.328, 18.988, 18, 18.548, 18.736, 18.704, 18.652, 18.892, 18.288, 18.8};
    {0, 0, 0, 0, 0, 0, 0, 0, 3.768, 8.472, 15.884, 17.184, 17.092, 17.456, 17.644, 18.28, 18.916, 18.36, 18.556, 18.784, 18.16, 18.572, 18.492, 18.936, 18.848, 18.688};
  double pcbDT_as1[26] = {0, 0, 0, 0, 0, 0, 0, 0, 20.784, 30.08, 39.616, 41.308, 40.764, 42.004, 42.612, 44.392, 44.84, 45.032, 44.924, 45.388, 44.524, 44.38, 45.028, 45.312, 45.396, 46.252};
  double pcbDT_as0p5[26] = {0, 0, 0, 0, 0, 0, 0, 0, 39.98, 49.772, 58.076, 59.1, 59.664, 60.112, 60.488, 61.972, 62.368, 62.3, 62.932, 62.756, 62.476, 63.044, 63.436, 63.216, 62.984, 63.596};

  //Percent Branched for delta Tau WITH flags cut
  double pcbDTNF_as2[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0.168112, 0.807398, 1.99072, 3.04015, 3.47144, 3.55573, 3.51307, 2.57653, 2.54802, 2.59571, 2.46944, 2.81949, 2.21454, 2.62967, 2.57385, 2.7465, 2.73545, 2.582072};
  double pcbDTNF_as1[26] = {0, 0, 0, 0, 0, 0, 0, 0, 6.04964, 9.64405, 13.83, 17.2572, 16.6235, 17.0832, 16.2702, 13.0096, 12.1621, 12.246, 12.957, 12.7297, 12.4558, 12.5631, 13.536, 12.8833, 12.6928, 13.7066};
  double pcbDTNF_as0p5[26] = {0, 0, 0, 0, 0, 0, 0, 0, 28.3542, 33.1842, 37.6136, 41.4423, 41.8847, 41.4739, 41.0377, 35.2395, 34.3249, 34.2068, 36.9374, 35.7782, 37.2725, 36.9462, 36.0597, 36.7487, 38.3284, 39.3516};

  double deltaTau[26] = {2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 120.0, 140.0, 160.0, 200.0};
  double TauStart[21] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};

TCanvas* tc = new TCanvas("tc","tc",1000,800);

TGraph* branchingVTauStart = new TGraph(21, TauStart, pcbST_as2);
 branchingVTauStart->SetLineColor(2);
 branchingVTauStart->SetLineWidth(2);
TGraph* branchingVTauStart2 = new TGraph(21, TauStart, pcbST_as1);
 branchingVTauStart2->SetLineColor(3);
 branchingVTauStart2->SetLineWidth(2);
TGraph* branchingVTauStart3 = new TGraph(21, TauStart, pcbST_as0p5);
 branchingVTauStart3->SetLineColor(4);
 branchingVTauStart3->SetLineWidth(2);

 TLegend * legend = new TLegend(0.7,0.85,0.95,0.95);
    legend->SetHeader("A/#sigma","C"); // option "C" allows to center the header
    legend->AddEntry(branchingVTauStart,"A/#sigma = 2.0","l");
    legend->AddEntry(branchingVTauStart2,"A/#sigma = 1.0","l");
    legend->AddEntry(branchingVTauStart3,"A/#sigma = 0.5","l");
    legend->SetTextSize(0.03);

 branchingVTauStart->Draw();
 branchingVTauStart2->Draw("SAME");
 branchingVTauStart3->Draw("SAME");
 legend->Draw("SAME");

 branchingVTauStart->SetTitle("Branching vs. Tau Start;Tau Start;% Branched");

 // TCanvas* tc2 = new TCanvas("tc2","tc2",1000,800);

TGraph* branchingVTauStartNF = new TGraph(21, TauStart, pcbSTNF_as2);
 branchingVTauStartNF->SetLineColor(2);
 branchingVTauStartNF->SetLineWidth(2);
 branchingVTauStartNF->SetLineStyle(2);
 TGraph* branchingVTauStartNF2 = new TGraph(21, TauStart, pcbSTNF_as1);
 branchingVTauStartNF2->SetLineColor(3);
 branchingVTauStartNF2->SetLineWidth(2);
 branchingVTauStartNF2->SetLineStyle(2);
TGraph* branchingVTauStartNF3 = new TGraph(21, TauStart, pcbSTNF_as0p5);
 branchingVTauStartNF3->SetLineColor(4);
 branchingVTauStartNF3->SetLineWidth(2);
 branchingVTauStartNF3->SetLineStyle(2);

  legend->AddEntry(branchingVTauStartNF,"A/#sigma = 2.0, flags cut","l");
    legend->AddEntry(branchingVTauStartNF2,"A/#sigma = 1.0, flags cut","l");
    legend->AddEntry(branchingVTauStartNF3,"A/#sigma = 0.5, flags cut","l");

 /*TLegend * legend2 = new TLegend(0.7,0.85,0.95,0.95);
    legend2->SetHeader("A/#sigma","C"); // option "C" allows to center the header
    legend2->AddEntry(branchingVTauStartNF,"A/#sigma = 2.0","l");
    legend2->AddEntry(branchingVTauStartNF2,"A/#sigma = 1.0","l");
    legend2->AddEntry(branchingVTauStartNF3,"A/#sigma = 0.5","l");
    legend2->SetTextSize(0.04);*/

 branchingVTauStartNF3->Draw("SAME");
 branchingVTauStartNF2->Draw("SAME");
 branchingVTauStartNF->Draw("SAME");
 //legend2->Draw("SAME");

 //branchingVTauStartNF3->SetTitle("Branching vs. Tau Start, flagged points cut;Tau Start;% Branched");

 //========================================================================================

 TCanvas* tc3 = new TCanvas("tc3","tc3",1000,800);
 TGraph* branchingVDelTau = new TGraph(26, deltaTau, pcbDT_as2);
 branchingVDelTau->SetLineColor(2);
 branchingVDelTau->SetLineWidth(2);
 TGraph* branchingVDelTau2 = new TGraph(26, deltaTau, pcbDT_as1);
 branchingVDelTau2->SetLineColor(3);
 branchingVDelTau2->SetLineWidth(2);
 TGraph* branchingVDelTau3 = new TGraph(26, deltaTau, pcbDT_as0p5);
 branchingVDelTau3->SetLineColor(4);
 branchingVDelTau3->SetLineWidth(2);

 TLegend * legend3 = new TLegend(0.75,0.9,1.0,0.95);
    legend3->SetHeader("A/#sigma","C"); // option "C" allows to center the header
    legend3->AddEntry(branchingVDelTau,"A/#sigma = 2.0","l");
    legend3->AddEntry(branchingVDelTau2,"A/#sigma = 1.0","l");
    legend3->AddEntry(branchingVDelTau3,"A/#sigma = 0.5","l");
    legend3->SetTextSize(0.03);

 branchingVDelTau3->Draw();
 branchingVDelTau2->Draw("SAME");
 branchingVDelTau->Draw("SAME");
 legend3->Draw("SAME");

 branchingVDelTau3->SetTitle("Branching vs. Tau Window;width of limits;% Branched");

 //TCanvas* tc4 = new TCanvas("tc4","tc4",1000,800);

TGraph* branchingVDelTauNF = new TGraph(26, deltaTau, pcbDTNF_as2);
 branchingVDelTauNF->SetLineColor(2);
 branchingVDelTauNF->SetLineWidth(2);
 branchingVDelTauNF->SetLineStyle(2);
TGraph* branchingVDelTauNF2 = new TGraph(26, deltaTau, pcbDTNF_as1);
 branchingVDelTauNF2->SetLineColor(3);
 branchingVDelTauNF2->SetLineWidth(2);
 branchingVDelTauNF2->SetLineStyle(2);
 TGraph* branchingVDelTauNF3 = new TGraph(26, deltaTau, pcbDTNF_as0p5);
 branchingVDelTauNF3->SetLineColor(4);
 branchingVDelTauNF3->SetLineWidth(2);
 branchingVDelTauNF3->SetLineStyle(2);

  legend3->AddEntry(branchingVDelTauNF,"A/#sigma = 2.0, flags cut","l");
    legend3->AddEntry(branchingVDelTauNF2,"A/#sigma = 1.0, flags cut","l");
    legend3->AddEntry(branchingVDelTauNF3,"A/#sigma = 0.5, flags cut","l");

 /*TLegend * legend4 = new TLegend(0.75,0.9,1.0,0.95);
    legend4->SetHeader("A/#sigma","C"); // option "C" allows to center the header
    legend4->AddEntry(branchingVDelTauNF,"A/#sigma = 2.0","l");
    legend4->AddEntry(branchingVDelTauNF2,"A/#sigma = 1.0","l");
    legend4->AddEntry(branchingVDelTauNF3,"A/#sigma = 0.5","l");
    legend4->SetTextSize(0.04);*/

 branchingVDelTauNF3->Draw("SAME");
 branchingVDelTauNF2->Draw("SAME");
 branchingVDelTauNF->Draw("SAME");
 //legend4->Draw("SAME");

 //branchingVDelTauNF3->SetTitle("Branching vs. Tau Window, flagged points cut;width of limits;% Branched");

}
