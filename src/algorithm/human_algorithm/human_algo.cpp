#include "human_algo.h"

std::vector<std::pair<rotation_side, rotation_type>> Human_algo::solve(const Cube_bg_model &const_bg_cube) const
{
    // create a copy of cube memory model to operate with
    Cube_bg_model bg_cube = const_bg_cube;

    // vector of the moves
    std::vector<std::pair<rotation_side, rotation_type>> result;


    // this stages may need to be run multiple times
    while(1) {
        auto phase1 = this->phase1(bg_cube);
        if(phase1.empty())
            break;

        for(const auto &i : phase1) {
            result.push_back(i);
        }
    }

    while(1) {
        auto phase2 = this->phase2(bg_cube);
        if(phase2.empty())
            break;

        for(const auto &i : phase2) {
            result.push_back(i);
        }
    }

    while(1) {
        auto phase3 = this->phase3(bg_cube);
        if(phase3.empty())
            break;

        for(const auto &i : phase3) {
            result.push_back(i);
        }
    }

    while(1) {
        auto phase4 = this->phase4(bg_cube);
        if(phase4.empty())
            break;

        for(const auto &i : phase4) {
            result.push_back(i);
        }
    }
    
    while(1) {
        auto phase5 = this->phase5(bg_cube);
        if(phase5.empty())
            break;

        for(const auto &i : phase5) {
            result.push_back(i);
        }
    }
    
    while(1) {
        auto phase6 = this->phase6(bg_cube);
        if(phase6.empty())
            break;

        for(const auto &i : phase6) {
            result.push_back(i);
        }
    }
    
    while(1) {
        auto phase7 = this->phase7(bg_cube);
        if(phase7.empty())
            break;

        for(const auto &i : phase7) {
            result.push_back(i);
        }
    }

    return result;
}

// Phase 7 - orientation of the D edges
std::vector<std::pair<rotation_side, rotation_type>> Human_algo::phase7(Cube_bg_model &bg_cube) const
{
    // lambda for applying the rotation
    auto apply_rot = [&bg_cube](auto &res_vec, std::vector<std::pair<rotation_side, rotation_type>> rts){
        for(const auto &i : rts) {
            res_vec.emplace_back(i.first, i.second);
            bg_cube.rotate(i.first, i.second);
        }
    };

    auto is_edge_correct = [](color a1, color a2, color b1, color b2) {
        return (a1 == b1) && (a2 == b2);
    };

    std::vector<std::pair<rotation_side, rotation_type>> result;

    while(true) {
        // 1. Count wrongly positioned edges
        std::vector<std::vector<color>> corners = {
            {bg_cube[48], bg_cube[16]},
            {bg_cube[46], bg_cube[25]},
            {bg_cube[50], bg_cube[34]},
            {bg_cube[52], bg_cube[43]},
        };

        std::vector<std::vector<color>> colors = {
            {color::D, color::L}, // DL
            {color::D, color::F}, // DF
            {color::D, color::R}, // DR
            {color::D, color::B}  // DB
        };

        std::vector<int> wrong_edges;
        for(int i = 0; i < 4; i++) {
            if(!is_edge_correct(corners[i][0], corners[i][1], colors[i][0], colors[i][1]))
                wrong_edges.push_back(i);
        }


        // 2. Select move type
        std::vector<std::pair<rotation_side, rotation_type>> flip_DF_DR_move = {
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_L, rotation_type::ROTATION_R),

            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L),

            std::make_pair(rotation_side::SIDE_L, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L),

            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)
        };
        std::vector<std::pair<rotation_side, rotation_type>> flip_DF_DB_move = {
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_L, rotation_type::ROTATION_R),

            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),

            std::make_pair(rotation_side::SIDE_L, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L),

            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)
        };
        
        if(wrong_edges.size() == 4) {
            apply_rot(result, flip_DF_DB_move);
            apply_rot(result, circle_move(flip_DF_DB_move, 1));
        }
        else if(wrong_edges.size() == 2) {
            // DL, DR
            if(wrong_edges[0] == 0 && wrong_edges[1] == 2)
                apply_rot(result, circle_move(flip_DF_DB_move, 1));
            // DF, DB
            else if(wrong_edges[0] == 1 && wrong_edges[1] == 3)
                apply_rot(result, flip_DF_DB_move);

            // DF, DR
            else if(wrong_edges[0] == 1 && wrong_edges[1] == 2)
                apply_rot(result, flip_DF_DR_move);
            // DR, DB
            else if(wrong_edges[0] == 2 && wrong_edges[1] == 3)
                apply_rot(result, circle_move(flip_DF_DR_move, -1));
            // DB, DL
            else if(wrong_edges[0] == 0 && wrong_edges[1] == 3)
                apply_rot(result, circle_move(flip_DF_DR_move, 2));
            // DL, DF
            else if(wrong_edges[0] == 0 && wrong_edges[1] == 1)
                apply_rot(result, circle_move(flip_DF_DR_move, 1));
        }
        else
            break;
    }
    
    return result;
}

