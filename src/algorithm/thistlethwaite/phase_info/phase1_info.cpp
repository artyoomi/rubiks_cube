#include "phase1_info.h"

#include "../database/phase1_database.h"

uint32_t Phase1_info::id(const Cube_bg_model& cube) const
{
    /*
     * Stores the orientation of all edges (by position, regardless of which edge is where)
     * the orientation of 11 edges dictates the orientation of the 12th edge (even orientation values)
     */
    std::array<uint8_t, 11> edge_orientation_perm = {
        cube.edge_orientation(cube.edge(epiece::RB)),
        cube.edge_orientation(cube.edge(epiece::RF)),
        cube.edge_orientation(cube.edge(epiece::UR)),
        cube.edge_orientation(cube.edge(epiece::DR)),
        cube.edge_orientation(cube.edge(epiece::LB)),
        cube.edge_orientation(cube.edge(epiece::LF)),
        cube.edge_orientation(cube.edge(epiece::UL)),
        cube.edge_orientation(cube.edge(epiece::DL)),
        cube.edge_orientation(cube.edge(epiece::UB)),
        cube.edge_orientation(cube.edge(epiece::UF)),
        cube.edge_orientation(cube.edge(epiece::DB)),
    };

    // convert to decimal [0; 2047]
    uint32_t id = 0;
    for (std::size_t i = 0; i < 11; ++i)
        id += (edge_orientation_perm[i] << i);
    return id;
}

bool Phase1_info::solved(const Cube_bg_model& cube) const
{
    return this->id(cube) == 0;
}
