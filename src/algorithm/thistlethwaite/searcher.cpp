#include "searcher.h"

std::vector<Cube_bg_model::emove> Searcher::search(const Cube_bg_model& cube, const Phase_info& phase_info, const Database& database) const
{
    // compares node scores for logarithmic insertions
    auto cmp_nodes = [](Graph_node_ptr left, Graph_node_ptr right) -> bool
    {
        return left->score > right->score;
    };

    // set to true if cube in solved state for current phase
     bool solved = false;

    // initialize root node
    uint8_t        root_score = database[cube];
    Graph_node_ptr root_node  = std::make_shared<Graph_node>(Graph_node{cube, nullptr, emove::NO_MOVE, root_score});

    Graph_node_ptr curr_node   = nullptr;
    Graph_node_ptr solved_node = nullptr;

    /*
     * here we just want to build min heap to get node
     * with minimal score in fastest possible time
     */
    std::priority_queue<Graph_node_ptr, std::vector<Graph_node_ptr>, decltype(cmp_nodes)> pr_q;

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
            throw std::logic_error("Searcher: A solved state in the database didn't match the goal");

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

            // don't consider nodes that move away from a solution to more efficient graph traversal
            if (new_score < curr_node->score) {
                Graph_node_ptr new_node = std::make_shared<Graph_node>(Graph_node{copy, curr_node, move, new_score});
                pr_q.push(new_node);
            }
        }
    }
    // no solution was found and the queue is empty, invalid database led to wrong assumptions
    if (!solved)
        throw std::logic_error("Searcher::Graph Didn't find a solution, invalid database.");

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