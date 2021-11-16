{
	auto canvas = new TCanvas("canvas","",900,900);
	//gStyle->SetOptStat(0);
	canvas->Divide(2,2);

	auto file_nest = TFile::Open("qnest.root");
	auto tree_nest = (TTree*)file_nest->Get("mcTree");

	auto file_qs1r = TFile::Open("qs1raw.root");
	auto tree_qs1r = (TTree*)file_qs1r->Get("mcTree");

	int c=0;
	
	canvas->cd(++c);
	TH2F nnr("nnr","NEST NR", 35, 0, 35, 100, 0, 600);
	tree_nest->Draw("photonNR:energyNR>>nnr","","COLZ");
	
/*	const int rd_range = (rt==0)?600:600;	// x10^2 mm
	const int rd_nbins = 100;
	TH2F rd("rd","gen. y:x", rd_nbins, -rd_range, rd_range, rd_nbins, -rd_range, rd_range);
	//rd.GetXaxis()->SetTitle("primaryT");
	//h.GetYaxis()->SetTitle("events");
	rd.SetLineColor((rt==0)?kRed:kBlue);
	rd.SetLineWidth(1);
	rd.SetFillStyle((rt==0)?3354:3345);
	rd.SetFillColor((rt==0)?kRed:kBlue);
	rd.SetFillColorAlpha((rt==0)?kRed:kBlue, 0.35);
	tree_nest->Draw("photonNR:energyNR","","COLZ");
	//rd.SetDirectory(0);
	//rd.Draw();
*/
	canvas->cd(++c);
	TH2F ner("ner","NEST ER", 10, 0, 10, 100, 0, 350);
	tree_nest->Draw("photonER:energyER>>ner","","COLZ");

/*	const int hi_range = (rt==0)?600:600;
	const int hi_nbins = 100;
	TH2F hi("hi","gen. x:z", hi_nbins, -hi_range, hi_range, 150, -1000, 500);
	//hi.GetXaxis()->SetTitle("primaryZ");
	//h.GetYaxis()->SetTitle("events");
	hi.SetLineColor((rt==0)?kRed:kBlue);
	hi.SetLineWidth(3);
	hi.SetMarkerSize(3);
	hi.SetFillStyle((rt==0)?3354:3345);
	hi.SetFillColor((rt==0)?kRed:kBlue);
	hi.SetFillColorAlpha((rt==0)?kRed:kBlue, 0.35);
	tree_nest->Draw("photonER:energyER","","COLZ");
*/

	canvas->cd(++c);
	TH2F qnr("qnr","QS1R NR", 35, 0, 35, 100, 0, 600);
	tree_qs1r->Draw("photonNR:energyNR>>qnr","","COLZ");

	canvas->cd(++c);
	TH2F qer("qer","QS1R ER", 10, 0, 10, 100, 0, 350);
	tree_qs1r->Draw("photonER:energyER>>qer","","COLZ");

	//hi.SetDirectory(0);
	//hi.Draw();
	
	//canvas->cd(++c);
	//tree->Draw("nPMTHits");

	//canvas->cd(++c);
	//tree->Draw("PmtNumber");
	
	//canvas->cd(++c);
	//tree->Draw("Photons");

	//canvas->cd(++c);
	//tree->Draw("PositionX");

	//canvas->cd(++c);
	//tree->Draw("PositionY");
	
	//canvas->cd(++c);
	//tree->Draw("PositionZ");
	
	//canvas->cd(++c);
	//tree->Draw("TimeGlobal");
	
	//canvas->cd(++c);
	//tree->Draw("TimeLocal");
	
	//canvas->cd(++c);
	//tree->Draw("TimeProper");
/*
	canvas->cd(++c);
	const int ro_range = (rt==0)?60:60;	// x10^2 mm
	const int ro_nbins = 50;
	TH2F ro("ro","det. x:y:top", ro_nbins, -ro_range, ro_range, ro_nbins, -ro_range, ro_range);
	//ro.GetXaxis()->SetTitle("primaryT");
	//h.GetYaxis()->SetTitle("events");
	ro.SetLineColor((rt==0)?kRed:kBlue);
	ro.SetLineWidth(3);
	ro.SetFillStyle((rt==0)?3354:3345);
	ro.SetFillColor((rt==0)?kRed:kBlue);
	ro.SetFillColorAlpha((rt==0)?kRed:kBlue, 0.35);
	tree->Draw("PositionY:PositionX>>ro","PositionZ>-50","COLZ");
	//ro.SetDirectory(0);
	//ro.Draw();

	canvas->cd(++c);
	const int rp_range = (rt==0)?60:60;	// x10^2 mm
	const int rp_nbins = 50;
	TH2F rp("rp","det. x:y:bottom", rp_nbins, -rp_range, rp_range, rp_nbins, -rp_range, rp_range);
	//rp.GetXaxis()->SetTitle("primaryT");
	//h.GetYaxis()->SetTitle("events");
	rp.SetLineColor((rt==0)?kRed:kBlue);
	rp.SetLineWidth(3);
	rp.SetFillStyle((rt==0)?3354:3345);
	rp.SetFillColor((rt==0)?kRed:kBlue);
	rp.SetFillColorAlpha((rt==0)?kRed:kBlue, 0.35);
	tree->Draw("PositionY:PositionX>>rp","PositionZ<-50","COLZ");
	//rp.SetDirectory(0);
	//rp.Draw();
*/
	/*
	canvas->cd(++c);
	const int ho_range = (rt==0)?100:100;
	TH1I ho("ho","PositionZ", ho_range, 0, ho_range);
	//ho.GetXaxis()->SetTitle("TimeGlobal");
	//h.GetYaxis()->SetTitle("events");
	ho.SetLineColor((rt==0)?kRed:kBlue);
	ho.SetLineWidth(1);
	ho.SetFillStyle((rt==0)?3354:3345);
	ho.SetFillColor((rt==0)?kRed:kBlue);
	ho.SetFillColorAlpha((rt==0)?kRed:kBlue, 0.35);
	tree->Draw("PositionZ");
	*/
	
	canvas->SaveAs("print.png");
	//file->Close();
}
