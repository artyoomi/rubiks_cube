#pragma once

#include "phase_info.h"

struct Phase3_info : public Phase_info
{
	Phase3_info()
    {
        // forbid U, F, B and D quarter turns
        allowed_moves = {
            emove::U2,
            emove::L, emove::Lp, emove::L2,
            emove::F2,
            emove::R, emove::Rp, emove::R2,
            emove::B2,
            emove::D2
        };
    }

    // G3 is contented when it's possible to solve the cube without 90 degree twists
    // to ensure that, all edges and corners are in their orbits and the parity is even

    // this implementation splits the corners into 4 pairs instead of forming 2 tetrads
	bool solved(const Cube_bg_model& cube) const override;
    
private:
    using emove = Cube_bg_model::emove;

    // moves to solve the even tetrad (ULB, DLF, DRB, URF)
    const std::array<std::vector<emove>, 3> C_evenTetradSolvingMoves = {{
        { emove::U2, emove::L2, emove::B2 },  // ULB
        { emove::D2, emove::F2 },             // DLF
        { emove::R2 },                        // DRB
    }};
    // moves to solve ULF (first corner of the odd tetrad)
    const std::array<std::array<emove, 4>, 3> C_oddTetradSolvingMoves = {{
        // these move sequences perform a double swap on the four pieces of  
        // the odd tetrad without affecting the corners in the even tetrad
        { emove::F2, emove::L2, emove::F2, emove::U2 },
        { emove::U2, emove::F2, emove::U2, emove::L2 },
        { emove::L2, emove::U2, emove::L2, emove::F2 },
    }};

    // imitates a move on an array
    void imitate_move(emove move, std::array<uint8_t, 8>& tetradsPerm) const;
};