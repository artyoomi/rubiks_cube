#include "phase1_info.h"

#include "../database/phase1_database.h"

bool Phase1_info::solved(const Cube_bg_model& cube) const
{
    return cube.edge_orientation(cube.edge(epiece::UL)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::DL)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::DR)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::UR)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::LF)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::LB)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::RF)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::RB)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::UF)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::DF)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::DB)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::UB)) == 0;
}
