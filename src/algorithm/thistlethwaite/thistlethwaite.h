#pragma once

#include "../solver.h"
#include "phases.h"
#include "searcher.h"

// jaapsch.net/puzzles/thistle.htm
class Thistlethwaite : public Solver {
public:
    using emove = Cube_bg_model::emove;

	Thistlethwaite();

	/*
	 * transform emove notation to (rotation_side;rotation_type) pair
	 * this uses for compatible between program and this algorithm
	 */
	std::vector<std::pair<rotation_side, rotation_type>> emove_to_rot(std::vector<emove> moves) const;

	// solve given cube
	// std::vector<std::vector<std::pair<rotation_side, rotation_type>>> solve(const Cube_bg_model &const_cube) const override;
	std::vector<std::pair<rotation_side, rotation_type>> solve(const Cube_bg_model &const_cube) const override;

private:
	// we give meaningful aliases for convenience
	using Phase1 = TypedPhase<Phase1_database, Phase1_info>;
	using Phase2 = TypedPhase<Phase2_database, Phase2_info>;
	using Phase3 = TypedPhase<Phase3_database, Phase3_info>;
	using Phase4 = TypedPhase<Phase4_database, Phase4_info>;
    
	Phase1 _phase1;
	Phase2 _phase2;
	Phase3 _phase3;
	Phase4 _phase4;

	std::vector<Phase*> _phases;
};
