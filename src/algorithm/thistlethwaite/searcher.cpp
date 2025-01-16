#include "searcher.h"

#include "database/phase1_database.h"
#include "database/phase2_database.h"
#include "database/phase3_database.h"
#include "database/phase4_database.h"

std::vector<Cube_bg_model::emove> Searcher::search(const Cube_bg_model& cube, const Phase_info& phase_info, const Database& database) const
{
    // set to true if cube in solved state for current phase
    bool solved = false;

    // queue to search
    std::queue<Cube_bg_model> cubes_queue;

    Cube_bg_model curr_cube;
    emove         last_move = emove::NO_MOVE;

    // current phase moves to get solved (on current phase) cube
    std::vector<emove> solve_moves;

    // firstly, add solved cube to queue
    cubes_queue.push(cube);

    while (!cubes_queue.empty()) {
        // get front cube state from cubes_queue
        curr_cube = cubes_queue.front();
        cubes_queue.pop();

        // end loop if cube already solved on current phase
        if (phase_info.solved(curr_cube)) {
            solved      = true;
            break;
        }

        // if solved state in the database didn't match the goal
        if (database[curr_cube] == 0)
            throw std::logic_error("Searcher: A solved state in the database didn't match the goal");

        // generate child nodes with allowed moves
        for (const auto& move : phase_info.allowed_moves) {
            // skip move if it is redudant
            if (utilities::redundant(move, last_move))
                continue;
            
            // make copy of cube and do specified rotate
            Cube_bg_model new_cube = curr_cube;
            new_cube.rotate(move);

            // don't consider nodes that move away from a solution to more efficient graph traversal
            if (database[new_cube] < database[curr_cube]) {
                cubes_queue.push(new_cube);
                solve_moves.push_back(move);
                last_move = move;
                break;
            }
        }
    }
    
    // no solution was found and the queue is empty, invalid database led to wrong assumptions
    if (!solved)
        throw std::logic_error("Searcher::Graph Didn't find a solution, invalid database.");

    return solve_moves;
}