// Phase 6 - position of the D edges
std::vector<std::pair<rotation_side, rotation_type>> Human_algo::phase6(Cube_bg_model &bg_cube) const
{
    // lambda for applying the rotation
    auto apply_rot = [&bg_cube](auto &res_vec, std::vector<std::pair<rotation_side, rotation_type>> rts){
        for(const auto &i : rts) {
            res_vec.emplace_back(i.first, i.second);
            bg_cube.rotate(i.first, i.second);
        }
    };

    auto is_edge_correct = [](color a1, color a2, color b1, color b2) {
        return (std::min(a1, a2) == std::min(b1, b2)) &&
               (std::max(a1, a2) == std::max(b1, b2));
    };

    std::vector<std::pair<rotation_side, rotation_type>> result;

    while(true) {
        // 1. Count correctly placed D egdes (ignoring their orientation)
        std::vector<std::vector<color>> corners = {
            {bg_cube[48], bg_cube[16]},
            {bg_cube[46], bg_cube[25]},
            {bg_cube[50], bg_cube[34]},
            {bg_cube[52], bg_cube[43]},
        };

        std::vector<std::vector<color>> colors = {
            {color::D, color::L}, // DL
            {color::D, color::F}, // DF
            {color::D, color::R}, // DR
            {color::D, color::B}  // DB
        };

        std::vector<int> correct_edges;
        for(int i = 0; i < 4; i++) {
            if(is_edge_correct(corners[i][0], corners[i][1], colors[i][0], colors[i][1]))
                correct_edges.push_back(i);
        }

        // 2. Select non-movable edge and circle the other ones
        int rotation = 0;
        if(correct_edges.size() == 4)
            break;
        else if(correct_edges.size() != 0) {
            if(correct_edges[0] == 0)
                rotation = 1;
            else if(correct_edges[0] == 1)
                rotation = 0;
            else if(correct_edges[0] == 2)
                rotation = -1;
            else if(correct_edges[0] == 3)
                rotation = 2;
        }

        // 3. Apply the rotation
        std::vector<std::pair<rotation_side, rotation_type>> basic_move = {
            std::make_pair(rotation_side::SIDE_L, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_L, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_L, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_L, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L)
        };
        
        if(rotation != 0)
            basic_move = circle_move(basic_move, rotation);
        
        apply_rot(result, basic_move);
    }

    return result;
}

