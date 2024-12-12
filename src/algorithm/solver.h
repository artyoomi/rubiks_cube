#pragma once
#include "cube_bg_model.h"
#include <utility>
#include <vector>

namespace solver
{
    std::vector<std::pair<rotation_side, rotation_type>> solve(const Cube_bg_model &bg_cube);
};
