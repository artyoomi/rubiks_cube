#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <queue>

#include "utilities/search_utilities.h"
#include "../cube_bg_model.h"
#include "database/database.h"
#include "phase_info/phase_info.h"

/*
 * Database search algorithm
 */
struct Searcher {
    using emove = Cube_bg_model::emove;

    std::vector<emove> search(const Cube_bg_model& cube, const Phase_info& phase_info, const Database& database) const;
};
