// graphs of run time changing with different parameters

void SpecSimpleGraphs(){

  /*
  double gulpSize[4] =  {17.0,  18.0,  19.0,  20.0};
  double gulpTimes[4] = {22.37, 19.23, 17.05, 14.32};

  TCanvas* tc1 = new TCanvas("","",1200,900);
  TGraph* gulpSizeTimeGraph = new TGraph(4, gulpSize, gulpTimes);

  gulpSizeTimeGraph->SetTitle("Gulp Size vs Run Time;gulp size power of 2;time (mins)");
  gulpSizeTimeGraph->SetMarkerStyle(20);
  gulpSizeTimeGraph->Draw();

  double threadsOnly[14] =     {7.0,   14.0,  24.0,  26.0,  27.0,  29.0,  30.0, 31.0,  32.0, 36.0,  40.0,  48.0,  56.0,  57.0};
  double threadsTimes[14] =    {62.03, 30.83, 16.07, 15.73, 17.05, 18.48, 9.62, 10.08, 9.92, 10.07, 10.37, 12.08, 13.90, 14.13};
  double threadsCPUtimes[14] = {601,   1196,  1971,  2149,  2148,  2148,  2110, 2098,  2155, 2283,  2389,  2431,  2454,  2466};

  double core14threads[4] =         {13.0,  28.0,  30.0,  36.0};
  double core14threadsTimes[4] =    {33.85, 27.92, 16.17, 17.38};
  double core14threadsCPUtimes[4] = {1009,  1227,  1144,  1244};

  double core7threads[3] =         {6.0,   14.0,  30.0};
  double core7threadsTimes[3] =    {70.22, 52.67, 26.6};
  double core7threadsCPUtimes[3] = {498,   639,   657};

  TCanvas* tc2 = new TCanvas("","",1200,900);
  TGraph* threadsOnlyTimeGraph = new TGraph(14, threadsOnly, threadsTimes);
  TGraph* core14threadsTimeGraph = new TGraph(4, core14threads, core14threadsTimes);
  TGraph* core7threadsTimeGraph = new TGraph(3, core7threads, core7threadsTimes);

  threadsOnlyTimeGraph->SetTitle("Changed Number of Worker Threads Only;number of worker threads;time (mins)");
  threadsOnlyTimeGraph->SetMarkerStyle(20);
  threadsOnlyTimeGraph->Draw();
  threadsOnlyTimeGraph->SetMaximum(75.0);
  core14threadsTimeGraph->SetMarkerStyle(20);
  core14threadsTimeGraph->SetMarkerColor(2);
  core14threadsTimeGraph->SetLineColor(2);
  core14threadsTimeGraph->Draw("LPSAME");
  core7threadsTimeGraph->SetMarkerStyle(20);
  core7threadsTimeGraph->SetMarkerColor(4);
  core7threadsTimeGraph->SetLineColor(4);
  core7threadsTimeGraph->Draw("LPSAME");

  TCanvas* tc3 = new TCanvas("","",1200,900); // do divided by #cpus
  TGraph* threadsOnlyCPUtimeGraph = new TGraph(14, threadsOnly, threadsCPUtimes);
  TGraph* core14threadsCPUtimeGraph = new TGraph(4, core14threads, core14threadsCPUtimes);
  TGraph* core7threadsCPUtimeGraph = new TGraph(3, core7threads, core7threadsCPUtimes);

  threadsOnlyCPUtimeGraph->SetTitle("Changed Number of Worker Threads Only;number of worker threads;CPU %");
  threadsOnlyCPUtimeGraph->SetMarkerStyle(20);
  threadsOnlyCPUtimeGraph->Draw();
  core14threadsCPUtimeGraph->SetMarkerStyle(20);
  core14threadsCPUtimeGraph->SetMarkerColor(2);
  core14threadsCPUtimeGraph->SetLineColor(2);
  core14threadsCPUtimeGraph->Draw("LPSAME");
  core7threadsCPUtimeGraph->SetMarkerStyle(20);
  core7threadsCPUtimeGraph->SetMarkerColor(4);
  core7threadsCPUtimeGraph->SetLineColor(4);
  core7threadsCPUtimeGraph->Draw("LPSAME");*/

  /*
  const int size(20);
  double numThreads[size] =   {7.0,  10.0, 12.0, 13.0, 14.0, 15.0, 15.0, 16.0, 16.0, 20.0, 24.0, 27.0, 28.0, 29.0, 30.0, 36.0, 56.0, 72.0, 80.0, 120.0};
  double threadsTimes[size] = {8.27, 6.72, 4.93, 4.52, 4.27, 5.30, 4.07, 4.93, 3.88, 3.32, 3.18, 2.92, 2.87, 2.88, 2.93, 2.43, 2.2, };
  double CPUpc[size] =        {22.6, 29.0, 38.8, 42.3, 45.0, 39.0, 47.3, 38.7, 50.0, 58.6, 62.4, 68.8, 68.9, 66.4, 67.7, 78.1, 85.7};

  TCanvas* tc1 = new TCanvas("","",1200,900);
  TGraph* CPU28graph = new TGraph(size,numThreads,threadsTimes);
  CPU28graph->SetTitle("28 CPUs, varying number of worker threads;number of worker threads;time (mins)");
  CPU28graph->SetMarkerStyle(20);
  CPU28graph->Draw();

  TCanvas* tc2 = new TCanvas("","",1200,900);
  tc2->cd();
  TGraph* CPUtime = new TGraph(size,numThreads,CPUpc);
  CPUtime->SetTitle("CPU time/#CPUs (28), varying number of worker threads;number of worker threads;CPU%/#CPUS");
  CPUtime->SetMarkerStyle(20);
  CPUtime->SetMinimum(0.0);
  CPUtime->SetMaximum(100.0);
  CPUtime->Draw();
  */

  /*
  // These are testing with/without using the -Ofast compiling flag

  const int l(3);
  double nThreads[l] = {20.0, 28.0, 32.0};
  double ttimes[l] = {44, 35, 34};
  double ttimesnof[l] = {147, 109, 111};
  double utimes[l] = {567, 508, 514};
  double utimesnof[l] = {2363, 2320, 2379};


  TCanvas* tc3 = new TCanvas("","",1800,700);
  tc3->Divide(2,1);
  TGraph* ofast = new TGraph(l,nThreads,ttimes);
  TGraph* noOfast = new TGraph(l,nThreads,ttimesnof);

  tc3->cd(1);
  ofast->SetTitle("real times with/without -Ofast flag for varying num threads (with=black,without=blue);number worker threads;time (secs)");
  ofast->SetMarkerStyle(20);
  ofast->SetMinimum(0.0);
  ofast->SetMaximum(150);
  ofast->Draw();
  noOfast->SetMarkerStyle(20);
  noOfast->SetMarkerColor(4);
  noOfast->SetLineColor(4);
  noOfast->Draw("PLSAME");

  TGraph* ofastUT = new TGraph(l,nThreads,utimes);
  TGraph* noOfastUT = new TGraph(l,nThreads,utimesnof);
  tc3->cd(2);

  ofastUT->SetTitle("user times with/without -Ofast flag for varying num threads (with=black,without=blue);number worker threads;user time");
  ofastUT->SetMarkerStyle(20);
  ofastUT->SetMinimum(0.0);
  ofastUT->SetMaximum(2500);
  ofastUT->Draw();
  noOfastUT->SetMarkerStyle(20);
  noOfastUT->SetMarkerColor(4);
  noOfastUT->SetLineColor(4);
  noOfastUT->Draw("PLSAME");
  */

  // these are for varying number of threads WITH -OFAST

  //for 28 cores: (gulp = 2^19)
  const int l(10);
  double nThreads[l] = {4,     8,     16,    20,    24,    28,    32,    36,    40,    50};   //,  80,    100};     // number of threads
  double etimes[l] =   {5.19,  3.12,  1.62,  1.35,  1.16,  0.98,  0.93,  0.83,  0.73,  0.59}; //, 0.55,  0.55};  // "elapsed" time (wall clock time)
  double utimes[l] =   {59952, 68276, 68311, 67720, 66173, 62001, 60623, 54903, 50764, 45763}; //, 45615, 44977}; // "user" time (cpu time)

  //for 28 cores, changed gulp size to 2^18 to do higher num threads:
  const int l2(13);
  double nThreadsG18[l2] = {4,     8,     16,    20,    24,    28,    32,    36,    40,    50,    60,    80,    100};
  double etimesG18[l2] =   {5.56,  3.08,  1.67,  1.39,  1.16,  0.99,  0.92,  0.90,  0.80,  0.77,  0.66,  0.55,  0.55};
  double utimesG18[l2] =   {57895, 61813, 62654, 59754, 56603, 53483, 50245, 51181, 49651, 49837, 46336, 45615, 44977};

  //for 20 cores: (gulp = 2^19)
  double th20core[2] =      {20,    28};    // number of threads
  double etimes20core[2]  = {1.52,  1.14};  // "elapsed" time
  double utimes20core[2] =  {65135, 53984}; // "user" time


  TCanvas* tc3 = new TCanvas("","",1800,700);
  tc3->Divide(2,1);
  TGraph* ofast = new TGraph(l,nThreads,etimes);               // 28 cores, threads vs elapsed time
  TGraph* ofastUT = new TGraph(l,nThreads,utimes);             // 28 cores, threads vs user time
  TGraph* ofast20core = new TGraph(2,th20core,etimes20core);   // 20 cores, threads vs elapsed time
  TGraph* ofast20coreUT = new TGraph(2,th20core,utimes20core); // 20 cores, threads vs user time
  TGraph* ofastG18 = new TGraph(l2,nThreadsG18,etimesG18);     // 28 cores, threads vs elapsed time, gulp size 2^18 for larger N threads
  TGraph* ofastG18UT = new TGraph(l2,nThreadsG18,utimesG18);   // 28 cores, threads vs user time, gulp size 2^18

  TLine* runtime = new TLine(-1, 0.98, 100, 0.98);// horiz line at the time length of the run

  tc3->cd(1);
  ofastG18->SetMarkerStyle(20);
  ofastG18->SetMarkerColor(4);
  ofastG18->SetLineColor(4);
  ofastG18->SetMinimum(0.0);
  ofastG18->SetMaximum(7);
  ofastG18->SetTitle("real times with -Ofast for varying num threads;number worker threads;time (hours)");
  ofastG18->Draw();
  ofast->SetMarkerStyle(20);
  ofast->Draw("PLSAME");
  ofast20core->SetMarkerStyle(20);
  ofast20core->SetMarkerColor(2);
  ofast20core->SetLineColor(2);
  ofast20core->Draw("PLSAME");
  runtime->SetLineColor(2);
  runtime->Draw("SAME");

  tc3->cd(2);
  ofastG18UT->SetMarkerStyle(20);
  ofastG18UT->SetMarkerColor(4);
  ofastG18UT->SetLineColor(4);
  ofastG18UT->SetMinimum(0.0);
  ofastG18UT->SetMaximum(70000);
  ofastG18UT->SetTitle("user times with -Ofast for varying num threads;number worker threads;user time");
  ofastG18UT->Draw();
  ofastUT->SetMarkerStyle(20);
  ofastUT->Draw("PLSAME");
  ofast20coreUT->SetMarkerStyle(20);
  ofast20coreUT->SetMarkerColor(2);
  ofast20coreUT->SetLineColor(2);
  ofast20coreUT->Draw("PLSAME");

}