// Phase 5 - orientation of the bottom corners
std::vector<std::pair<rotation_side, rotation_type>> Human_algo::phase5(Cube_bg_model &bg_cube) const
{
    // lambda for applying the rotation
    auto apply_rot = [&bg_cube](auto &res_vec, std::vector<std::pair<rotation_side, rotation_type>> rts){
        for(const auto &i : rts) {
            res_vec.emplace_back(i.first, i.second);
            bg_cube.rotate(i.first, i.second);
        }
    };

    auto is_corner_correct = [](color a1, color a2, color a3, color b1, color b2, color b3) {
        return (a1 == b1) && (a2 == b2) && (a3 == b3);
    };

    std::vector<std::pair<rotation_side, rotation_type>> result;

    while(true) {
        std::vector<std::vector<color>> corners = {
            {bg_cube[51], bg_cube[44], bg_cube[15]},
            {bg_cube[45], bg_cube[17], bg_cube[24]},
            {bg_cube[47], bg_cube[26], bg_cube[33]},
            {bg_cube[53], bg_cube[35], bg_cube[42]}
        };

        std::vector<std::vector<color>> colors = {
            {color::D, color::B, color::L}, // DBL
            {color::D, color::L, color::F}, // DLF
            {color::D, color::F, color::R}, // DFR
            {color::D, color::R, color::B}  // DRB
        };

        // 1. Count twisted corners
        std::vector<int> twisted_corners;
        for(int i = 0; i < 4; i++) {
            if(!is_corner_correct(corners[i][0], corners[i][1], corners[i][2],
                                  colors[i][0], colors[i][1], colors[i][2]))
                twisted_corners.push_back(i);
        }

        // 2. Choose rotation
        int rotation = 0;
        if(twisted_corners.size() == 4) {
            if(bg_cube[17] == color::D)
                rotation = 0;
            else if(bg_cube[44] == color::D)
                rotation = 1;
            else if(bg_cube[26] == color::D)
                rotation = -1;
            else if(bg_cube[35] == color::D)
                rotation = 2;
        }
        else if(twisted_corners.size() == 3) {
            if(bg_cube[45] == color::D)
                rotation = 0;
            else if(bg_cube[51] == color::D)
                rotation = 1;
            else if(bg_cube[47] == color::D)
                rotation = -1;
            else if(bg_cube[53] == color::D)
                rotation = 2;
        }
        else if(twisted_corners.size() == 2) {
            if(bg_cube[24] == color::D)
                rotation = 0;
            else if(bg_cube[15] == color::D)
                rotation = 1;
            else if(bg_cube[33] == color::D)
                rotation = -1;
            else if(bg_cube[42] == color::D)
                rotation = 2;
        }
        else
            break;

        // 3. Perform rotation and retest
        std::vector<std::pair<rotation_side, rotation_type>> basic_move = {
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)
        };

        if(rotation != 0)
            basic_move = circle_move(basic_move, rotation);
        
        apply_rot(result, basic_move);
    }

    return result;
}

// Phase 4 - position the bottom corners
std::vector<std::pair<rotation_side, rotation_type>> Human_algo::phase4(Cube_bg_model &bg_cube) const
{
    // lambda for applying the rotation
    auto apply_rot = [&bg_cube](auto &res_vec, std::vector<std::pair<rotation_side, rotation_type>> rts){
        for(const auto &i : rts) {
            res_vec.emplace_back(i.first, i.second);
            bg_cube.rotate(i.first, i.second);
        }
    };

    auto are_sets_equal = [](color a1c, color a2c, color a3c, color b1c, color b2c, color b3c) {
        int a1 = static_cast<int>(a1c);
        int a2 = static_cast<int>(a2c);
        int a3 = static_cast<int>(a3c);
        int b1 = static_cast<int>(b1c);
        int b2 = static_cast<int>(b2c);
        int b3 = static_cast<int>(b3c);
        return (std::min(a1, std::min(a2, a3)) == std::min(b1, std::min(b2, b3))) &&
               (std::max(a1, std::max(a2, a3)) == std::max(b1, std::max(b2, b3))) &&
               (a1+a2+a3 == b1+b2+b3);
    };

    std::vector<std::pair<rotation_side, rotation_type>> result;

    // 1. Rotate D until at least two corners are positioned correctly (ignoring their orientation)
    std::vector<int> correct_corners;
    while(true) {
        std::vector<std::vector<color>> corners = {
            {bg_cube[51], bg_cube[44], bg_cube[15]},
            {bg_cube[45], bg_cube[17], bg_cube[24]},
            {bg_cube[47], bg_cube[26], bg_cube[33]},
            {bg_cube[53], bg_cube[35], bg_cube[42]}
        };

        std::vector<std::vector<color>> colors = {
            {color::D, color::B, color::L}, // DBL
            {color::D, color::L, color::F}, // DLF
            {color::D, color::F, color::R}, // DFR
            {color::D, color::R, color::B}  // DRB
        };

        correct_corners.clear();
        for(int i = 0; i < 4; i++) {
            if(are_sets_equal(corners[i][0], corners[i][1], corners[i][2],
                              colors[i][0], colors[i][1], colors[i][2]))
                correct_corners.push_back(i);
        }
        
        if(correct_corners.size() < 2)
            apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
        else
            break;
    }

    // 2. Swap non-correctly positioned corners
    if(correct_corners.size() != 4) {
        std::vector<std::pair<rotation_side, rotation_type>> swap_DLF_DFR_move = {
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)
        };
        std::vector<std::pair<rotation_side, rotation_type>> swap_DLF_DRB_move = {
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)
        };
        
        // if correctly placed corners are neighbors:
        // swap DLF - DFR
        if(correct_corners[0] == 0 && correct_corners[1] == 3) {
            apply_rot(result, swap_DLF_DFR_move);
        }
        // swap DBL - DLF
        else if(correct_corners[0] == 2 && correct_corners[1] == 3) {
            apply_rot(result, circle_move(swap_DLF_DFR_move, 1));
        }
        // swap DFR - DRB
        else if(correct_corners[0] == 0 && correct_corners[1] == 1) {
            apply_rot(result, circle_move(swap_DLF_DFR_move, -1));
        }
        // swap DBL - DRB
        else if(correct_corners[0] == 1 && correct_corners[1] == 2) {
            apply_rot(result, circle_move(swap_DLF_DFR_move, 2));
        }

        // if correctly placed corners aren't neighbors:
        // swap DLF - DRB
        else if(correct_corners[0] == 0 && correct_corners[1] == 2) {
            apply_rot(result, swap_DLF_DRB_move);
        }
        // swap DBL - DFR
        else if(correct_corners[0] == 1 && correct_corners[1] == 3) {
            apply_rot(result, circle_move(swap_DLF_DRB_move, 1));
        }
    }
    return result;
}

