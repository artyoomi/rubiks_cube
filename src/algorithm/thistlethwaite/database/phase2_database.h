#pragma once

#include "database.h"
#include "../utilities/indexer.h"

/*
 * In G2, all the LR-slice edges are brought back to their home slice and the orientation of all the corners
 * is solved (their Left or Right facelet is in the Left or Right face). There are 3 ways a corner can be
 * oriented which gives 3^8 corner states. Similar to the edges in G0, only 3^8 / 3 of the corner states are
 * actually reachable because the total orientation value of the corners is always divisible by 3. 12C4 for the edges
 * is for 12 positions where the 4 LR-slice edges can be placed (without regard to order)
 *
 * Therefore, there are 12C4 * 3^8 / 3 = 12C4 * 3^7 = 1082565 states to store in a database.
*/
struct Phase2_database : public Database {
	Phase2_database() : Database(1082565, "G1") {}

        uint32_t id(const Cube_bg_model& cube) const override;

private:
    CombIndexer<4> comb_indexer4;
};
