#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <queue>

#include "utilities/searchutil.h"
#include "cube_bg_model.h"
#include "database/database.h"
#include "thistlethwaite/phase_info/phase_info.h"

/*
 * A* searching algorithm
 */
struct AStar {
    using emove = Cube_bg_model::emove;

    struct AStar_node;
    using AStar_node_ptr = std::shared_ptr<AStar_node>;

    struct AStar_node {
        Cube_bg_model  cube;
        AStar_node_ptr parent = nullptr;
        emove          move   = emove::NO_MOVE;
        uint8_t        score;
    };

    std::vector<emove> search(const Cube_bg_model& cube, const Phase_info& phase_info, const Database& database) const;
};