// Phase 3 - solve the middle edges
std::vector<std::pair<rotation_side, rotation_type>> Human_algo::phase3(Cube_bg_model &bg_cube) const
{
    // lambda for applying the rotation
    auto apply_rot = [&bg_cube](auto &res_vec, std::vector<std::pair<rotation_side, rotation_type>> rts){
        for(const auto &i : rts) {
            res_vec.emplace_back(i.first, i.second);
            bg_cube.rotate(i.first, i.second);
        }
    };

    std::vector<std::pair<rotation_side, rotation_type>> result;

    std::vector<std::pair<rotation_side, rotation_type>> FD_FR_move = {
        std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L),
        std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L),
        std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
        std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
        std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
        std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R),
        std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L),
        std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L)
    };
    std::vector<std::pair<rotation_side, rotation_type>> DF_FR_move = {
        std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
        std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
        std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R),
        std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L),
        std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L),
        std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L),
        std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L),
        std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
        std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R)
    };
    

    // 1. Find edges in the D layer that belongs to the middle layer
    while(true) {
        // DF edge doesn't have D color
        if(bg_cube[25] != color::D && bg_cube[46] != color::D) {
            // find the destination
            // FD -> FR
            if(bg_cube[25] == color::F && bg_cube[46] == color::R) {
                apply_rot(result, FD_FR_move);
            }
            // FD -> RB
            else if(bg_cube[25] == color::R && bg_cube[46] == color::B) {
                apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
                apply_rot(result, circle_move(FD_FR_move, -1));
            }
            // FD -> BL
            else if(bg_cube[25] == color::B && bg_cube[46] == color::L) {
                apply_rot(result, {
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
                apply_rot(result, circle_move(FD_FR_move, 2));
            }
            // FD -> LF
            else if(bg_cube[25] == color::L && bg_cube[46] == color::F) {
                apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L)});
                apply_rot(result, circle_move(FD_FR_move, 1));
            }
            // DF -> FR
            else if(bg_cube[25] == color::R && bg_cube[46] == color::F) {
                apply_rot(result, DF_FR_move);
            }
            // DF -> RB
            else if(bg_cube[25] == color::B && bg_cube[46] == color::R) {
                apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
                apply_rot(result, circle_move(DF_FR_move, -1));
            }
            // DF -> BL
            else if(bg_cube[25] == color::L && bg_cube[46] == color::B) {
                apply_rot(result, {
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
                apply_rot(result, circle_move(DF_FR_move, 2));
            }
            // DF -> LF
            else if(bg_cube[25] == color::F && bg_cube[46] == color::L) {
                apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L)});
                apply_rot(result, circle_move(DF_FR_move, 1));
            }
            
        }
        // Rotate D to place any middle-layer edges into DF place
        else if(bg_cube[16] != color::D && bg_cube[48] != color::D)
            apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
        else if(bg_cube[34] != color::D && bg_cube[50] != color::D)
            apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
        else if(bg_cube[43] != color::D && bg_cube[52] != color::D)
            apply_rot(result, {
                std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
                std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
        else
            break;
    }

    // 2. Check middle layer edges placement
    //    If some of them aren't places correctly, swap them with random edge from D
    //    and repeat the phase3
    if(bg_cube[14] != color::L || bg_cube[21] != color::F)
        apply_rot(result, circle_move(FD_FR_move, 1));
    else if(bg_cube[23] != color::F || bg_cube[30] != color::R)
        apply_rot(result, FD_FR_move);
    else if(bg_cube[32] != color::R || bg_cube[39] != color::B)
        apply_rot(result, circle_move(FD_FR_move, -1));
    else if(bg_cube[41] != color::B || bg_cube[12] != color::L)
        apply_rot(result, circle_move(FD_FR_move, 2));
    

    return result;
}

