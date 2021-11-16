#ifndef PmtPositionArray_H
#define PmtPositionArray_H

class TVector3;

class PmtPositionArray
{
public:
	static void GetTopPmtPos(const Double_t offset_z, std::vector<TVector3>& positions);
	static void GetBotPmtPos(const Double_t offset_z, std::vector<TVector3>& positions);	
	static TVector3 GetTopPMTXYPositionIIII(Int_t iPmtNb);
	static TVector3 GetBotPMTXYPositionIIII(Int_t iPmtNb);

	PmtPositionArray() {} 
	~PmtPositionArray() {}
};

#endif //PmtPositionArray_H
