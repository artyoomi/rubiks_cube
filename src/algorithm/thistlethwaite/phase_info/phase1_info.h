#pragma once

#include "phase_info.h"

struct Phase1_info : public Phase_info {
    Phase1_info()
    {
        // all moves are allowed
        allowed_moves = {
            EMOVE::U, EMOVE::Up, EMOVE::U2,
            EMOVE::L, EMOVE::Lp, EMOVE::L2,
            EMOVE::F, EMOVE::Fp, EMOVE::F2,
            EMOVE::R, EMOVE::Rp, EMOVE::R2,
            EMOVE::B, EMOVE::Bp, EMOVE::B2,
            EMOVE::D, EMOVE::Dp, EMOVE::D2
        };
    }

	// G1 is contented when all the edges are oriented correctly
	bool solved(const Cube_bg_model& cube) const override;
};