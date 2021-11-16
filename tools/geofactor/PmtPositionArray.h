#ifndef PmtPositionArray_H
#define PmtPositionArray_H

class TVector3;

class PmtPositionArray
{
public:
    // unit = mm, pmt_position is on it own face which is the offset = 15. mm
	// pmt_top_pos_z = LXe_z + GXe_z - pmt_face_offset
	// pmt_bot_pos_z = - LXe_z + pmt_face_offset
	PmtPositionArray(const Double_t pmt_ida_=76., const Double_t pmt_gap_=1.5
 , const Double_t pmt_top_pos_z_=600.+100.-15., const Double_t pmt_bot_pos_z_=-600.+15.); 
	~PmtPositionArray();

	void Print();

	const std::vector<TVector3>& Get() { return pmt_opt_sd_pos_; }
private:
	std::vector<TVector3> pmt_opt_sd_pos_;

	static void GetPmtPos(const Double_t interval
		, const Double_t offset_x, const Double_t offset_y
		, const Double_t offset_z, std::vector<TVector3>& positions);
};

#endif //PmtPositionArray_H
