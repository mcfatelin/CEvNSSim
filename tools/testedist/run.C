
//void run(void)
{
	gROOT->ProcessLine(".x loadlibs.C");

	//gROOT->ProcessLine(".x pmtarr.C");

	gROOT->ProcessLine(".x qnestgen.C");
	gROOT->ProcessLine(".x qs1rawgen.C");
	
	cout << "executed: run.C" << endl;
}
