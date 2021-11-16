
//void run(void)
{
	gROOT->ProcessLine(".x loadlibs.C");

	//gROOT->ProcessLine(".x pmtarr.C");

	gROOT->ProcessLine(".x qnestgen.C");


	
	cout << "executed: run.C" << endl;
}
