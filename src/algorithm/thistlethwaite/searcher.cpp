#include "searcher.h"

std::vector<Cube_bg_model::EMOVE> AStar::search(const Cube_bg_model& cube, const Goal& goal, const Database& database) const
{
     bool    solved     = false;
    uint8_t root_score = database[cube];

    AStar_node_ptr root_node   = std::make_shared<AStar_node>(AStar_node{cube, nullptr, EMOVE::NO_MOVE, root_score});
    AStar_node_ptr curr_node   = nullptr;
    AStar_node_ptr solved_node = nullptr;

    std::priority_queue<AStar_node_ptr> pr_q;
    pr_q.push(root_node);

    while (!pr_q.empty()) {
        curr_node = pr_q.top();
        pr_q.pop();

        // found a solution
        if (goal.contented(curr_node->cube)) {
            solved_node = curr_node;
            solved     = true;
            break;
        }
        // solved state in the database didn't satisfiy the goal
        if (database[curr_node->cube] == 0)
            throw std::logic_error("Searcher::Astar A solved state in the database didn't satisfiy the goal");

        // generate child nodes
        for (const auto& move : goal.legalMoves) {
            if (utilities::redundant(move, curr_node->move)) continue;
            
            Cube_bg_model copy = curr_node->cube;
            copy.rotate(move);

            uint32_t newIndex = database.id(copy);
            uint8_t  newScore = database[newIndex];

            // don't consider nodes that move away from a solution
            if (newScore < curr_node->score) {
                AStar_node_ptr newNode = std::make_shared<AStar_node>(AStar_node{ copy, curr_node, move, newScore });
                pr_q.push(newNode);
            }
            // copy.revertMove(move);
        }
    }
    // no solution was found and the queue is empty, invalid database led to wrong assumptions
    if (!solved)
        throw std::logic_error("Searcher::Astar Didn't find a solution, invalid database.");

    std::vector<EMOVE> result;
    while (solved_node->parent)
    {
        result.push_back(solved_node->move);
        solved_node = solved_node->parent;
    }
    // moves are pushed in reverse order
    std::reverse(result.begin(), result.end());

    return result;
}