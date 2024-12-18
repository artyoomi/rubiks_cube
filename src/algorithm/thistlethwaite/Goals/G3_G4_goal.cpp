#include "G3_G4_goal.h"

bool G3_G4_Goal::contented(const Cube_bg_model& cube) const
{
    return cube.solved();
}
