#include "PmtPositionArray.h"
#include <TVector3.h>
#include <cmath>
#include <cstdio>

// Get the hexagonal-patterned PMT vertex by x-y plane inteval offset for PX-xT.
// 
// Created by: Parinya Namwongsa (Pick)
// Created: 2018-03-02
// Email: pickitsimple@gmail.com, pickitsimple@hotmail.com, pickitsimple@yahoo.co.th

void PmtPositionArray::GetTopPmtPos(const Double_t offset_z, std::vector<TVector3>& positions)
{
	for (Int_t i=0; i<169; i++)
	{
		TVector3 vv = PmtPositionArray::GetTopPMTXYPositionIIII(i);
		vv.SetZ(offset_z);
		positions.push_back(vv);
	}	
}

void PmtPositionArray::GetBotPmtPos(const Double_t offset_z, std::vector<TVector3>& positions)
{
	for (Int_t i=0; i<199; i++)
	{
		TVector3 vv = PmtPositionArray::GetBotPMTXYPositionIIII(i);
		vv.SetZ(offset_z);
		positions.push_back(vv);
	}	
}

TVector3 PmtPositionArray::GetTopPMTXYPositionIIII(Int_t iPmtNb)
{
    TVector3 hPos;
    
    const Int_t iNbTopPMTs = 169;
    
    const Int_t iNbRows = 8;
    const Int_t hNbPerRow[iNbRows] = {42,36,30,24,18,12,6,1};
    
    //const Double_t dDistance[iNbRows]={27*mm, 27*mm,27*mm,27*mm,27*mm,27*mm,27*mm,0};
    const Double_t dDistance = 81.5;	// mm
    
    vector<Double_t> hRowOffset;
    for(Int_t i=0; i<iNbRows; i++)
		hRowOffset.push_back((Double_t)(-1*(iNbRows-i-1)*dDistance));
    
    if (iPmtNb>=iNbTopPMTs)
		iPmtNb = iPmtNb-iNbTopPMTs;

    Int_t iPMTNb1 = 0;
    
    Int_t iTotal = hNbPerRow[0];
    while(iPmtNb+1>iTotal)
		iTotal += hNbPerRow[++iPMTNb1];
    
    Int_t iPMTNb2 = iPmtNb + hNbPerRow[iPMTNb1] - iTotal;
    
    hPos.SetX(hRowOffset[iPMTNb1]*std::cos(iPMTNb2*2*M_PI/hNbPerRow[iPMTNb1]));
    hPos.SetY(hRowOffset[iPMTNb1]*std::sin(iPMTNb2*2*M_PI/hNbPerRow[iPMTNb1]));
    hPos.SetZ(0.0);
    
    return hPos;
}

TVector3 PmtPositionArray::GetBotPMTXYPositionIIII(Int_t iPmtNb)
{
    TVector3 hPos;
    
    const Int_t iNbBottomPMTs = 199;
    
    const Double_t dDistance = 81.5; //79.5*mm;
    const Double_t dRowDistance = sqrt(3.)/2.*dDistance;
    
    const Int_t iNbRows = 17;
    const Int_t hNbPerRow[iNbRows] = {5,8,11,12,13,14,15,14,15,14,15,14,13,12,11,8,5};
    
    vector<Double_t> hRowOffset;
    for(Int_t i=0; i<iNbRows; i++)
		hRowOffset.push_back((Double_t)(-0.5*hNbPerRow[i]*dDistance));
    
    if (iPmtNb>=iNbBottomPMTs)
		iPmtNb = iPmtNb-iNbBottomPMTs;
    
    Int_t iPMTNb1 = 0;
    Int_t iTotal = hNbPerRow[0];
    while(iPmtNb+1>iTotal)
		iTotal += hNbPerRow[++iPMTNb1];
    
    const Int_t iPMTNb2 = iPmtNb + hNbPerRow[iPMTNb1] - iTotal;
    
    hPos.SetX((hRowOffset[iPMTNb1] + iPMTNb2*dDistance + dDistance/2));
    hPos.SetY(((0.5*(iNbRows)-iPMTNb1)*dRowDistance - dRowDistance/2));
    
    hPos.SetZ(0.0);
    
    return hPos;
}

