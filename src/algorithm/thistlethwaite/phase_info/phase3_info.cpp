#include "phase3_info.h"

bool Phase3_info::solved(const Cube_bg_model& cube) const
{
    // stores which corner is currently occupying which position
    std::array<uint8_t, 8> C_perm = {
        cube.piece_index(epiece::ULB),
        cube.piece_index(epiece::ULF),
        cube.piece_index(epiece::DLF),
        cube.piece_index(epiece::DLB),
        cube.piece_index(epiece::DRB),
        cube.piece_index(epiece::DRF),
        cube.piece_index(epiece::URF),
        cube.piece_index(epiece::URB),
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
        (cube.colour(eedge::UR) == ecolour::W || cube.colour(eedge::UR) == ecolour::Y) &&
        (cube.colour(eedge::UL) == ecolour::W || cube.colour(eedge::UL) == ecolour::Y) &&
        (cube.colour(eedge::DR) == ecolour::W || cube.colour(eedge::DR) == ecolour::Y) &&
        (cube.colour(eedge::DL) == ecolour::W || cube.colour(eedge::DL) == ecolour::Y) &&
        (cube.colour(eedge::FR) == ecolour::G || cube.colour(eedge::FR) == ecolour::B) &&
        (cube.colour(eedge::FL) == ecolour::G || cube.colour(eedge::FL) == ecolour::B) &&
        (cube.colour(eedge::BR) == ecolour::G || cube.colour(eedge::BR) == ecolour::B) &&
        (cube.colour(eedge::BL) == ecolour::G || cube.colour(eedge::BL) == ecolour::B);
}

void Phase3_info::imitate_move(emove move, std::array<uint8_t, 8>& tetradsPerm) const
{
    std::array<uint8_t, 4> indices, positions;
    switch (move)
    {
    case emove::U2:
        indices = { 0,6,1,7 };
        break;
    case emove::D2:
        indices = { 2,4,3,5 };
        break;
    case emove::L2:
        indices = { 0,2,1,3 };
        break;
    case emove::R2:
        indices = { 4,6,5,7 };
        break;
    case emove::F2:
        indices = { 2,6,1,5 };
        break;
    case emove::B2:
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