#pragma once

#include <vector>
#include <array>
#include <memory>

#include "cube_bg_model.h"

/*
 * Base class for phase additional info and functions
 */
struct Phase_info {
	using ecolour = Cube_bg_model::ecolour;
    using emove   = Cube_bg_model::emove;
    using eedge   = Cube_bg_model::eedge;
    using ecorner = Cube_bg_model::ecorner;
    using epiece  = Cube_bg_model::epiece;

	 // checks if cube solved on current phase
	virtual bool solved(const Cube_bg_model& cube) const = 0;

	std::vector<emove> allowed_moves;
};