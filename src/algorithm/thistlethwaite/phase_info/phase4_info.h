#pragma once

#include "phase_info.h"

struct Phase4_info : public Phase_info
{
	Phase4_info()
    {
        // forbid all quarter turns
        allowed_moves = {
            EMOVE::U2,
            EMOVE::L2,
            EMOVE::F2,
            EMOVE::R2,
            EMOVE::B2,
            EMOVE::D2
        };
    }

	// G4 is contented when the cube is solved
	bool solved(const Cube_bg_model& cube) const override;
};