#include "phase1_database.h"

uint32_t Phase1_database::id(const Cube_bg_model& cube) const
{
    using EPIECE = Cube_bg_model::EPIECE;

    // stores the orientation of all edges (by position, regardless of which edge is where)
    // the orientation of 11 edges dictates the orientation of the 12th edge (even orientation values)
    std::array<uint8_t, 11> edge_orientation_perm = {
        cube.edge_orientation(cube.edge(EPIECE::RB)),
        cube.edge_orientation(cube.edge(EPIECE::RF)),
        cube.edge_orientation(cube.edge(EPIECE::UR)),
        cube.edge_orientation(cube.edge(EPIECE::DR)),
        cube.edge_orientation(cube.edge(EPIECE::LB)),
        cube.edge_orientation(cube.edge(EPIECE::LF)),
        cube.edge_orientation(cube.edge(EPIECE::UL)),
        cube.edge_orientation(cube.edge(EPIECE::DL)),
        cube.edge_orientation(cube.edge(EPIECE::UB)),
        cube.edge_orientation(cube.edge(EPIECE::UF)),
        cube.edge_orientation(cube.edge(EPIECE::DB)),
    };

    // convert to decimal [0; 2047]
    uint32_t id = 0;
    for (std::size_t i = 0; i < 11; ++i)
        id += (edge_orientation_perm[i] << i);
    return id;
}
