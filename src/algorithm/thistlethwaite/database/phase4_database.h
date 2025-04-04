#pragma once

#include "database.h"
#include "../phase_info/phase4_info.h"

/*
 * In G3->G4, finally the cube is solved. In this state the cube is seperated to 3 edge slices
 * and 2 corner tetrads (each containing 4 pieces). Because only 180-degree moves are allowed the
 * pieces will never leave these orbits. Each slice/tetrad can be permuted in 4! ways which
 * gives 4!^5, but there are some restrictions:
 *
 * Corners: only 4!^2 / 6 of the corner states are reachable due to parity and disallowed lone 3-cycles.
 *
 * Edges: only 4!^4 / 2 of the edge states are reachable due to parity.
 *
 * Therefore, there are 4!^5 / 12 = 96 * 4!^3 / 2 = 663552 states to store in the database.
 *
 * Disallowed lone 3-cycles explained below: 
 * puzzling.stackexchange.com/questions/5402/what-is-the-meaning-of-a-tetrad-twist-in-thistlethwaites-algorithm
*/
struct Phase4_database : public Database {
	Phase4_database() : Database(663552, "phase4")
    {
        phase_info = std::make_shared<Phase4_info>();
    }
};
