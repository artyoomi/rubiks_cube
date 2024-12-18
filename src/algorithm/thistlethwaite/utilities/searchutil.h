#pragma once

#include "cube_bg_model.h"

// functions to help in search
namespace utilities
{
    using EMOVE = Cube_bg_model::EMOVE;

    bool redundant(EMOVE curr, EMOVE last);
};