// Phase 2 - solve the top corners
std::vector<std::pair<rotation_side, rotation_type>> Human_algo::phase2(Cube_bg_model &bg_cube) const
{
    // lambda for applying the rotation
    auto apply_rot = [&bg_cube](auto &res_vec, std::vector<std::pair<rotation_side, rotation_type>> rts){
        for(const auto &i : rts) {
            res_vec.emplace_back(i.first, i.second);
            bg_cube.rotate(i.first, i.second);
        }
    };

    std::vector<std::pair<rotation_side, rotation_type>> result;

    // 1. Find corners with U color in the D layer and place them correctly
    while(true) {
        // check DFR corner
        if(bg_cube[26] == color::U || bg_cube[47] == color::U || bg_cube[33] == color::U) {
            // define basic_move according to the orientation of the corner
            // also get another two color codes
            std::vector<std::pair<rotation_side, rotation_type>> basic_move;
            color subcolor1, subcolor2;
            
            if(bg_cube[26] == color::U) { // FRD -> URF
                subcolor1 = bg_cube[47];
                subcolor2 = bg_cube[33];
                basic_move = {
                    std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R),
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
                    std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L)
                };
            }
            else if(bg_cube[47] == color::U) { // DFR -> URF
                subcolor1 = bg_cube[26];
                subcolor2 = bg_cube[33];
                basic_move = {
                    std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R),
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L),
                    std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L),
                    std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L),
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
                    std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R)
                };
            }
            else if(bg_cube[33] == color::U) { // RDF -> URF
                subcolor1 = bg_cube[47];
                subcolor2 = bg_cube[26];
                basic_move = {
                    std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L),
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L),
                    std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R)
                };
            }
            
            // now define the overall operation rotation according to the subcolors
            if(std::min(subcolor1, subcolor2) == color::L && std::max(subcolor1, subcolor2) == color::F) {
                apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L)});
                apply_rot(result, circle_move(basic_move, 1));
            }
            else if(std::min(subcolor1, subcolor2) == color::F && std::max(subcolor1, subcolor2) == color::R) {
                apply_rot(result, basic_move);
            }
            else if(std::min(subcolor1, subcolor2) == color::R && std::max(subcolor1, subcolor2) == color::B) {
                apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
                apply_rot(result, circle_move(basic_move, -1));
            }
            else if(std::min(subcolor1, subcolor2) == color::L && std::max(subcolor1, subcolor2) == color::B) {
                apply_rot(result, {
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
                apply_rot(result, circle_move(basic_move, 2));
            }
        }
        // check all other corners in the D layer & rotate D to place corner to DFR position
        else if(bg_cube[17] == color::U || bg_cube[24] == color::U || bg_cube[45] == color::U)
                apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
        else if(bg_cube[15] == color::U || bg_cube[51] == color::U || bg_cube[44] == color::U)
                apply_rot(result, {
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
        else if(bg_cube[35] == color::U || bg_cube[42] == color::U || bg_cube[53] == color::U)
                apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L)});
        else
            break;
    }

    // 1. Check colors of the U corners
    int action = 0; // 0 = no_action, 1 = R'DR, 2 = R'D'R
    int circle = 0;
    if(bg_cube[0] != color::U) {
        action = (bg_cube[38] == color::U) ? 1 : 2;
        circle = 2;
    }
    else if(bg_cube[6] != color::U) {
        action = (bg_cube[11] == color::U) ? 1 : 2;
        circle = 1;
    }
    else if(bg_cube[8] != color::U) {
        action = (bg_cube[20] == color::U) ? 1 : 2;
        circle = 0;
    }
    else if(bg_cube[2] != color::U) {
        action = (bg_cube[29] == color::U) ? 1 : 2;
        circle = -1;
    }

    if(action != 0) {
        std::vector<std::pair<rotation_side, rotation_type>> basic_move = {
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R)
        };
        if(action == 2)
            basic_move[1].second = rotation_type::ROTATION_L;
        if(circle != 0)
            basic_move = circle_move(basic_move, circle);
        apply_rot(result, basic_move);
    }
    return result;
}


