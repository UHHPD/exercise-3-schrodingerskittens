void histogram_hist() {
    
    TH1D hist("hist", ";N", 11, 0, 30);


    TTree t;
    t.ReadFile("hist.txt", "index/I:counts/I");


    t.Draw("index >> hist", "counts", "HIST");

    gPad->SaveAs("histogram_hist.png");
    gSystem->Exit(0);

}