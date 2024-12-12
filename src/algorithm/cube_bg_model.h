#pragma once

#include <cstdint>
#include <cstddef>

/*
 * We need some way to store the cube sides data, right?
 * Here goes the format:
 * Value_Type = uint8_t (there're only 6 colors, so why more?)
 * Let's visualize cube sides using the indicies of the corresponding
 * elements in the data array:
 *          0  1  2
 *          3  4  5
 *          6  7  8
 *         ----------
 * 9  10 11|18 19 20|27 28 29|36 37 38
 * 12 13 14|21 22 23|30 31 32|39 40 41
 * 15 16 17|24 25 26|33 34 35|42 43 44
 *         ----------
 *          45 46 47
 *          48 49 50
 *          51 52 53
 *
 * And names of the sides:
 *        (U)p
 *       ---------
 * (L)eft|(F)ront|(R)ight|(B)ack
 *       ---------
 *        (D)own
 *
 * Now let's define rotations - each side can be rotated to 90, 180, 270 deg clockwise
 * To do that rotation, call rotate(side, rotation).
 *
 * Note: this header doesn't define any colors - they are represented as uint8_t in range [0, 5]
 */

// can be static_cast'ed to offset of the first element using multiplication by 9
enum class rotation_side {
    SIDE_U = 0,
    SIDE_L = 1,
    SIDE_F = 2,
    SIDE_R = 3,
    SIDE_B = 4,
    SIDE_D = 5
};

enum class rotation_type {
    ROTATION_R = 0,
    ROTATION_L = 1,
};

class Cube_bg_model
{
public:
    // normal contructor
    Cube_bg_model();
    // copy constructor
    Cube_bg_model(const Cube_bg_model &another);

    // rotate selected side
    void rotate(rotation_side side, rotation_type rot);

    // get side colors
    // returned as uint8_t[9] array:
    // 0 1 2
    // 3 4 5
    // 6 7 8
    // Note: dynamically allocates memory!
    uint8_t *get_side(rotation_side side);
private:
    // rotate one side (doesn't affect adjacent side)
    void _rotate_side(rotation_side side);

    // rotate adjacent elements
    void _rotate_adjacent(rotation_side side);
    uint8_t _cube_data[54];
};
