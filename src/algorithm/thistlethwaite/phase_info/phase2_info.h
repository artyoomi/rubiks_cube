#pragma once

#include "phase_info.h"

struct Phase2_info : public Phase_info
{
	Phase2_info()
    {
        // forbid U and D quarter turns
        allowed_moves = {
            emove::U2,
            emove::L, emove::Lp, emove::L2,
            emove::F, emove::Fp, emove::F2,
            emove::R, emove::Rp, emove::R2,
            emove::B, emove::Bp, emove::B2,
            emove::D2
        };
    }

	// G2 is contented when all the corners are oriented correctly and the M-slice
	// edges are brought back intro their slice
	bool solved(const Cube_bg_model& cube) const override;
};