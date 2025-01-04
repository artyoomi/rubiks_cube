#pragma once

#include "database.h"
#include "../phase_info/phase3_info.h"

/*
 * In G3, a cube is solvable using 180-degree moves only. This means that all edges are in their
 * home slice and all corners are in their natural orbits. The LR-slice is already placed in G1.
 * So one solved slice / tetrad means that the second slice / tetrad is also solved, and the positions
 * of 4 edges and 4 corners are tracked (8C4 possible combinations for both)
 * 
 * Because of 90-degree L/R face turns, there are states in G2 that have odd parity which adds an
 * additional factor of 2.
 * 
 * Additionally, a factor of 3 is added which is explained here:
 * puzzling.stackexchange.com/questions/5402/what-is-the-meaning-of-a-tetrad-twist-in-thistlethwaites-algorithm
 *
 * Therefore, there are 8C4^2 * 2 * 3 = 29400 states to store in the database.
 * 
 * NOTE: E-slice is UD-slice, S-slice is FB-slice
*/
struct Phase3_database : public Database {
	Phase3_database() : Database(29400, "G2")
    {
        phase_info = std::make_shared<Phase3_info>();
    }
};
