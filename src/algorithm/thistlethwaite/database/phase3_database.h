#pragma once

#include "database.h"
#include "../utilities/indexer.h"

/*
 * In G3, a cube is solvable using 180-degree moves only. This means that all edges are in their
 * home slice and all corners are in their natural orbits. The M-slice is already solved in G1.
 * One solved slice / tetrad means that the second slice / tetrad is also solved, so the positions
 * of 4 edges and 4 corners are tracked (8C4 possible combinations for both)
 * 
 * Because of 90-degree L/R face turns, there are states in G2 that have odd parity which adds an
 * additional factor of 2.
 * 
 * Additionally, a factor of 3 is added which is explained here:
 * puzzling.stackexchange.com/questions/5402/what-is-the-meaning-of-a-tetrad-twist-in-thistlethwaites-algorithm
 *
 * Therefore, there are 8C4^2 * 2 * 6 = 29400 states to store in the database.
*/
struct Phase3_database : public Database {
	Phase3_database() : Database(29400, "G2") {}

    uint32_t id(const Cube_bg_model& cube) const override;

private:
    CombIndexer<4> combIndexer4;
    PermIndexer<3> permIndexer3;

    using emove = Cube_bg_model::emove;

    // moves to solve the even tetrad (ULB, DLF, DRB, URF)
    const std::array<std::vector<emove>, 3> C_evenTetradSolvingMoves = {{
        { emove::U2, emove::L2, emove::B2 },  // ULB
        { emove::D2, emove::F2 },             // DLF
        { emove::R2 },                        // DRB
    }};
    // moves to solve ULF (first corner of the odd tetrad)
    const std::array<std::array<emove, 4>, 3> C_oddTetradSolvingMoves = {{
        // these move sequences perform a double swap on the four pieces of  
        // the odd tetrad without affecting the corners in the even tetrad
        { emove::F2, emove::L2, emove::F2, emove::U2 },
        { emove::U2, emove::F2, emove::U2, emove::L2 },
        { emove::L2, emove::U2, emove::L2, emove::F2 },
    }};

    // imitates a move on an array
    void imitate_move(emove move, std::array<uint8_t, 8>& tetradsPerm) const;
};
