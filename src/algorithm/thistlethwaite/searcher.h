#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <queue>

#include "utilities/searchutil.h"
#include "../cube_bg_model.h"
#include "database/database.h"
#include "phase_info/phase_info.h"

/*
 * Database search algorithm
 */
struct Searcher {
    using emove = Cube_bg_model::emove;

    struct Graph_node;
    using Graph_node_ptr = std::shared_ptr<Graph_node>;

    struct Graph_node {
        Cube_bg_model  cube;
        Graph_node_ptr parent = nullptr;
        emove          move   = emove::NO_MOVE;
        uint8_t        score;
    };

    std::vector<emove> search(const Cube_bg_model& cube, const Phase_info& phase_info, const Database& database) const;
};
