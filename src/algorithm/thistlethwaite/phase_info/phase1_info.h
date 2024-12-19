#pragma once

#include "phase_info.h"

struct Phase1_info : public Phase_info {
    Phase1_info()
    {
        // all moves are allowed
        allowed_moves = {
            emove::U, emove::Up, emove::U2,
            emove::L, emove::Lp, emove::L2,
            emove::F, emove::Fp, emove::F2,
            emove::R, emove::Rp, emove::R2,
            emove::B, emove::Bp, emove::B2,
            emove::D, emove::Dp, emove::D2
        };
    }

	// G1 is contented when all the edges are oriented correctly
	bool solved(const Cube_bg_model& cube) const override;
};