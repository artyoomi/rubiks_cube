#ifndef GOAL_H
#define GOAL_H

#include <vector>
#include <array>
#include <memory>

#include "cube_bg_model.h"

// base class for a goal that checks if a goal is reached and provides the moves to reach it
struct Goal
{
    Goal(const std::vector<Cube_bg_model::EMOVE>& legal_moves)
        : legalMoves(legal_moves)
	{
	}

    // checks if a cube is in a state that satisfies the goal
	virtual bool contented(const Cube_bg_model& cube) const = 0;

	std::vector<Cube_bg_model::EMOVE> legalMoves;
};

#endif // GOAL_H
