// goal: to quantify noise outside peak region : peak height to determine some points that should be included

void signalnoise(){

    const int ndir = 98; // number of directories
    int nwindows = 16; // number of window chunks
    int windowsize = 40; // width of window chunk
    TCanvas* d1prof = new TCanvas("","",1000,600);

    TString Dir[ndir] = {"UTC20211217/m12d16h23/T1T2OFF",   // these are all the definitely not-glitched directories for BetUma
                        "UTC20211217/m12d16h23/T1T3OFF",
                        "UTC20211217/m12d16h23/T1T4OFF",
                        "UTC20211217/m12d16h23/T2T3OFF",
                        "UTC20211217/m12d16h23/T2T4OFF",
                        "UTC20211217/m12d16h23/T3T4OFF",
                        "UTC20211217/m12d17h01/T1T2OFF",
                        "UTC20211217/m12d17h01/T1T3OFF",
                        "UTC20211217/m12d17h01/T1T4OFF",
                        "UTC20211217/m12d17h01/T2T3OFF", //10
                        "UTC20211217/m12d17h01/T2T4OFF",
                        "UTC20211217/m12d17h01/T3T4OFF",
                        "UTC20211217/m12d17h03/T1T2OFF",
                        "UTC20211217/m12d17h03/T1T3OFF",
                        "UTC20211217/m12d17h03/T1T4OFF",
                        "UTC20211217/m12d17h03/T2T3OFF",
                        "UTC20211217/m12d17h03/T2T4OFF",
                        "UTC20211217/m12d17h03/T3T4OFF",
                        "UTC20211217/m12d17h05/T1T2OFF",
                        "UTC20211217/m12d17h05/T1T3OFF", //20
                        "UTC20211217/m12d17h05/T1T4OFF",
                        "UTC20211217/m12d17h05/T2T3OFF",
                      //  "UTC20211217/m12d17h05/T2T4OFF", <-- this JustShift is glitched!! the HBTPeakWithFit is alright
                        "UTC20211217/m12d17h05/T3T4OFF",
                        "UTC20220212/m02d11h19/T1T2OFF",
                        "UTC20220212/m02d11h19/T1T3OFF",
                        "UTC20220212/m02d11h19/T1T4OFF",
                        "UTC20220212/m02d11h19/T2T3OSU",
                        "UTC20220212/m02d11h19/T2T4OFF",
                        "UTC20220212/m02d11h19/T3T4OFF", //30
                        "UTC20220212/m02d11h20/T1T2OFF",
                        "UTC20220212/m02d11h20/T1T3OFF",
                        "UTC20220212/m02d11h20/T1T4OFF",
                        "UTC20220212/m02d11h20/T2T3OSU",
                        "UTC20220212/m02d11h20/T2T4OFF",
                        "UTC20220212/m02d11h20/T3T4OFF",
                        "UTC20220212/m02d11h23/T1T2OFF",
                        "UTC20220212/m02d11h23/T1T3OFF",
                        "UTC20220212/m02d11h23/T1T4OFF",
                        "UTC20220212/m02d11h23/T2T3OSU", //40
                        "UTC20220212/m02d11h23/T2T4OFF",
                        "UTC20220212/m02d11h23/T3T4OFF",
                        "UTC20220212/m02d12h01/T1T2OFF",
                        "UTC20220212/m02d12h01/T1T3OFF",
                        "UTC20220212/m02d12h01/T1T4OFF",
                        "UTC20220212/m02d12h01/T2T3OSU",
                        "UTC20220212/m02d12h01/T2T4OFF",
                      //  "UTC20220212/m02d12h01/T3T4OFF", <-- this JustShift also glitched!!
                        "UTC20220212/m02d12h03/T1T2OFF",
                        "UTC20220212/m02d12h03/T1T3OFF", //50
                        "UTC20220212/m02d12h03/T1T4OFF",
                        "UTC20220212/m02d12h03/T2T3OSU",
                        "UTC20220212/m02d12h03/T2T4OSU",
                        "UTC20220212/m02d12h03/T3T4OFF",
                        "UTC20220214/m02d13h19/T1T2OFF",
                        "UTC20220214/m02d13h19/T1T3OFF",
                        "UTC20220214/m02d13h19/T1T4OFF",
                        "UTC20220214/m02d13h19/T2T3OSU",
                        "UTC20220214/m02d13h19/T2T4OFF",
                        "UTC20220214/m02d13h19/T3T4OFF", //60
                        "UTC20220214/m02d13h21/T1T2OFF",
                        "UTC20220214/m02d13h21/T1T3OFF",
                        "UTC20220214/m02d13h21/T1T4OFF",
                        "UTC20220214/m02d13h21/T2T3OSU",
                        "UTC20220214/m02d13h21/T2T4OFF",
                        "UTC20220214/m02d13h21/T3T4OFF",
                        "UTC20220214/m02d13h23/T1T2OFF",
                        "UTC20220214/m02d13h23/T1T3OFF",
                        "UTC20220214/m02d13h23/T1T4OFF",
                        "UTC20220214/m02d13h23/T2T3OSU", //70
                        "UTC20220214/m02d13h23/T2T4OFF",
                        "UTC20220214/m02d13h23/T3T4OFF",
                        "UTC20220214/m02d14h01/T1T2OFF",
                        "UTC20220214/m02d14h01/T1T3OFF",
                        "UTC20220214/m02d14h01/T1T4OFF",
                        "UTC20220214/m02d14h01/T2T3OSU",
                        "UTC20220214/m02d14h01/T2T4OFF",
                        "UTC20220214/m02d14h01/T3T4OFF",
                        "UTC20220214/m02d14h03/T1T2OFF",
                        "UTC20220214/m02d14h03/T1T3OFF", //80
                        "UTC20220214/m02d14h03/T1T4OFF",
                        "UTC20220214/m02d14h03/T2T3OSU",
                        "UTC20220214/m02d14h03/T2T4OFF",
                        "UTC20220214/m02d14h03/T3T4OFF",
                        "UTC20220313/m03d12h22/T1T2OFF",
                        "UTC20220313/m03d12h22/T1T3OFF",
                        "UTC20220313/m03d12h22/T1T4OFF",
                        "UTC20220313/m03d12h22/T2T3OFF",
                        "UTC20220313/m03d12h22/T2T4OSU",
                        "UTC20220313/m03d12h22/T3T4OSU", //90
                        "UTC20220313/m03d13h01/T1T2OFF",
                        "UTC20220313/m03d13h01/T1T3OFF",
                        "UTC20220313/m03d13h01/T1T4OFF",
                        "UTC20220313/m03d13h01/T2T3OFF",
                        "UTC20220313/m03d13h01/T2T4OSU",
                        "UTC20220313/m03d13h01/T3T4OSU",
                        "UTC20220511/m05d10h21/T1T2OFF",
                        "UTC20220511/m05d10h21/T1T3OFF",
                        "UTC20220511/m05d10h21/T1T4OFF",
                        "UTC20220511/m05d10h21/T2T3OFF",};  // all directories of bet UMa

  d1prof->Print("d1profs.pdf[");
  TCanvas* hists = new TCanvas("","",1000,600);
  hists->Divide(4,4);

    // this is the fitting function - identical to the one used for fitting the actual HBT peaks
    TF1* gausfit = new TF1("gausfit","([0]*exp(-pow((x-[1])/[2],2)/2.0))/([2]*sqrt(2*TMath::Pi()))",-20,20);
    gausfit->SetParName(0,"area");          gausfit->SetParameter(0,0.0);
    gausfit->SetParName(1,"#tau_{0}");      gausfit->SetParameter(1,0.0);       gausfit->SetParLimits(1,-10,10);
    gausfit->SetParName(2,"#sigma");        gausfit->SetParameter(2,4.5);       gausfit->SetParLimits(2,3.0,6.0);

    ofstream avgnoise;
    avgnoise.open ("AvgNoiseByRun.txt");

    // loop over each directory - getting the correlations for each HBT peak and measuring the noise for each with fits and RMS
    for (int i=0; i<ndir; i++){

        // read in the TProfile2D, project to a TProfile (1D), and draw the full cf
        d1prof->cd();
        TProfile2D* origHBTpeak2D;
        TProfile* origHBTpeak;
        TFile *AnalysisFile = new TFile("/fs/ess/PAS1977/StellarAnalysis/betUMa/"+Dir[i]+"/Analysis.root","READONLY"); // must add the strings
        AnalysisFile->GetObject("JustShift",origHBTpeak2D);
        origHBTpeak = origHBTpeak2D->ProfileX("", 1, -1);
        origHBTpeak->SetTitle("/betUMa/"+Dir[i]+"/");
        origHBTpeak->Draw();
        d1prof->Print("d1profs.pdf"); // draw the full HBT peak

        // now we separate the off-peak areas into small chunks, and fit to each as if to an HBT peak
        double areasum(0.0);
        double RMSsum(0.0);

        // start of the sub-loop
        int bininc = 27; // start of the first window, increments in the loop
        for(int j=0; j<nwindows; j++){
            TH1D* noisechunk = new TH1D("noisechunk","Noise hist",windowsize,0-0.5*windowsize,0+0.5*windowsize);
            gausfit->SetParameter(0,0.0);       gausfit->SetParameter(1,0.0);       gausfit->SetParameter(2,4.5);
            if(j!=8){
                bininc=bininc-20;
                for(int k=1; k<=windowsize; k++){
                    noisechunk->SetBinContent(k,origHBTpeak->GetBinContent(bininc));
                    noisechunk->SetBinError(k,origHBTpeak->GetBinError(bininc));
                    bininc++;
                }
            }
            else if(j==8){ // jump over the peak region and reset bininc
                bininc=307;
                for(int k=1; k<=windowsize; k++){
                    noisechunk->SetBinContent(k,origHBTpeak->GetBinContent(bininc));
                    noisechunk->SetBinError(k,origHBTpeak->GetBinError(bininc));
                    bininc++;
                }
            }
            hists->cd(j+1);
            noisechunk->Draw();
            noisechunk->Fit(gausfit);
            double histarea = gausfit->GetParameter(0);
            areasum = areasum + abs(histarea);
        }

         // ok - now RMS just to compare
        double binval(0.0);
        double RMSinc(0);
        for (int r=37; r<=476; r++){
            binval = origHBTpeak->GetBinContent(r);
            RMSsum = RMSsum + pow(binval, 2);
            binval = 0;
            RMSinc++;
        }
        double RMS = RMSsum/RMSinc;
        RMS = sqrt(RMS);

        // print area mean and RMS to a text file by directory and draw the 16 histograms with their fits
        avgnoise << "betUMa/" << Dir[i] << "  area mean: " << areasum/nwindows << "     RMS: " << RMS << endl;
        hists->Print("d1profs.pdf");
    }

    avgnoise.close();
    d1prof->Print("d1profs.pdf]");

}
