#include "phase4_database.h"

uint32_t Phase4_database::id(const Cube_bg_model& cube) const
{
    // stores which edge is currently occupying each position in it's slice
    
    // UD-slice
    std::array<uint8_t, 4> edges_positions_perm_UDslice = {
        cube.piece_index(epiece::LF),
        cube.piece_index(epiece::LB),
        cube.piece_index(epiece::RF),
        cube.piece_index(epiece::RB),
    };

    // LR-slice
    std::array<uint8_t, 4> edges_positions_perm_LRslice = {
        cube.piece_index(epiece::UF),
        cube.piece_index(epiece::DF),
        cube.piece_index(epiece::DB),
        cube.piece_index(epiece::UB),
    };

    /*
     * FB-slice
     * only half the pieces in the FB-slice are stored, the positions of the first 10
     * edges dictate the positions of the last 2 (they have to have even parity)
     */
    std::array<uint8_t, 2> edges_positions_perm_FBslice = {
        cube.piece_index(epiece::UL),
        cube.piece_index(epiece::DL),
    };

    /* 
     * stores which corner from even tetrad is currently occupying which position
     */
    std::array<uint8_t, 4> corner_even_tetrad_position_perm = {
        cube.piece_index(epiece::ULB),
        cube.piece_index(epiece::DLF),
        cube.piece_index(epiece::DRB),
        cube.piece_index(epiece::URF),
    };

    // sets the indices of all edge and corner pieces to a value between 0 and 3
    for (auto& c : corner_even_tetrad_position_perm) c >>= 1;
    for (auto& e : edges_positions_perm_UDslice)     e &= 3;
    for (auto& e : edges_positions_perm_LRslice)     e &= 3;
    // indices of the FB-slice edges are 0..3 by default

    /*
     * for every permutation of the first tetrad the second tetrad will start 
     * with either 0/1/2/3 which dictates the "rank" of the permutation
     */
    uint8_t corners_odd_tetrad_rank = cube.piece_index(epiece::ULF);
    uint8_t edges_FBslice_rank = perm_indexer4p2.index(edges_positions_perm_FBslice);

    // (0..4! - 1) * 4 + 0..3 = 0..96
    uint32_t corners_index = perm_indexer4.index(corner_even_tetrad_position_perm) * 4 + (corners_odd_tetrad_rank >> 1);
    // (0..4! - 1) * (4!^2 / 2) + (0..4! - 1) * (4! / 2) + (0..4! / 2) = 0..6911
    uint32_t edges_index = perm_indexer4.index(edges_positions_perm_LRslice) * 288 + perm_indexer4.index(edges_positions_perm_UDslice) * 12 + edges_FBslice_rank;
    // 0..9611 * 96 + 0..95 = 0..663551
    return edges_index * 96 + corners_index;
}
