#include "phase3_info.h"

bool Phase3_info::solved(const Cube_bg_model& cube) const
{
    using ECOLOUR = Cube_bg_model::ECOLOUR;
    using EPIECE  = Cube_bg_model::EPIECE;
    using EEDGE   = Cube_bg_model::EEDGE;

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
    
    // checks whether the tetrads are formed
    for (int i = 0; i < 8; ++i) if (C_perm[i] % 2 != i % 2) return false;

    // a corner permutation is in G3 if all corners are solved after solving 5 corners

    // solves the even tetrad (ULB = 0, DLF = 2, DRB = 4, URF = 6)
    for (uint8_t i = 0; i < 6; i += 2)
    {
        if (C_perm[i] == i) continue;

        for (auto move : C_evenTetradSolvingMoves[i / 2])
        {
            imitate_move(move, C_perm);
            if (C_perm[i] == i) break;    
            imitate_move(move, C_perm);
        }
    }
    // solves one corner in the odd tetrad (ULF = 1)
    uint8_t move_sequence = 0;
    while (C_perm[1] != 1)
    {
        for (int j = 0; j < 4; ++j)
        {
            imitate_move(C_oddTetradSolvingMoves[move_sequence][j], C_perm);
        }
        if (C_perm[1] == 1) break;
        for (int j = 3; j >= 0; --j)
        {
            imitate_move(C_oddTetradSolvingMoves[move_sequence][j], C_perm);
        }
        move_sequence++;
    }

    // checks if the permutation is solved
    for (uint8_t i = 0; i < 8; ++i) if (C_perm[i] != i) return false;

    // checks if all the edges are in their home slice (M-slice edges are already solved)
    return
        (cube.colour(EEDGE::UR) == ECOLOUR::W || cube.colour(EEDGE::UR) == ECOLOUR::Y) &&
        (cube.colour(EEDGE::UL) == ECOLOUR::W || cube.colour(EEDGE::UL) == ECOLOUR::Y) &&
        (cube.colour(EEDGE::DR) == ECOLOUR::W || cube.colour(EEDGE::DR) == ECOLOUR::Y) &&
        (cube.colour(EEDGE::DL) == ECOLOUR::W || cube.colour(EEDGE::DL) == ECOLOUR::Y) &&
        (cube.colour(EEDGE::FR) == ECOLOUR::G || cube.colour(EEDGE::FR) == ECOLOUR::B) &&
        (cube.colour(EEDGE::FL) == ECOLOUR::G || cube.colour(EEDGE::FL) == ECOLOUR::B) &&
        (cube.colour(EEDGE::BR) == ECOLOUR::G || cube.colour(EEDGE::BR) == ECOLOUR::B) &&
        (cube.colour(EEDGE::BL) == ECOLOUR::G || cube.colour(EEDGE::BL) == ECOLOUR::B);
}

void Phase3_info::imitate_move(EMOVE move, std::array<uint8_t, 8>& tetradsPerm) const
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
        throw std::logic_error("G2_G3_Goal::imitate_move invalid enum value " + moveValue);
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