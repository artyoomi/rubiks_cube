#include "astar.h"

std::vector<Cube_bg_model::emove> AStar::search(const Cube_bg_model& cube, const Phase_info& phase_info, const Database& database) const
{
    // compares node scores for logarithmic insertions
    auto compareNodeScore = [](AStar_node_ptr lhs, AStar_node_ptr rhs) -> bool
    {
        return lhs->score > rhs->score;
    };

    // set to true if cube in solved state for current phase
     bool solved = false;

    // initialize root node
    uint8_t        root_score = database[cube];
    AStar_node_ptr root_node  = std::make_shared<AStar_node>(AStar_node{cube, nullptr, emove::NO_MOVE, root_score});

    AStar_node_ptr curr_node   = nullptr;
    AStar_node_ptr solved_node = nullptr;

    // here we compare by min
    std::priority_queue<AStar_node_ptr, std::vector<AStar_node_ptr>, decltype(compareNodeScore)> pr_q;

    // firstly, add root_node to queue
    pr_q.push(root_node);

    while (!pr_q.empty()) {
        curr_node = pr_q.top();
        pr_q.pop();

        // found a solution
        if (phase_info.solved(curr_node->cube)) {
            solved_node = curr_node;
            solved      = true;
            break;
        }

        // solved state in the database didn't match the goal
        if (database[curr_node->cube] == 0)
            throw std::logic_error("AStar: A solved state in the database didn't match the goal");

        // generate child nodes with allowed moves
        for (const auto& move : phase_info.allowed_moves) {
            // skip move if it is redudant
            if (utilities::redundant(move, curr_node->move))
                continue;
            
            // make copy of cube and do specified rotate
            Cube_bg_model copy = curr_node->cube;
            copy.rotate(move);

            // get id of cube copy and get depth from database
            uint32_t new_id = database.id(copy);
            uint8_t  new_score = database[new_id];

            // don't consider nodes that move away from a solution
            //if (new_score < curr_node->score) {
                AStar_node_ptr new_node = std::make_shared<AStar_node>(AStar_node{copy, curr_node, move, new_score});
                pr_q.push(new_node);
            //}
        }
    }
    // no solution was found and the queue is empty, invalid database led to wrong assumptions
    if (!solved)
        throw std::logic_error("Searcher::Astar Didn't find a solution, invalid database.");

    // current phase moves to get solved (on current phase) cube
    std::vector<emove> result;

    // come back to root_node and store taken moves
    while (solved_node->parent) {
        result.push_back(solved_node->move);
        solved_node = solved_node->parent;
    }
    // moves are pushed in reverse order
    std::reverse(result.begin(), result.end());

    return result;
}