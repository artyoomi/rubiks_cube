#include "solver.h"

std::vector<std::pair<rotation_side, rotation_type>> solver::solve(const Cube_bg_model &const_bg_cube)
{
    // create a copy of cube memory model to operate with
    Cube_bg_model bg_cube = const_bg_cube;

    // vector of the moves
    std::vector<std::pair<rotation_side, rotation_type>> result;

    // <TODO> the algorithm

    // just a filler for testing purposes
    result.emplace_back(rotation_side::SIDE_F, rotation_type::ROTATION_R);
    result.emplace_back(rotation_side::SIDE_R, rotation_type::ROTATION_R);
    result.emplace_back(rotation_side::SIDE_U, rotation_type::ROTATION_R);
    result.emplace_back(rotation_side::SIDE_F, rotation_type::ROTATION_L);
    result.emplace_back(rotation_side::SIDE_R, rotation_type::ROTATION_L);

    return result;
}
