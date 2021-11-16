#include "PmtPositionArray.h"
#include <TVector3.h>
#include <iostream>

// Get the hexagonal-patterned PMT vertex by x-y plane inteval offset for PX-xT.
// 
// Created by: Parinya Namwongsa (Pick)
// Created: ~2018/01
// Email: pickitsimple@gmail.com, pickitsimple@hotmail.com

PmtPositionArray::PmtPositionArray(const Double_t pmt_dia_, const Double_t pmt_gap_
 , const Double_t pmt_top_pos_z_, const Double_t pmt_bot_pos_z_)
 //: pmt_opt_sd_pos_(new std::vector<TVector3>)
{
	const Double_t interval = pmt_dia_ + pmt_gap_;
    const Double_t offset_x = interval / 2;
    const Double_t offset_y =
        sqrt((interval * interval) - (offset_x * offset_x));

    PmtPositionArray::GetPmtPos(interval, offset_x, offset_y, 
		pmt_top_pos_z_, pmt_opt_sd_pos_);


    PmtPositionArray::GetPmtPos(interval, offset_x, offset_y, 
		pmt_bot_pos_z_, pmt_opt_sd_pos_);

}

PmtPositionArray::~PmtPositionArray()
{
	//delete pmt_opt_sd_pos_;
}

void PmtPositionArray::Print()
{
	for (auto i : pmt_opt_sd_pos_)
		printf("PMT: x=%f, y=%f, z=%f\n", i.X(), i.Y(), i.Z());
}

void PmtPositionArray::GetPmtPos(const Double_t interval
		, const Double_t offset_x, const Double_t offset_y
		, const Double_t offset_z, std::vector<TVector3>& positions)
{
	// Create the 199-PMT positions belong to offset_z

    const Int_t iter_y = 9;
    const Int_t iter_hset[iter_y] = {7, 7, 7, 7, 6, 6, 5, 4, 2};
	
	for (Int_t y = 0; y < iter_y; y++) {
        for (Int_t x = 0; x < iter_hset[y]; x++) {
            if (y % 2 == 0) {
                if (x == 0) {
		    positions.push_back(TVector3(0, +y * offset_y, offset_z));
                    if (y != 0)positions.push_back(TVector3(0, -y * offset_y, offset_z));
                }

                positions.push_back(TVector3(+(x + 1) * interval, +y * offset_y, offset_z));
                positions.push_back(TVector3(-(x + 1) * interval, +y * offset_y, offset_z));

                if (y != 0) {
                    positions.push_back(TVector3(+(x + 1) * interval, -y * offset_y, offset_z));
                    positions.push_back(TVector3(-(x + 1) * interval, -y * offset_y, offset_z));
                }
            } else {
                positions.push_back(TVector3(+offset_x + x * interval, +y * offset_y, offset_z));
                positions.push_back(TVector3(-offset_x - x * interval, +y * offset_y, offset_z));
                positions.push_back(TVector3(+offset_x + x * interval, -y * offset_y, offset_z));
                positions.push_back(TVector3(-offset_x - x * interval, -y * offset_y, offset_z));
            }
        }
    }

}
