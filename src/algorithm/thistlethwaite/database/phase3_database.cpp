#include "phase3_database.h"

uint32_t Phase3_database::id(const Cube_bg_model& cube) const
{
    using EPIECE = Cube_bg_model::EPIECE;

    // stores the edges that are currently occupying each position on the E & S slice
    std::array<uint8_t, 8> E_perm = {
        cube.piece_index(EPIECE::RF),
        cube.piece_index(EPIECE::RB),
        cube.piece_index(EPIECE::LF),
        cube.piece_index(EPIECE::LB),
        cube.piece_index(EPIECE::UL),
        cube.piece_index(EPIECE::UR),
        cube.piece_index(EPIECE::DL),
        cube.piece_index(EPIECE::DR),
    };
    // stores which corner is currently occupying which position
    std::array<uint8_t, 8> C_perm = {
        cube.piece_index(EPIECE::ULB),
        cube.piece_index(EPIECE::ULF),
        cube.piece_index(EPIECE::DLF),
        cube.piece_index(EPIECE::DLB),
        cube.piece_index(EPIECE::DRB),
        cube.piece_index(EPIECE::DRF),
        cube.piece_index(EPIECE::URF),
        cube.piece_index(EPIECE::URB),
    };
    
    // stores the positions of the 4 edges that need to be brought back to the E-slice
    std::array<uint8_t, 4> E_posComb;
    // stores the positions of the 4 corners that need to be brought back to the even tetrad
    std::array<uint8_t, 4> C_posComb;
    // extracts the corners into their tetrads while keeping the same relative order from the initial perm
    std::array<uint8_t, 4> C_eTetrad, C_oTetrad;
    std::array<uint8_t, 8> C_tetradsPerm;
    // used to check the positions of the even tetrad first
    const std::array<uint8_t, 8> C_map = { 0,2,4,6,1,3,5,7 };

    for (uint8_t i = 0, e = 0, c = 0, ce = 0, co = 0; i < 8; ++i)
    {
        // indices of the E-slice edges are 4, 5, 6, 7
        if (E_perm[i] == 4 || E_perm[i] == 5 ||
            E_perm[i] == 6 || E_perm[i] == 7)
        {
            E_posComb[e++] = i + 1;
        }
        // even tetrad (even indices)
        if (C_perm[C_map[i]] % 2 == 0)
        {
            C_posComb[c++] = i + 1;
        }
        // splits the corners while keeping the relative order
        if (C_perm[i] % 2 == 0) C_eTetrad[ce++] = C_perm[i];
        else                    C_oTetrad[co++] = C_perm[i];
    }

    // forms the new permutation with the corners in their tetrads in relative order
    for (unsigned i = 0; i < 8; ++i)
    {
        C_tetradsPerm[i] = (i & 1) ? C_oTetrad[i >> 1] : C_eTetrad[i >> 1];
    }

    // solves the even tetrad (ULB = 0, DLF = 2, DRB = 4, URF = 6)
    for (uint8_t i = 0; i < 6; i += 2)
    {
        if (C_tetradsPerm[i] == i) continue;

        for (auto move : C_evenTetradSolvingMoves[i / 2])
        {
            imitate_move(move, C_tetradsPerm);
            if (C_tetradsPerm[i] == i) break;    
            imitate_move(move, C_tetradsPerm);
        }
    }
    // solves one corner in the odd tetrad (ULF = 1)
    uint8_t move_sequence = 0;
    while (C_tetradsPerm[1] != 1)
    {
        for (int j = 0; j < 4; ++j)
        {
            imitate_move(C_oddTetradSolvingMoves[move_sequence][j], C_tetradsPerm);
        }
        if (C_tetradsPerm[1] == 1) break;
        for (int j = 3; j >= 0; --j)
        {
            imitate_move(C_oddTetradSolvingMoves[move_sequence][j], C_tetradsPerm);
        }
        move_sequence++;
    }

    // stores the permutation of the remaining 3 corners in the odd tetrad (3,5,7) as (0,1,2)
    std::array<uint8_t, 3> C_tetradTwist = {
        (uint8_t)((C_tetradsPerm[3] >> 1) - 1),
        (uint8_t)((C_tetradsPerm[5] >> 1) - 1),
        (uint8_t)((C_tetradsPerm[7] >> 1) - 1),
    };

    // 0..8C4 - 1
    uint32_t E_ind = combIndexer4.id(E_posComb);
    // 0..8C4 - 1
    uint32_t C_ind = combIndexer4.id(C_posComb);
    // 0...3! - 1
    uint32_t F_ind = permIndexer3.id(C_tetradTwist);

    // (0..8C4 - 1 * 8C4 + 0..8C4 - 1) * 6 + ..5 = 0..29399
    return (C_ind * 70 + E_ind) * 6 + F_ind;
}

void Phase3_database::imitate_move(EMOVE move, std::array<uint8_t, 8>& tetradsPerm) const
{
    std::array<uint8_t, 4> indices, positions;
    switch (move)
    {
    case EMOVE::U2:
        indices = { 0,6,1,7 };
        break;
    case EMOVE::D2:
        indices = { 2,4,3,5 };
        break;
    case EMOVE::L2:
        indices = { 0,2,1,3 };
        break;
    case EMOVE::R2:
        indices = { 4,6,5,7 };
        break;
    case EMOVE::F2:
        indices = { 2,6,1,5 };
        break;
    case EMOVE::B2:
        indices = { 0,4,3,7 };
        break;
    default:
        std::string moveValue = std::to_string((int)move);
        throw std::logic_error("G2_G3_database::imitate_move invalid enum value " + moveValue);
    }

    for (uint8_t i = 0; i < 8; ++i)
    {
        if (tetradsPerm[i] == indices[0]) positions[0] = i;
        if (tetradsPerm[i] == indices[1]) positions[1] = i;
        if (tetradsPerm[i] == indices[2]) positions[2] = i;
        if (tetradsPerm[i] == indices[3]) positions[3] = i;
    }

    std::swap(tetradsPerm[positions[0]], tetradsPerm[positions[1]]);
    std::swap(tetradsPerm[positions[2]], tetradsPerm[positions[3]]);
}
