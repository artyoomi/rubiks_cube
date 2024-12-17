#pragma once

#include <utility>
#include <vector>

#include "cube_bg_model.h"

/*
 * Base class for all solving algorithms
 */
class Solver {
public:
    virtual std::vector<std::pair<rotation_side, rotation_type>> solve(const Cube_bg_model& cube) const = 0;
};