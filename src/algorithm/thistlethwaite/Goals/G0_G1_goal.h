#ifndef G0_G1_GOAL_H
#define G0_G1_GOAL_H

#include "goal.h"

struct G0_G1_Goal : public Goal
{
	G0_G1_Goal()
        : Goal({
            Cube_bg_model::EMOVE::L , Cube_bg_model::EMOVE::Lp , Cube_bg_model::EMOVE::L2,
            Cube_bg_model::EMOVE::R , Cube_bg_model::EMOVE::Rp , Cube_bg_model::EMOVE::R2,
            Cube_bg_model::EMOVE::F , Cube_bg_model::EMOVE::Fp , Cube_bg_model::EMOVE::F2,
            Cube_bg_model::EMOVE::B , Cube_bg_model::EMOVE::Bp , Cube_bg_model::EMOVE::B2,
            Cube_bg_model::EMOVE::U , Cube_bg_model::EMOVE::Up , Cube_bg_model::EMOVE::U2,
            Cube_bg_model::EMOVE::D , Cube_bg_model::EMOVE::Dp , Cube_bg_model::EMOVE::D2, })
	{
	}

	// G1 is contented when all the edges are oriented correctly
	bool contented(const Cube_bg_model& cube) const override;
};

#endif // G0_G1_GOAL_H
