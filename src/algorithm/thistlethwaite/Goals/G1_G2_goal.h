#ifndef G1_G2_GOAL_H
#define G1_G2_GOAL_H

#include "goal.h"

struct G1_G2_Goal : public Goal
{
	G1_G2_Goal()
        : Goal({
            Cube_bg_model::EMOVE::L , Cube_bg_model::EMOVE::Lp , Cube_bg_model::EMOVE::L2,
			Cube_bg_model::EMOVE::R , Cube_bg_model::EMOVE::Rp , Cube_bg_model::EMOVE::R2,
			Cube_bg_model::EMOVE::F , Cube_bg_model::EMOVE::Fp , Cube_bg_model::EMOVE::F2,
			Cube_bg_model::EMOVE::B , Cube_bg_model::EMOVE::Bp , Cube_bg_model::EMOVE::B2,
			Cube_bg_model::EMOVE::U2,
            Cube_bg_model::EMOVE::D2, })
	{
	}

	// G2 is contented when all the corners are oriented correctly and the M-slice
	// edges are brought back intro their slice
	bool contented(const Cube_bg_model& cube) const override;
};

#endif // G1_G2_GOAL_H
