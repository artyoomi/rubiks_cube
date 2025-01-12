#pragma once

#include "phase_info.h"
#include "../utilities/rankers.h"

// G1 -> G2
struct Phase2_info : public Phase_info
{
	Phase2_info()
    {
        // G1: forbid U and D 90-degree turns
        allowed_moves = {
            emove::U2,
            emove::L, emove::Lr, emove::L2,
            emove::F, emove::Fr, emove::F2,
            emove::R, emove::Rr, emove::R2,
            emove::B, emove::Br, emove::B2,
            emove::D2
        };
    }

    uint32_t id(const Cube_bg_model& cube) const override;

    /* 
	 * G1 -> G2 is solved when all the corners are oriented correctly and the M-slice
	 * edges are brought back intro their slice
	 */
    bool solved(const Cube_bg_model& cube) const override;

private:
    CombRanker<4> _comb_ranker4;
};