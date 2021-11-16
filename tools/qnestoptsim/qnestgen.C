
{
	const Int_t nEvent = 100;
	const Double_t Edep = 10.0; //keVee

    auto f = new TFile("qnest.root", "RECREATE");

	Int_t _runId = 9001;
	Int_t _eventId = 0;
	std::vector<Int_t> _nPhotons;


	auto t = new TTree("qnTree", "Tree with QuantaNest info");
    t->Branch("runId", &_runId, "runId/I");
    t->Branch("eventId", &_eventId, "eventId/I");
    t->Branch("nPhotons", &_nPhotons);

	
	for (_eventId=0; _eventId<nEvent; _eventId++)
	{
		QuantaNest q;
		q.setType(1); // 0:NR; 1:ER
		q.setEnergy(Edep);
		_nPhotons.push_back(q.getNPhoton());
	}

	t->Fill();
	f->Write();
    f->Close();
	std::cout << "output: qnest.root" << std::endl;

}
