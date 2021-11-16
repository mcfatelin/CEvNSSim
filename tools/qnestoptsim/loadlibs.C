
{
	//if (!gSystem->Load("libgsl"))
		//printf("loadlibs - libgsl\n");
	//else
		//printf("err: can't load LIBGSL\n");
	
	if (!gROOT->ProcessLine(".L QuantaNest.cxx+"))
		printf("loadlibs - QuantaNest.cxx+\n");
	else
		printf("err: can't process GeometryFactorcxx+\n");

	//if (!gROOT->ProcessLine(".L PmtPositionArray.cxx+"))
		//printf("loadlibs - PmtPositionArray.cxx+\n");
	//else
		//printf("err: can't process GeometrPmtPositionArray.cxx+\n");

}