// Phase 1 - solve the top layer edges
std::vector<std::pair<rotation_side, rotation_type>> Human_algo::phase1(Cube_bg_model &bg_cube) const
{
    // lambda for applying the rotation
    auto apply_rot = [&bg_cube](auto &res_vec, std::vector<std::pair<rotation_side, rotation_type>> rts){
        for(const auto &i : rts) {
            res_vec.emplace_back(i.first, i.second);
            bg_cube.rotate(i.first, i.second);
        }
    };

    std::vector<std::pair<rotation_side, rotation_type>> result;
    
    // 0. Prepare the U side - rotate it to correctly place at least one edge if presented
    int rot_count = 0;
    if(bg_cube[1] == color::U) {
        if(bg_cube[37] == color::L)
            rot_count = 3;
        else if(bg_cube[37] == color::F)
            rot_count = 2;
        else if(bg_cube[37] == color::R)
            rot_count = 1;
    }
    else if(bg_cube[3] == color::U) {
        if(bg_cube[10] == color::F)
            rot_count = 3;
        else if(bg_cube[10] == color::R)
            rot_count = 2;
        else if(bg_cube[10] == color::B)
            rot_count = 1;
    }
    else if(bg_cube[7] == color::U) {
        if(bg_cube[19] == color::L)
            rot_count = 1;
        else if(bg_cube[19] == color::R)
            rot_count = 3;
        else if(bg_cube[19] == color::B)
            rot_count = 2;
    }
    else if(bg_cube[5] == color::U) {
        if(bg_cube[28] == color::L)
            rot_count = 2;
        else if(bg_cube[28] == color::F)
            rot_count = 1;
        else if(bg_cube[28] == color::B)
            rot_count = 3;
    }
    for(int i = 0; i < rot_count; i++) {
        apply_rot(result, {std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R)});
    }
    
    // 1. Check edges that are already placed in the top layer
    while(true) {
        // UB edge
        if((bg_cube[1] == color::U && bg_cube[37] != color::B) || bg_cube[37] == color::U)
            result.emplace_back(rotation_side::SIDE_B, rotation_type::ROTATION_R);
        // UL edge
        else if((bg_cube[3] == color::U && bg_cube[10] != color::L) || bg_cube[10] == color::U)
            result.emplace_back(rotation_side::SIDE_L, rotation_type::ROTATION_R);
        // UR edge
        else if((bg_cube[5] == color::U && bg_cube[28] != color::R) || bg_cube[28] == color::U)
            result.emplace_back(rotation_side::SIDE_R, rotation_type::ROTATION_R);
        // UF edge
        else if((bg_cube[7] == color::U && bg_cube[19] != color::F) || bg_cube[19] == color::U)
            result.emplace_back(rotation_side::SIDE_F, rotation_type::ROTATION_R);
        else
            break;
            
        bg_cube.rotate(result.back().first, result.back().second);
    }

    // 2. Place edges from the D to the U layer
    while(true) {
        // orient & place DF edge
        if(bg_cube[46] == color::U) {
            // F2
            std::vector<std::pair<rotation_side, rotation_type>> basic_move = {
                std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R),
                std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R)
            };
            
            // DF -> UF
            if(bg_cube[25] == color::F) {
                apply_rot(result, basic_move);
            }
            // DF -> UL
            else if(bg_cube[25] == color::L) {
                // circled left
                apply_rot(result, {
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L)});
                apply_rot(result, circle_move(basic_move, 1));
            }
            // DF -> UR
            else if(bg_cube[25] == color::R) {
                // circled right
                apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
                apply_rot(result, circle_move(basic_move, -1));
            }
            // DF -> UB
            else if(bg_cube[25] == color::B) {
                // circled 180
                apply_rot(result, {
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
                apply_rot(result, circle_move(basic_move, 2));
            }
        }
        // orient & place FD edge
        else if(bg_cube[25] == color::U) {
            // U' F' R F U
            std::vector<std::pair<rotation_side, rotation_type>> basic_move = {
                std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_L),
                std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L),
                std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
                std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R),
                std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R)
            };
            
            // FD -> UF
            if(bg_cube[46] == color::F) {
                apply_rot(result, basic_move);
            }
            // FD -> UL
            else if(bg_cube[46] == color::L) {
                // circled left
                apply_rot(result, {
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L)});
                apply_rot(result, circle_move(basic_move, 1));
            }
            // FD -> UR
            else if(bg_cube[46] == color::R) {
                // circled right
                apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
                apply_rot(result, circle_move(basic_move, -1));
            }
            // FD -> UB
            else if(bg_cube[46] == color::B) {
                // circled 180
                apply_rot(result, {
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
                apply_rot(result, circle_move(basic_move, 2));
            }
        }
        // rotate D to place edge with UP color to the DF/FD
        else if(bg_cube[50] == color::U || bg_cube[34] == color::U)
                apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L)});
        else if(bg_cube[48] == color::U || bg_cube[16] == color::U)
                apply_rot(result, {std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
        else if(bg_cube[52] == color::U || bg_cube[43] == color::U)
                apply_rot(result, {
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R),
                    std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R)});
        else
            break;
    }

    // 3. Move edges from the middle layer to their destination
    while(true) {
        // let's define some movement algos first
        // RF -> UF = F'
        std::vector<std::pair<rotation_side, rotation_type>> RF_UF_move = {
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L)
        };
        // RF -> UR = U F' U'
        std::vector<std::pair<rotation_side, rotation_type>> RF_UR_move = {
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_L)
        };
        // RF -> UB = U2 F' U2
        std::vector<std::pair<rotation_side, rotation_type>> RF_UB_move = {
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R)
        };
        // RF -> UL = U' F' U
        std::vector<std::pair<rotation_side, rotation_type>> RF_UL_move = {
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R)
        };
        // FR -> UR = R
        std::vector<std::pair<rotation_side, rotation_type>> FR_UR_move = {
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R)
        };
        // FR -> UB = U R U'
        std::vector<std::pair<rotation_side, rotation_type>> FR_UB_move = {
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_L)
        };
        // FR -> UL = U2 R U2
        std::vector<std::pair<rotation_side, rotation_type>> FR_UL_move = {
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R)
        };
        // FR -> UF = U' R U
        std::vector<std::pair<rotation_side, rotation_type>> FR_UF_move = {
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_L),
            std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R),
            std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R)
        };

        // RF -> Ux
        if(bg_cube[30] == color::U) {
            if(bg_cube[23] == color::L)
                apply_rot(result, RF_UL_move);
            else if(bg_cube[23] == color::F)
                apply_rot(result, RF_UF_move);
            else if(bg_cube[23] == color::R)
                apply_rot(result, RF_UR_move);
            else if(bg_cube[23] == color::B)
                apply_rot(result, RF_UB_move);
        }
        // FR -> Ux
        else if(bg_cube[23] == color::U) {
            if(bg_cube[30] == color::L)
                apply_rot(result, FR_UL_move);
            else if(bg_cube[30] == color::F)
                apply_rot(result, FR_UF_move);
            else if(bg_cube[30] == color::R)
                apply_rot(result, FR_UR_move);
            else if(bg_cube[30] == color::B)
                apply_rot(result, FR_UB_move);
        }
        
        // BR -> Ux
        else if(bg_cube[39] == color::U) {
            if(bg_cube[32] == color::L)
                apply_rot(result, circle_move(RF_UB_move, -1));
            else if(bg_cube[32] == color::F)
                apply_rot(result, circle_move(RF_UL_move, -1));
            else if(bg_cube[32] == color::R)
                apply_rot(result, circle_move(RF_UF_move, -1));
            else if(bg_cube[32] == color::B)
                apply_rot(result, circle_move(RF_UR_move, -1));
        }
        // RB -> Ux
        else if(bg_cube[32] == color::U) {
            if(bg_cube[39] == color::L)
                apply_rot(result, circle_move(FR_UB_move, -1));
            else if(bg_cube[39] == color::F)
                apply_rot(result, circle_move(FR_UL_move, -1));
            else if(bg_cube[39] == color::R)
                apply_rot(result, circle_move(FR_UF_move, -1));
            else if(bg_cube[39] == color::B)
                apply_rot(result, circle_move(FR_UR_move, -1));
        }

        // FL -> Ux
        else if(bg_cube[21] == color::U) {
            if(bg_cube[14] == color::L)
                apply_rot(result, circle_move(RF_UF_move, 1));
            else if(bg_cube[14] == color::F)
                apply_rot(result, circle_move(RF_UR_move, 1));
            else if(bg_cube[14] == color::R)
                apply_rot(result, circle_move(RF_UB_move, 1));
            else if(bg_cube[14] == color::B)
                apply_rot(result, circle_move(RF_UL_move, 1));
        }
        // LF -> Ux
        else if(bg_cube[14] == color::U) {
            if(bg_cube[21] == color::L)
                apply_rot(result, circle_move(FR_UF_move, 1));
            else if(bg_cube[21] == color::F)
                apply_rot(result, circle_move(FR_UR_move, 1));
            else if(bg_cube[21] == color::R)
                apply_rot(result, circle_move(FR_UB_move, 1));
            else if(bg_cube[21] == color::B)
                apply_rot(result, circle_move(FR_UL_move, 1));
        }

        // LB -> Ux
        else if(bg_cube[12] == color::U) {
            if(bg_cube[41] == color::L)
                apply_rot(result, circle_move(RF_UR_move, 2));
            else if(bg_cube[41] == color::F)
                apply_rot(result, circle_move(RF_UB_move, 2));
            else if(bg_cube[41] == color::R)
                apply_rot(result, circle_move(RF_UL_move, 2));
            else if(bg_cube[41] == color::B)
                apply_rot(result, circle_move(RF_UF_move, 2));
        }
        // BL -> Ux
        else if(bg_cube[41] == color::U) {
            if(bg_cube[12] == color::L)
                apply_rot(result, circle_move(FR_UR_move, 2));
            else if(bg_cube[12] == color::F)
                apply_rot(result, circle_move(FR_UB_move, 2));
            else if(bg_cube[12] == color::R)
                apply_rot(result, circle_move(FR_UL_move, 2));
            else if(bg_cube[12] == color::B)
                apply_rot(result, circle_move(FR_UF_move, 2));
        }
        
        else
            break;
    }
    return result;
}

