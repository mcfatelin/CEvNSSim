
{
	PmtPositionArray ppa;
    //ppa.Print();

	GeometryFactor gf;
	//printf("pick:%f\n", gf.Calculate());
	vector<TVector3> v;
	
	// LXESD h=1190.5mm, zshift=-694.85mm
	// GXESD h=45mm, zshift=-235.5mm
	// LXE h~1200mm
	// GXE h~50mm
	const Double_t zshift = (1200+50)/2; //mm
	ppa.GetTopPmtPos(zshift, v);
	ppa.GetBotPmtPos(zshift, v);
	
	const Double_t val = gf.Calculate(v, TVector3(0,0,0));
	
	printf("The geom factor at (0,0,0) is %f\n", val);
	
	printf("The solid angle at (0,0,0) is %f\n", val*4*M_PI);
}
