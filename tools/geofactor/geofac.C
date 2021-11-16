
{
	PmtPositionArray ppa;
    //ppa.Print();

	GeometryFactor gf;
	//printf("pick:%f\n", gf.Calculate());
	TVector3 src_pos(0,0,0);

	Double_t val = gf.Calculate(ppa.Get(), src_pos);
	

	printf("The solid angle at (%f, %f, %f) is %f\n"
		, src_pos.X(), src_pos.Y(), src_pos.Z(), val*4*M_PI);

	printf("The geom factor at (%f, %f, %f) is %f\n"
		, src_pos.X(), src_pos.Y(), src_pos.Z(),val);


}
