#pragma once

#include <iostream>
#include <string>
#include <array>
#include <queue>

#include "../database/database.h"
#include "../phase_info/phase_info.h"

#include "../utilities/timer.h"
#include "../utilities/search_utilities.h"

/* 
 * Searches the cube (IDDFS) for all possible states and stores the depth of each state in a file
 */
class DB_generator {
public:
    using emove = Cube_bg_model::emove;

    // if a cube isn't passed the database will be generated using a solved cube
    void generate(const Phase_info& phase_info, Database& database) const;

private:
    bool _db_searcher(Cube_bg_model cube, Cube_bg_model::emove last_move,
                      const Phase_info& phase_info, Database& database,
                      int depth, int max_depth,
                      std::vector<bool>& visited) const;
};
