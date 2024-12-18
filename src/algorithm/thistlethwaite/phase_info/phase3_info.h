#pragma once

#include "phase_info.h"

struct Phase3_info : public Phase_info
{
	Phase3_info()
    {
        // forbid U, F, B and D quarter turns
        allowed_moves = {
            EMOVE::U2,
            EMOVE::L, EMOVE::Lp, EMOVE::L2,
            EMOVE::F2,
            EMOVE::R, EMOVE::Rp, EMOVE::R2,
            EMOVE::B2,
            EMOVE::D2
        };
    }

    // G3 is contented when it's possible to solve the cube without 90 degree twists
    // to ensure that, all edges and corners are in their orbits and the parity is even

    // this implementation splits the corners into 4 pairs instead of forming 2 tetrads
	bool solved(const Cube_bg_model& cube) const override;
    
private:
    using EMOVE = Cube_bg_model::EMOVE;

    // moves to solve the even tetrad (ULB, DLF, DRB, URF)
    const std::array<std::vector<EMOVE>, 3> C_evenTetradSolvingMoves = {{
        { EMOVE::U2, EMOVE::L2, EMOVE::B2 },  // ULB
        { EMOVE::D2, EMOVE::F2 },             // DLF
        { EMOVE::R2 },                        // DRB
    }};
    // moves to solve ULF (first corner of the odd tetrad)
    const std::array<std::array<EMOVE, 4>, 3> C_oddTetradSolvingMoves = {{
        // these move sequences perform a double swap on the four pieces of  
        // the odd tetrad without affecting the corners in the even tetrad
        { EMOVE::F2, EMOVE::L2, EMOVE::F2, EMOVE::U2 },
        { EMOVE::U2, EMOVE::F2, EMOVE::U2, EMOVE::L2 },
        { EMOVE::L2, EMOVE::U2, EMOVE::L2, EMOVE::F2 },
    }};

    // imitates a move on an array
    void imitate_move(EMOVE move, std::array<uint8_t, 8>& tetradsPerm) const;
};