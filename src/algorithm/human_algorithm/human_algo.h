#pragma once

#include <vector>

#include "../solver.h"
#include "../cube_bg_model.h"

using color = Cube_bg_model::ecolor;

class Human_algo : Solver {
public:
    std::vector<std::pair<rotation_side, rotation_type>> solve(const Cube_bg_model &bg_cube) const override;

    std::vector<std::pair<rotation_side, rotation_type>> phase1(Cube_bg_model &bg_cube) const;
    std::vector<std::pair<rotation_side, rotation_type>> phase2(Cube_bg_model &bg_cube) const;
    std::vector<std::pair<rotation_side, rotation_type>> phase3(Cube_bg_model &bg_cube) const;
    std::vector<std::pair<rotation_side, rotation_type>> phase4(Cube_bg_model &bg_cube) const;
    std::vector<std::pair<rotation_side, rotation_type>> phase5(Cube_bg_model &bg_cube) const;
    std::vector<std::pair<rotation_side, rotation_type>> phase6(Cube_bg_model &bg_cube) const;
    std::vector<std::pair<rotation_side, rotation_type>> phase7(Cube_bg_model &bg_cube) const;

    std::vector<std::pair<rotation_side, rotation_type>> circle_move(std::vector<std::pair<rotation_side, rotation_type>> in_vec, int r) const;
};
