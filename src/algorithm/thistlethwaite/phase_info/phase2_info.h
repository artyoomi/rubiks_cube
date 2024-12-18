#pragma once

#include "phase_info.h"

struct Phase2_info : public Phase_info
{
	Phase2_info()
    {
        // forbid U and D quarter turns
        allowed_moves = {
            EMOVE::U2,
            EMOVE::L, EMOVE::Lp, EMOVE::L2,
            EMOVE::F, EMOVE::Fp, EMOVE::F2,
            EMOVE::R, EMOVE::Rp, EMOVE::R2,
            EMOVE::B, EMOVE::Bp, EMOVE::B2,
            EMOVE::D2
        };
    }

	// G2 is contented when all the corners are oriented correctly and the M-slice
	// edges are brought back intro their slice
	bool solved(const Cube_bg_model& cube) const override;
};