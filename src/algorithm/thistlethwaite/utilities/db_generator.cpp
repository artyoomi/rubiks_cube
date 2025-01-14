#include "db_generator.h"

void DB_generator::generate(const Phase_info& phase_info, Database& database) const
{
    Cube_bg_model cube;
    int           depth = 0;
    Timer         timer;

    timer.set();

    while (!database.full()) {
        // keeps track of visited nodes in each of the iterations
        std::vector<bool> visited(database.capacity(), false);

        std::cout << "Depth: " << depth << ". ";

        // this condition will be true only when database will become full
        if (_db_searcher(cube, Cube_bg_model::emove::NO_MOVE, phase_info, database, 0, depth, visited))
            break;

        std::cout << "visited states: " << database.size() << " / " << database.capacity() << std::endl;
        ++depth;
    }

    // all states visited, write the result to a file
    database.save();
    std::cout << "Finished generating (" << timer.get() / 1000 << " seconds)" << std::endl;
}


bool DB_generator::_db_searcher(Cube_bg_model cube, Cube_bg_model::emove last_move,
                                const Phase_info& phase_info, Database& database,
                                int depth, int max_depth,
                                std::vector<bool>& visited) const
{
    // id of the current state of cube
    uint32_t index = phase_info.id(cube);

    /*
     * Meaning of conditions:
     * 1. If current cube state was already visited in the same iteration by a different branch -> return false
     * 2. If current cube state was already visited in earlier iteration -> return false
     */
    if (visited[index] || depth > database[index])
        return false;
    
    // marks the current cube state as visited
    visited[index] = true;

    // index the cube states in the database in leaf level
    if (depth == max_depth) {
        database.set(index, depth);
        return database.full();
    }

    // generate child nodes
    for (const auto move : phase_info.allowed_moves) {
        if (utilities::redundant(move, last_move))
            continue;

        cube.rotate(move);

        if (_db_searcher(cube, move, phase_info, database, depth + 1, max_depth, visited))
            return true;

        cube.revert_rotate(move);
    }

    // branch led to a dead end
    return false;
}