// function to "rotate" moves cw around the cube axis
// example1: circle_move([U F R D U' F'], 1)  = [U R B D U' R']
// example2: circle_move([U F R D U' F'], -1) = [U L F D U' L']
std::vector<std::pair<rotation_side, rotation_type>> Human_algo::circle_move(std::vector<std::pair<rotation_side, rotation_type>> in_vec, int r) const
{
    std::vector<std::pair<rotation_side, rotation_type>> out_vec;
    for(const auto &i : in_vec) {
        rotation_side out_side;
        if(i.first == rotation_side::SIDE_U || i.first == rotation_side::SIDE_D)
            out_side = i.first;
        else if(i.first == rotation_side::SIDE_L) {
            if(r == -1)
                out_side = rotation_side::SIDE_F;
            else if(r == 1)
                out_side = rotation_side::SIDE_B;
            else if(r == 2)
                out_side = rotation_side::SIDE_R;
        }
        else if(i.first == rotation_side::SIDE_F) {
            if(r == -1)
                out_side = rotation_side::SIDE_R;
            else if(r == 1)
                out_side = rotation_side::SIDE_L;
            else if(r == 2)
                out_side = rotation_side::SIDE_B;
        }
        else if(i.first == rotation_side::SIDE_R) {
            if(r == -1)
                out_side = rotation_side::SIDE_B;
            else if(r == 1)
                out_side = rotation_side::SIDE_F;
            else if(r == 2)
                out_side = rotation_side::SIDE_L;
        }
        else if(i.first == rotation_side::SIDE_B) {
            if(r == -1)
                out_side = rotation_side::SIDE_R;
            else if(r == 1)
                out_side = rotation_side::SIDE_L;
            else if(r == 2)
                out_side = rotation_side::SIDE_F;
        }
        out_vec.emplace_back(out_side, i.second);
    }
    return out_vec;
};
