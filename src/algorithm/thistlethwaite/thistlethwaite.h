#ifndef THISTLETHWAITE_H
#define THISTLETHWAITE_H

#include "solver.h"
#include "groups.h"
#include "searcher.h"

// jaapsch.net/puzzles/thistle.htm
class Thistlethwaite : public Solver {
public:
    using EMOVE = Cube_bg_model::EMOVE;

	Thistlethwaite();

	std::vector<std::pair<rotation_side, rotation_type>> emove_to_rot(std::vector<EMOVE> moves) const;

	std::vector<std::pair<rotation_side, rotation_type>> solve(const Cube_bg_model &bg_cube) const override;

private:
	using G0_G1 = TypedGroup<Phase1_database, G0_G1_Goal>;
	using G1_G2 = TypedGroup<Phase2_database, G1_G2_Goal>;
	using G2_G3 = TypedGroup<Phase3_database, G2_G3_Goal>;
	using G3_G4 = TypedGroup<Phase4_database, G3_G4_Goal>;
    
	G0_G1 m_G0G1;
	G1_G2 m_G1G2;
	G2_G3 m_G2G3;
	G3_G4 m_G3G4;

	std::vector<Group*> m_groups;
};

#endif // THISTLETHWAITE_H
