#pragma once

#include "phase_info.h"
#include "../utilities/rankers.h"

struct Phase3_info : public Phase_info
{
	Phase3_info()
    {
        // forbid U, F, B and D quarter turns
        allowed_moves = {
            emove::U2,
            emove::L, emove::Lr, emove::L2,
            emove::F2,
            emove::R, emove::Rr, emove::R2,
            emove::B2,
            emove::D2
        };
    }

    uint32_t id(const Cube_bg_model& cube) const override;

    /*
     * G3 is solved when it's possible to solve the cube without 90 degree twists
     * to ensure that, all edges and corners are in their orbits and the parity is even
     */
	bool solved(const Cube_bg_model& cube) const override;

private:
    // moves to solve the even tetrad (ULB, DLF, DRB, URF)
    const std::array<std::vector<emove>, 3> _corners_even_tetrad_solving_moves = {{
        {emove::U2, emove::L2, emove::B2},  // ULB
        {emove::D2, emove::F2},             // DLF
        {emove::R2},                        // DRB
    }};

    // moves to solve ULF (first corner of the odd tetrad)
    const std::array<std::array<emove, 4>, 3> _corners_odd_tetrad_solving_moves = {{
        /* 
         * these move sequences perform a double swap on the four pieces of  
         * the odd tetrad without affecting the corners in the even tetrad
         */
        {emove::F2, emove::L2, emove::F2, emove::U2},
        {emove::U2, emove::F2, emove::U2, emove::L2},
        {emove::L2, emove::U2, emove::L2, emove::F2},
    }};

    // imitates a move on an array
    void _imitate_move(emove move, std::array<uint8_t, 8>& tetrads_perm) const;

    CombRanker<4> _comb_ranker4;
    PermRanker<3> _perm_ranker3;
};