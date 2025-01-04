#pragma once

#include "database.h"

#include "../phase_info/phase1_info.h"

/*
 * In G1, the orientation of all 12 edges is solved (good orientation means an edge can be solved
 * without using a 90-degree U or D move) G0->G1 only looks at edge orientations (0 for good, 1 for bad),
 * which gives 2^12 unique states. Only half of these states is reachable because the total edge orientation
 * value is always even (each move affects 0 or 4 edges which gives an overall even value).
 *
 * Therefore, there are 2^12 / 2 = 2^11 = 2048 states to store in a database.
*/
struct Phase1_database : public Database {
	Phase1_database() : Database(2048, "G0")
	{
		phase_info = std::make_shared<Phase1_info>();
	}
};