#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <queue>

#include "utilities/searchutil.h"
#include "cube_bg_model.h"
#include "database/database.h"
#include "thistlethwaite/Goals/goal.h"

/*
 * A* searching algorithm
 */
struct AStar {
    using EMOVE = Cube_bg_model::EMOVE;

    struct AStar_node;
    using AStar_node_ptr = std::shared_ptr<AStar_node>;

    struct AStar_node {
        Cube_bg_model  cube;
        AStar_node_ptr parent = nullptr;
        EMOVE          move   = EMOVE::NO_MOVE;
        uint8_t        score;
    };

    std::vector<EMOVE> search(const Cube_bg_model& cube, const Goal& goal, const Database& database) const;
};
