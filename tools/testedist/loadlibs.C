
{
	//if (!gSystem->Load("libgsl"))
		//printf("loadlibs - libgsl\n");
	//else
		//printf("err: can't load LIBGSL\n");
	
	if (!gROOT->ProcessLine(".L QuantaNest.cxx+"))
		printf("loadlibs - QuantaNest.cxx+\n");
	else
		printf("err: can't process QuantaNest.cxx+\n");

	if (!gROOT->ProcessLine(".L QS1RawNest.cc+"))
		printf("loadlibs - QS1RawNest.cc+\n");
	else
		printf("err: can't process QS1RawNest.cc+\n");

	//if (!gROOT->ProcessLine(".L PmtPositionArray.cxx+"))
		//printf("loadlibs - PmtPositionArray.cxx+\n");
	//else
		//printf("err: can't process GeometrPmtPositionArray.cxx+\n");

}
