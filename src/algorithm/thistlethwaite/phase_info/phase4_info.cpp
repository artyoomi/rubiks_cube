#include "phase4_info.h"

uint32_t Phase4_info::id(const Cube_bg_model& cube) const
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

    // stores which corner from even tetrad is currently occupying which position
    std::array<uint8_t, 4> corner_even_tetrad_position_perm = {
        cube.piece_index(epiece::ULB),
        cube.piece_index(epiece::DLF),
        cube.piece_index(epiece::DRB),
        cube.piece_index(epiece::URF),
    };

    // sets the indices of all edge and corner pieces to a value between 0 and 3

    /*
     * Here even tetrad corners can have only indexes 0, 2, 4, 6 and we need to 
     * interpret this numbers as 4 numbers. which we can permute in 4! ways to encode it. So
     * we transform this numbers in numbers 0, 1, 2, 3.
     */
    for (auto& c : corner_even_tetrad_position_perm) c >>= 1;
    
    /*
     * In next two permutations situation is same. We don't need global index of edge, we just need
     * number of edge in UD-slice edges, so we transform it to number [0; 3]
     */
    for (auto& e : edges_positions_perm_UDslice) e &= 3;
    for (auto& e : edges_positions_perm_LRslice) e &= 3;
    // indices of the FB-slice edges are 0..3 by default

    // same logic as earlier, we need index of corner only in it's tetrad
    uint8_t corners_odd_tetrad_rank = (cube.piece_index(epiece::ULF) >> 1);
    uint8_t edges_FBslice_rank = perm_indexer4p2.index(edges_positions_perm_FBslice);


    /*
     * index for edges in each slice
     * (0..4! - 1) * (4!^2 / 2) + (0..4! - 1) * (4! / 2) + (0..4! / 2) = 0..6911
     */
    uint32_t edges_index = perm_indexer4.index(edges_positions_perm_LRslice) * 288 + perm_indexer4.index(edges_positions_perm_UDslice) * 12 + edges_FBslice_rank;

    /*
     * index for corners in each tetrad
     * (0..4! - 1) * 4 + 0..3 = 0..95
     */
    uint32_t corners_index = perm_indexer4.index(corner_even_tetrad_position_perm) * 4 + corners_odd_tetrad_rank;

    // 0..9611 * 96 + 0..95 = 0..663551
    return edges_index * 96 + corners_index;
}

bool Phase4_info::solved(const Cube_bg_model& cube) const
{
    return cube.solved();
}
