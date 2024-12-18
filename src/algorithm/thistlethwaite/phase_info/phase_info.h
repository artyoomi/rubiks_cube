#pragma once

#include <vector>
#include <array>
#include <memory>

#include "cube_bg_model.h"

/*
 * Base class for phase additional info and functions
 */
struct Phase_info {
	using ECOLOUR = Cube_bg_model::ECOLOUR;
    using EMOVE   = Cube_bg_model::EMOVE;
    using EEDGE   = Cube_bg_model::EEDGE;
    using ECORNER = Cube_bg_model::ECORNER;
    using EPIECE  = Cube_bg_model::EPIECE;

	 // checks if cube solved on current phase
	virtual bool solved(const Cube_bg_model& cube) const = 0;

	std::vector<EMOVE> allowed_moves;
};