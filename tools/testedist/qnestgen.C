
{
	{
    auto f = new TFile("qnest.root", "RECREATE");
	auto t = new TTree("mcTree", "Tree with QuantaNest info");

	QuantaNest qNR;
	qNR.setType(0); // 0:NR; 1:ER
	qNR.setField(400); // V/cm
	std::vector<Int_t> _energyNR;
	std::vector<Int_t> _photonNR;
    t->Branch("energyNR", &_energyNR);
    t->Branch("photonNR", &_photonNR);

	QuantaNest qER;
	qER.setType(1); // 0:NR; 1:ER
	qER.setField(400); // V/cm
	std::vector<Int_t> _energyER;
	std::vector<Int_t> _photonER;
    t->Branch("energyER", &_energyER);
    t->Branch("photonER", &_photonER);
	
	for (Int_t e=5; e<=30; e++)
	{
		for (Int_t i=0; i<100; i++)
		{
			qNR.setEnergy(e);
			qNR.calculate();
			_energyNR.push_back(e);
			_photonNR.push_back(qNR.getNPhoton());
		}
	}

	for (Int_t e=1; e<=7; e++)
	{
		for (Int_t i=0; i<400; i++)
		{
			qER.setEnergy(e);
			qER.calculate();
			_energyER.push_back(e);
			_photonER.push_back(qER.getNPhoton());
		}
	}
	
	t->Fill();
	f->Write();
    f->Close();
	std::cout << "output: qnest.root" << std::endl;
	}
}
