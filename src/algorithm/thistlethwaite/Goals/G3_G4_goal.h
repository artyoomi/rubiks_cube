#ifndef G3_G4_GOAL_H
#define G3_G4_GOAL_H

#include "goal.h"

struct G3_G4_Goal : public Goal
{
	G3_G4_Goal()
        : Goal({
			Cube_bg_model::EMOVE::L2,
			Cube_bg_model::EMOVE::R2,
			Cube_bg_model::EMOVE::F2,
			Cube_bg_model::EMOVE::B2,
			Cube_bg_model::EMOVE::U2,
            Cube_bg_model::EMOVE::D2, })
	{
	}

	// G4 is contented when the cube is solved
	bool contented(const Cube_bg_model& cube) const override;
};

#endif // G3_G4_GOAL_H
