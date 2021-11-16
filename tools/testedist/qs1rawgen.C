{
	{
    auto f = new TFile("qs1raw.root", "RECREATE");
	auto t = new TTree("mcTree", "Tree with QuantaNest info");

	QS1RawNest qNR;
	std::vector<Int_t> _energyNR;
	std::vector<Int_t> _photonNR;
    t->Branch("energyNR", &_energyNR);
    t->Branch("photonNR", &_photonNR);

	QS1RawNest qER;
	std::vector<Int_t> _energyER;
	std::vector<Int_t> _photonER;
    t->Branch("energyER", &_energyER);
    t->Branch("photonER", &_photonER);
	
	for (Int_t e=5; e<=30; e++)
	{
		for (Int_t i=0; i<100; i++)
		{
			_energyNR.push_back(e);
			_photonNR.push_back(qNR.GetQuanta(e, 400, PRecoilType::rtNR));
		}
	}

	for (Int_t e=1; e<=7; e++)
	{
		for (Int_t i=0; i<400; i++)
		{
			_energyER.push_back(e);
			_photonER.push_back(qER.GetQuanta(e, 400, PRecoilType::rtER));
		}
	}
	
	t->Fill();
	f->Write();
    f->Close();
	std::cout << "output: qs1raw.root" << std::endl;
	}
}
