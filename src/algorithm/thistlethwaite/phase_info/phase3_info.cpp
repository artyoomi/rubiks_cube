#include "phase3_info.h"

uint32_t Phase3_info::id(const Cube_bg_model& cube) const
{
    /* 
     * Stores the edges that are currently occupying each position on the UD-slice & FB-slice slice.
     * NOTE: Edges from LR-slice were placed in previous phase, so here we consider remaining 8 edges.
     */
    std::array<uint8_t, 8> edges_perm = {
        cube.piece_index(epiece::RF),
        cube.piece_index(epiece::RB),
        cube.piece_index(epiece::LF),
        cube.piece_index(epiece::LB),
        cube.piece_index(epiece::UL),
        cube.piece_index(epiece::UR),
        cube.piece_index(epiece::DL),
        cube.piece_index(epiece::DR),
    };

    // stores which corner is currently occupying which position
    std::array<uint8_t, 8> corners_perm = {
        cube.piece_index(epiece::ULB),
        cube.piece_index(epiece::ULF),
        cube.piece_index(epiece::DLF),
        cube.piece_index(epiece::DLB),
        cube.piece_index(epiece::DRB),
        cube.piece_index(epiece::DRF),
        cube.piece_index(epiece::URF),
        cube.piece_index(epiece::URB),
    };
    
    // stores the positions of the 4 edges that need to be brought back to the UD-slice
    std::array<uint8_t, 4> edges_position_comb;
    
    /*
     * Stores the positions of the 4 corners that need to be brought back to the even tetrad
     * NOTE: even tetrad consists of LUB, LDF, RDB, RUF, odd tetrad consists of remaining corners
     */
    std::array<uint8_t, 4> corners_even_tetrad_position_comb;
    
    // extracts the corners into their tetrads while keeping the same relative order from the initial perm
    std::array<uint8_t, 4> corner_even_tetrad, corner_odd_tetrad;
    std::array<uint8_t, 8> corners_tetrads_perm;

    // used to check the positions of the even tetrad first
    const std::array<uint8_t, 8> corners_map = {0, 2, 4, 6, 1, 3, 5, 7};

    for (uint8_t i = 0, e = 0, c = 0, c_even = 0, c_odd = 0; i < 8; ++i) {
        /*
         * Get positions of UD-slice edges
         * (indices of the UD-slice edges are 4, 5, 6, 7)
         */
        if (edges_perm[i] == 4 || edges_perm[i] == 5 || edges_perm[i] == 6 || edges_perm[i] == 7)
            edges_position_comb[e++] = i;

        /*
         * Get positions of even tetrad corners
         * (corners from even tetrad has even indices)
         */
        if (corners_perm[corners_map[i]] % 2 == 0)
            corners_even_tetrad_position_comb[c++] = i;

        // splits the corners while keeping the relative order
        if (corners_perm[i] % 2 == 0)
            corner_even_tetrad[c_even++] = corners_perm[i];
        else
            corner_odd_tetrad[c_odd++] = corners_perm[i];
    }

    // forms the new permutation with the corners in their tetrads in relative order
    for (std::size_t i = 0; i < 8; ++i)
        corners_tetrads_perm[i] = (i & 1) ? corner_odd_tetrad[i >> 1] : corner_even_tetrad[i >> 1];

    // solves the even tetrad (ULB = 0, DLF = 2, DRB = 4, URF = 6)
    for (uint8_t i = 0; i < 6; i += 2) {
        if (corners_tetrads_perm[i] == i)
            continue;

        for (auto move : _corners_even_tetrad_solving_moves[i / 2]) {
            _imitate_move(move, corners_tetrads_perm);
            if (corners_tetrads_perm[i] == i)
                break;
            _imitate_move(move, corners_tetrads_perm);
        }
    }

    // solves one corner in the odd tetrad (ULF = 1)
    uint8_t move_sequence = 0;
    while (corners_tetrads_perm[1] != 1) {
        for (int j = 0; j < 4; ++j)
            _imitate_move(_corners_odd_tetrad_solving_moves[move_sequence][j], corners_tetrads_perm);

        if (corners_tetrads_perm[1] == 1)
            break;

        for (int j = 3; j >= 0; --j)
            _imitate_move(_corners_odd_tetrad_solving_moves[move_sequence][j], corners_tetrads_perm);
        
        ++move_sequence;
    }

    // stores the permutation of the remaining 3 corners in the odd tetrad (3,5,7) as (0,1,2)
    std::array<uint8_t, 3> odd_tetrad_perm = {
        (uint8_t)((corners_tetrads_perm[3] >> 1) - 1),
        (uint8_t)((corners_tetrads_perm[5] >> 1) - 1),
        (uint8_t)((corners_tetrads_perm[7] >> 1) - 1),
    };

    // 0..8C4 - 1
    uint32_t edges_index = _comb_ranker4.rank(edges_position_comb);

    // 0..8C4 - 1
    uint32_t corners_index = _comb_ranker4.rank(corners_even_tetrad_position_comb);

    // 0...3! - 1
    uint32_t odd_tetrad_index = _perm_ranker3.rank(odd_tetrad_perm);

    // (0..8C4 - 1 * 8C4 + 0..8C4 - 1) * 6 + ..5 = 0..29399
    return (corners_index * 70 + edges_index) * 6 + odd_tetrad_index;
}

bool Phase3_info::solved(const Cube_bg_model& cube) const
{
    return this->id(cube) == 0;
}

void Phase3_info::_imitate_move(emove move, std::array<uint8_t, 8>& tetrads_perm) const
{
    std::array<uint8_t, 4> indices, positions;
    switch (move) {
    case emove::U2:
        indices = {0, 6, 1, 7};
        break;
    case emove::D2:
        indices = {2, 4, 3, 5};
        break;
    case emove::L2:
        indices = {0, 2, 1, 3};
        break;
    case emove::R2:
        indices = {4, 6, 5, 7};
        break;
    case emove::F2:
        indices = {2, 6, 1, 5};
        break;
    case emove::B2:
        indices = {0, 4, 3, 7};
        break;
    default:
        std::string move_value = std::to_string((int)move);
        throw std::logic_error("Phase3_info::imitate_move invalid enum value " + move_value);
    }

    for (uint8_t i = 0; i < 8; ++i) {
        if (tetrads_perm[i] == indices[0]) positions[0] = i;
        if (tetrads_perm[i] == indices[1]) positions[1] = i;
        if (tetrads_perm[i] == indices[2]) positions[2] = i;
        if (tetrads_perm[i] == indices[3]) positions[3] = i;
    }

    std::swap(tetrads_perm[positions[0]], tetrads_perm[positions[1]]);
    std::swap(tetrads_perm[positions[2]], tetrads_perm[positions[3]]);
}
