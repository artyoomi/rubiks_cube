#include "db_generator.h"

void DB_generator::generate(const Goal& goal, Database& database) const
{
    Cube_bg_model cube;
    uint8_t       depth = 0;
    Timer         timer;

    timer.set();

    while (!database.full()) {
        // keeps track of visited nodes in each of the iterations
        std::vector<bool> visited(database.capacity(), false);

        std::cout << "Depth: " << (int)depth << ". ";
        if (_db_searcher(cube, Cube_bg_model::EMOVE::NO_MOVE, goal, database, 0, depth, visited))
            break;

        std::cout << "visited states: " << database.size() << " / " << database.capacity() << std::endl;
        ++depth;
    }

    // all states visited, write the result to a file
    database.save();
    std::cout << "Finished generating (" << timer.get() / 1000 << " seconds)" << std::endl;
}


bool DB_generator::_db_searcher(Cube_bg_model cube, Cube_bg_model::EMOVE last_move,
                                const Goal& goal, Database& database,
                                uint8_t depth, uint8_t max_depth, std::vector<bool>& visited) const
{
    // id of the current state of cube
    uint32_t index = database.id(cube);

    // prunes the branch if the current cube state was already visited in an earlier 
    // iteration, or in the same iteration by a different branch
    if (visited[index] || depth > database[index])
        return false;
    
    // marks the current cube state as visited
    visited[index] = true;

    // index the cube states in the database in leaf level
    if (depth == max_depth) {
        database.set(index, depth);
        return database.full();
    } else {
        // generate child nodes
        for (const auto move : goal.legalMoves) {
            if (utilities::redundant(move, last_move))
                continue;

            cube.rotate(move);

            if (_db_searcher(cube, move, goal, database, depth + 1, max_depth, visited))
                return true;

            cube.revert_rotate(move);
        }
    }

    // branch led to a dead end
    return false;
}
