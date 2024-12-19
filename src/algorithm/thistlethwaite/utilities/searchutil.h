#pragma once

#include "../../cube_bg_model.h"

// functions to help in search
namespace utilities
{
    using emove = Cube_bg_model::emove;

    bool redundant(emove curr, emove last);
};
