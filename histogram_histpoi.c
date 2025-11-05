void histogram_histpoi(){

TH1D hist("hist", ";N", 11, -0.5, 10.5);

TTree t;
t.ReadFile("histpoi.txt", "N/I:counts/I:prediction/D");


t.Draw("N >> hist", "counts", "HIST");


t.Draw("N", "prediction", "HISTSAME");
gPad->SaveAs("histogram_histpoi.png");
gSystem->Exit(0);

}